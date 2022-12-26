//
// Created by pascal on 24/09/22.
//

#include "LoadWidget.h"

LoadWidget::LoadWidget() {
}
LoadWidget::~LoadWidget() noexcept {
}

bool LoadWidget::on_draw(const Cairo::RefPtr<::Cairo::Context> &cr) {
  if (this->values.size() == 0) {
    return false;
  }

  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width() - 10;
  const int height = allocation.get_height() - 10;

  cr->set_line_width(1);
  cr->set_line_cap(Cairo::LINE_CAP_ROUND);
  cr->set_line_join(Cairo::LINE_JOIN_ROUND);

  const auto max_value = this->graph_max_value;
  auto calc_x = [&width](float value) { return width * value; };
  auto calc_y = [&height](float value) { return height * (1.0 - value); };

  cr->move_to(calc_x(0), calc_y(this->values[0].y));
  for (int i = 1; this->values.size() > i; i++) {
    auto x = calc_x(this->values[i].x);
    auto y = calc_y(this->values[i].y);
    cr->line_to(x, y);
  }
  cr->stroke();

  return true;
}

void LoadWidget::render_values(std::vector<Point> points) {
  values = points;
  queue_draw();
}
