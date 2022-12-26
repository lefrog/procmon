#include <iostream>
#include <cstdio>
#include <vector>
#include <thread>
#include <chrono>
#include <sys/stat.h>
#include <getopt.h>
#include <iomanip>
#include <ctime>

namespace pascal {
class AppError : std::exception {
  const char *_msg;
 public:
  explicit AppError(const char *msg) noexcept(true): _msg(msg) {}
  const char *what() {
    return _msg;
  }
};

static const std::vector<std::string> keywords = {
    "VmPeak",
    "VmSize",
    "VmHWM",
    "VmRSS"
};

void print_header_line() {
  std::cout << "\"Time\"";
  for (const auto& keyword : keywords) {
    std::printf(",\"%s\"", keyword.c_str());
  }
  std::cout << std::endl;
}

void parse_line(const char *line) {
  std::string str = line;
  char _keyword[16];
  char unit[8];
  int value = 0;
  unsigned long found;

  for (const auto& keyword : keywords) {
    found = str.find(keyword);
    if (found == std::string::npos) {
      continue;
    }

    std::sscanf(line, "%s %d %s", _keyword, &value, unit);
    std::cout << "," << value;
    break;
  }
}

void parse_proc_status_file(FILE *procFd) {
  char line[128];
  while (std::fgets(line, sizeof(line), procFd) != nullptr) {
    parse_line(line);
  }
}
}

struct CmdArgs {
  unsigned int pid;
  unsigned int refresh_interval_in_ms = 1000;
};

void process_args(int argc, char *argv[], CmdArgs * cmd_args) {
  int opt;
  while ((opt = getopt(argc, argv, "r:")) != -1) {
    switch (opt) {
      case 'r':
        cmd_args->refresh_interval_in_ms = atoi(optarg);
        break;
      default:
        std::printf("Usage: %s [-r ms] pid\n", argv[0]);
        exit(1);
    }
  }

  if (optind >= argc) {
    std::cerr << "Required process id" << std::endl;
    exit(1);
  }

  cmd_args->pid = atoi(argv[optind]);
}

int foo(int argc, char *argv[]) {
  CmdArgs cmd_args;
  process_args(argc, argv, &cmd_args);
  auto refresh_interval = std::chrono::milliseconds(cmd_args.refresh_interval_in_ms);

  char path[64];
  snprintf(path, sizeof(path), "/proc/%d/status", cmd_args.pid);
  struct stat buffer;

  FILE *procFd = std::fopen(path, "r");
  if (!procFd) {
    throw pascal::AppError("Failed to open file");
  }

  pascal::print_header_line();
  while (stat(path, &buffer) == 0) {
    const auto now1 = std::chrono::system_clock::now();
    const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now1.time_since_epoch()) % 1000;
    const auto timer = std::chrono::system_clock::to_time_t(now1);
    const auto bt = *std::localtime(&timer);
    std::cout << "\"" << std::put_time(&bt, "%FT%T") << "." << ms.count() << "\"";

    pascal::parse_proc_status_file(procFd);
    std::cout << std::endl;

    std::this_thread::sleep_for(refresh_interval);
    std::fseek(procFd, 0, SEEK_SET);
  }

  std::fclose(procFd);

  return 0;
}
