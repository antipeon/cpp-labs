#ifndef POLYGON_H
#define POLYGON_H

#include "cycled_broken_line.h"

namespace geometry {
struct Polygon : protected CycledBrokenLine {
  explicit Polygon(const std::vector<Point>& points);
  //  virtual double CalculatePerimeter() const;
  using CycledBrokenLine::CalculatePerimeter;
  virtual double CalculateSquare() const;

  virtual ~Polygon() = default;
};
}  // namespace geometry

#endif  // POLYGON_H
