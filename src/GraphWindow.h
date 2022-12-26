//
// Created by pascal on 01/10/22.
//

#ifndef PROCMON_SRC_GRAPHWINDOW_H_
#define PROCMON_SRC_GRAPHWINDOW_H_

#include <thread>
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/progressbar.h>
#include "LoadWidget.h"
#include "GraphController.h"

class GraphWindow : public Gtk::Window {
 public:
  GraphWindow();

  /**
   * Take some raw data (time and value) and convert to a cartesian (x,y) where
   * x: time and y: is value.
   * Both x and y value should be between 0 and 1.
   * Coordinate (0,0) is the lower left corner and (1,1) is the upper right corner.
   *
   * @param now
   * @param elapse
   * @param data
   * @param points return the list of data that matches in (x,y) format
   */
  static void get_xy_values(const std::chrono::time_point<std::chrono::system_clock> now,
                            const std::chrono::seconds elapse,
                            const std::vector<TimeSerieData> &data,
                            std::vector<LoadWidget::Point> &points);
 protected:
  void on_realize() override;

 private:
  GraphController graph_controller_;
  LoadWidget graph_;
  std::thread* worker_thread_;
  bool keep_running_ = true;
  /**
   * Process ids to monitor
   */
  std::vector<int> pids;
  void start_monitoring_();
  void manual_testing_();
  void monitor_process_();
  void draw_graph_();
};

#endif //PROCMON_SRC_GRAPHWINDOW_H_
