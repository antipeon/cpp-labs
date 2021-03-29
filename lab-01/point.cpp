#include "point.h"

#include <cmath>

using geometry::Point;

double Point::DistanceTo(const Point& to) const {
  const double diff_x = x - to.X();
  const double diff_y = y - to.Y();
  return sqrt(diff_x * diff_x + diff_y * diff_y);
}
