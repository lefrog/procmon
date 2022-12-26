//
// Created by pascal-lambert on 29/10/22.
//

#include "GraphController.h"

GraphController::GraphController() {
  start_time_ = std::chrono::system_clock::now();
}

GraphController::GraphController(std::chrono::time_point<std::chrono::system_clock> from)
    : start_time_(from) {}

void GraphController::add_value(
    double value,
    std::chrono::time_point<std::chrono::system_clock> at
) {
  values_.push_back(TimeSerieData{
      value,
      at
  });
}

void GraphController::select_values(
    std::vector<TimeSerieData> &result,
    const std::chrono::time_point<std::chrono::system_clock> &from
) {
  auto start = from - graph_max_time_span_;
  auto end = from;
  for (auto value : values_) {
    if (value.at > start && value.at <= end) {
      result.push_back(value);
    }
  }
}
