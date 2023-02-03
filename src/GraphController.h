//
// Created by pascal-lambert on 29/10/22.
//

#ifndef PROCMON_SRC_GRAPHCONTROLLER_H_
#define PROCMON_SRC_GRAPHCONTROLLER_H_

#include <chrono>
#include <vector>

struct TimeSerieData {
  double value;
  std::chrono::time_point<std::chrono::system_clock> at;
};

class GraphController {
  /**
   * Time at which the controller start. This is 99% always now but this can be used for automated testing.
   */
  std::chrono::time_point<std::chrono::system_clock> start_time_;

  /**
  * How many seconds worth of data are we rendering.
  */
  std::chrono::seconds graph_max_time_span_ = std::chrono::minutes(2);

  /**
   * assume values_ are already sorted by time ascending.
   */
  std::vector<TimeSerieData> values_;

 public:
  GraphController();
  GraphController(std::chrono::time_point<std::chrono::system_clock> from);

  void set_max_time_span(std::chrono::seconds max_seconds) {
    graph_max_time_span_ = max_seconds;
  }
  std::chrono::seconds get_max_time_span() {
    return graph_max_time_span_;
  }

  void add_value(
      double value = 0.0,
      std::chrono::time_point<std::chrono::system_clock> at = std::chrono::system_clock::now()
  );

  /**
   * The function will search data between (from - graph_max_time_span_) to (from).
   *
   * @param result
   * @param from
   */
  void select_values(
      std::vector<TimeSerieData> &result,
      const std::chrono::time_point<std::chrono::system_clock> &from = std::chrono::system_clock::now()
  );
};

#endif //PROCMON_SRC_GRAPHCONTROLLER_H_
