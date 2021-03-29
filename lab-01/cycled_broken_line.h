#ifndef CYCLEDBROKENLINE_H
#define CYCLEDBROKENLINE_H

#include <vector>

#include "broken_line.h"
#include "point.h"

namespace geometry {
struct CycledBrokenLine : protected BrokenLine {
  explicit CycledBrokenLine(const std::vector<Point>& points)
      : BrokenLine(points) {}
  double CalculatePerimeter() const override;

  virtual ~CycledBrokenLine() = default;
};
}  // namespace geometry

#endif  // CYCLEDBROKENLINE_H
