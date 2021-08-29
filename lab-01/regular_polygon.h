#ifndef REGULARPOLYGON_H
#define REGULARPOLYGON_H

#include "polygon.h"

namespace geometry {
struct RegularPolygon final : protected Polygon {
  explicit RegularPolygon(const std::vector<Point>& points);
  double CalculateSquare() const override;
  double CalculatePerimeter() const override;

 private:
  double edge_length;
};
}  // namespace geometry

#endif  // REGULARPOLYGON_H
