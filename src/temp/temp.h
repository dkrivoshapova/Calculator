#pragma once

namespace s21 {

struct Plot {
  double x_min;
  double x_max;
  double y_min;
  double y_max;
  double scale;
  Plot(double min_x = -10, double max_x = 10, double min_y = -10,
       double max_y = 10, double move = 0.5)
      : x_min(min_x), x_max(max_x), y_min(min_y), y_max(max_y), scale(move) {}
};

}  // namespace s21
