#include "GraphWindow.h"

int main(int argc, char **argv) {
  auto app =
      Gtk::Application::create(argc,
                               argv,
                               "pascal.performance_monitoring",
                               Gio::APPLICATION_HANDLES_COMMAND_LINE
      );
  app->add_main_option_entry(
      Gio::Application::OPTION_TYPE_INT,
      "pids",
      '\0',
      "process id to monitor",
      "process id to monitor",
      Glib::OptionEntry::Flags::FLAG_IN_MAIN
  );
  GraphWindow window;
  return app->run(window);
}
