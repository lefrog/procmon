#include <gtkmm.h>
#include "GraphWindow.h"

class MyOptionGroup : public Glib::OptionGroup {
 public:
  MyOptionGroup();

  bool show_gui_;
  int pid_;
};

MyOptionGroup::MyOptionGroup() :
    Glib::OptionGroup("procmon", "procmon application specific options", "bla bla bla"),
    show_gui_(false) {
  Glib::OptionEntry guiEntry;
  guiEntry.set_long_name("gui");
  guiEntry.set_description("show the gui");
  add_entry(guiEntry, show_gui_);

  Glib::OptionEntry pidEntry;
  pidEntry.set_long_name("pid");
  pidEntry.set_description("process id to monitor");
  add_entry(pidEntry, pid_);
}

int main(int argc, char **argv) {
  Glib::OptionContext context;
  MyOptionGroup option_group;
  context.set_main_group(option_group);
  context.parse(argc, argv);

  auto app =
      Gtk::Application::create(argc,
                               argv,
                               "pascal.performance_monitoring"
      );
  GraphWindow window;
  return app->run(window);
}
