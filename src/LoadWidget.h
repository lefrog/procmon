//
// Created by pascal on 24/09/22.
//

#ifndef TEST_APP__LOADWIDGET_H_
#define TEST_APP__LOADWIDGET_H_

#include <gtkmm/drawingarea.h>
#include <vector>

class LoadWidget : public Gtk::DrawingArea {
 public:
  struct Point {
    double x;
    double y;
  };

 private:
  /**
   * Minimum possible values_ for the graph_.
   */
  double graph_min_value = std::numeric_limits<double>::max();
  /**
   * Maximum possible values_ for the graph_.
   */
  double graph_max_value = std::numeric_limits<double>::min();

  std::vector<Point> values;

  void draw_graph();

 protected:
  bool on_draw(const Cairo::RefPtr<::Cairo::Context> &cr) override;

 public:
  LoadWidget();
  ~LoadWidget() noexcept override;

  /**
   * Render points. Points are expected to be in a cartesian format where (0,0) is the lower left corner and
   * (1,1) is the upper right corner.
   *
   * @param points (x, y) values are expected to be between 0 and 1
   */
  void render_values(std::vector<Point> points);

  double get_min_value() {
    return graph_min_value;
  }
  void set_min_value(double value) {
    graph_min_value = value;
  }
  double get_max_value() {
    return graph_max_value;
  }
  void set_max_value(double value) {
    graph_max_value = value;
  }
};

#endif //TEST_APP__LOADWIDGET_H_
