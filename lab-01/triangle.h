#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "polygon.h"

namespace geometry {
struct Triangle final : protected Polygon {
  explicit Triangle(const std::vector<Point>& points);
  double CalculateSquare() const override;
  using Polygon::CalculatePerimeter;
};
}  // namespace geometry

#endif  // TRIANGLE_H
