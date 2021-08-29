#include "polygon.h"

#include <stdexcept>
#include <string>

#include "vector.h"

using geometry::Polygon;

Polygon::Polygon(const std::vector<Point>& points) : CycledBrokenLine(points) {
  const auto points_number = points.size();
  const std::string error_message_not_polygon = "not polygon";
  // not enough points
  if (points_number < 3) {
    throw std::runtime_error(error_message_not_polygon + " - too few points");
  }

  // check if convex
  double prev_vector_product = 0;
  for (size_t i = 0; i < points_number; ++i) {
    const Vector a(points[i], points[(i + 1) % points_number]);
    const Vector b(points[(i + 1) % points_number],
                   points[(i + 2) % points_number]);
    const auto cur_vector_product = a.VectorProduct(b);
    if (cur_vector_product * prev_vector_product < 0) {
      throw std::runtime_error(error_message_not_polygon + " - not convex");
    }
    prev_vector_product = cur_vector_product;
  }
}

double Polygon::CalculateSquare() const {
  double square = 0;

  const auto points_number = points.size();
  const Point& fixed = points[0];
  for (size_t i = 1; i < points_number - 1; ++i) {
    const Vector a(fixed, points[i]);
    const Vector b(fixed, points[i + 1]);
    square += std::abs(a.VectorProduct(b)) / 2.;
  }

  return square;
}
