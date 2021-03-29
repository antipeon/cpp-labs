#include "broken_line.h"

using geometry::BrokenLine;

double BrokenLine::CalculatePerimeter() const {
  double perimeter = 0;
  for (size_t i = 0; i < points.size() - 1; ++i) {
    perimeter += points[i].DistanceTo(points[i + 1]);
  }
  return perimeter;
}
