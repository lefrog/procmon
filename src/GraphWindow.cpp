//
// Created by pascal on 01/10/22.
//

#include <cstdio>
#include <iostream>
#include "GraphWindow.h"
#include "LoadWidget.h"

GraphWindow::GraphWindow() {
  set_title("Performance Monitor");
  set_default_size(500, 500);
  set_border_width(5);

  graph_.set_min_value(0);
  graph_.set_max_value(1);

  add(graph_);
  show_all_children();
}

void GraphWindow::on_realize() {
  Widget::on_realize();
  std::puts("GraphWindow::on_realize");
  start_monitoring_();
}

void GraphWindow::start_monitoring_() {
//  worker_thread_ = new std::thread(&GraphWindow::manual_testing_, this);
  worker_thread_ = new std::thread(&GraphWindow::manual_testing_, this);
}

void GraphWindow::manual_testing_() {
  graph_controller_.add_value(0.0);
  double value;

  std::printf("Enter a value [%f, %f]:\n", graph_.get_min_value(), graph_.get_max_value());
  while (keep_running_) {
    std::cin >> value;
    std::printf("value: %f\n", value);
    graph_controller_.add_value(value);
    draw_graph_();
  }
}

void GraphWindow::monitor_process_() {

}


void GraphWindow::draw_graph_() {
  auto end = std::chrono::system_clock::now();
  std::vector<TimeSerieData> data;
  graph_controller_.select_values(data, end);

  std::vector<LoadWidget::Point> points;
  get_xy_values(end,
                graph_controller_.get_max_time_span(),
                data,
                points
  );

  graph_.render_values(points);
}

void GraphWindow::get_xy_values(const std::chrono::time_point<std::chrono::system_clock> now,
                                const std::chrono::seconds elapse,
                                const std::vector<TimeSerieData> &data,
                                std::vector<LoadWidget::Point> &points) {
  using sec = std::chrono::seconds;
  auto to_sec =
      [](std::chrono::time_point<std::chrono::system_clock> tp) { return std::chrono::time_point_cast<sec>(tp); };

  auto end = to_sec(now);
  auto beginning = end - elapse;

  for (auto value : data) {
    const auto at_in_sec = to_sec(value.at);
    double x = ((double) (at_in_sec - beginning).count()) / elapse.count();
    LoadWidget::Point point = {
        x,
        value.value
    };
    points.push_back(point);
  }
}
