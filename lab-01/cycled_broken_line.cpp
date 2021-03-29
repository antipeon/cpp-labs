#include "cycled_broken_line.h"

using geometry::CycledBrokenLine;

double CycledBrokenLine::CalculatePerimeter() const {
  double perimeter = BrokenLine::CalculatePerimeter();
  const auto first_point = points[0];
  const auto last_point = points[points.size() - 1];
  perimeter += first_point.DistanceTo(last_point);
  return perimeter;
}
