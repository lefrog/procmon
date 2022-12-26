//
// Created by pascal-lambert on 22/12/22.
//

#include <gtest/gtest.h>
#include "GraphWindow.h"
#include "helpers.h"

class GraphWindowFixture : public ::testing::Test {
 protected:
  virtual void SetUp() {
  }

  virtual void TearDown() {
  }
};

TEST_F(GraphWindowFixture, WhenGettingXY) {
  using namespace std::chrono_literals;
  const auto from = get_time_from_string("2022-01-01T00:00:10");
  const auto elapse = 10s;

  std::vector<TimeSerieData> data = {
      TimeSerieData{0.0, from - 2s},
      TimeSerieData{0.5, from - 1s},
      TimeSerieData{0.75, from - 0s},
  };

  auto points = std::vector<LoadWidget::Point>();
  GraphWindow::get_xy_values(from, elapse, data, points);
  EXPECT_EQ(points.size(), 3);

  EXPECT_EQ(points[0].x, 0.8);
  EXPECT_EQ(points[0].y, 0.0);

  EXPECT_EQ(points[1].x, 0.9);
  EXPECT_EQ(points[1].y, 0.5);

  EXPECT_EQ(points[2].x, 1.0);
  EXPECT_EQ(points[2].y, 0.75);
}
