#include "triangle.h"

#include <cmath>
#include <stdexcept>

#include "vector.h"

using geometry::Triangle;

Triangle::Triangle(const std::vector<Point>& points) : Polygon(points) {
  if (points.size() != 3) {
    throw std::runtime_error("not a triangle");
  }
}

double Triangle::CalculateSquare() const {
  const Point& fixed = points[0];
  const Vector a(fixed, points[1]);
  const Vector b(fixed, points[2]);
  return std::abs(a.VectorProduct(b)) / 2.;
}
