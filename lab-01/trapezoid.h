#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "polygon.h"

namespace geometry {
struct Trapezoid final : protected Polygon {
  explicit Trapezoid(const std::vector<Point>& points);
  double CalculateSquare() const override;
  using Polygon::CalculatePerimeter;
};
}  // namespace geometry

#endif  // TRAPEZOID_H
