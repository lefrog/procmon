//
// Created by pascal-lambert on 26/12/22.
//

#include <chrono>
#include <string>

std::chrono::time_point<std::chrono::system_clock> get_time_from_string(const std::string &time_string) {
  struct tm tm = {};
  strptime(time_string.c_str(), "%Y-%m-%dT%H:%M:%S", &tm);
  auto tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));
  return tp;
}
