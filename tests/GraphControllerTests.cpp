//
// Created by pascal-lambert on 29/10/22.
//

#include <gtest/gtest.h>
#include "GraphController.h"
#include "helpers.h"

class GraphControllerFixture : public ::testing::Test {
 protected:
  virtual void SetUp() {
    using namespace std::chrono_literals;

    graph_controller_ = new GraphController();
    graph_controller_->set_max_time_span(3s);

    graph_controller_->add_value(0.1, from_ + 1s);
    graph_controller_->add_value(0.2, from_ + 2s);
    graph_controller_->add_value(0.3, from_ + 3s);
    graph_controller_->add_value(0.4, from_ + 4s);
    graph_controller_->add_value(0.5, from_ + 5s);
    graph_controller_->add_value(0.6, from_ + 6s);
  }

  virtual void TearDown() {
    delete graph_controller_;
  }

  const std::chrono::time_point<std::chrono::system_clock> from_ = get_time_from_string("2022-01-01T00:00:00");

  GraphController *graph_controller_;
};

TEST_F(GraphControllerFixture, WhenSelectingValues) {
  using namespace std::chrono_literals;
  EXPECT_EQ(graph_controller_->get_max_time_span(), 3s);

  const auto from = get_time_from_string("2022-01-01T00:00:05");
  std::vector<TimeSerieData> result;
  graph_controller_->select_values(result, from);
  EXPECT_EQ(result.size(), 3) << "it should have find 3 elements";
  EXPECT_EQ(result[0].value, 0.3) << "it should have find the 3rd elements";
  EXPECT_EQ(result[1].value, 0.4) << "it should have find the 4th elements";
  EXPECT_EQ(result[2].value, 0.5) << "it should have find the 5th elements";
}
