#include "GraphWindow.h"

int main(int argc, char **argv) {
  auto app = Gtk::Application::create(argc, argv, "pascal.performance_monitoring");
  GraphWindow window;
  return app->run(window);
}
