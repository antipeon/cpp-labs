#include "regular_polygon.h"

#include <cmath>
#include <stdexcept>

#include "vector.h"

using geometry::RegularPolygon;

RegularPolygon::RegularPolygon(const std::vector<Point>& points)
    : Polygon(points) {
  const auto points_number = points.size();

  edge_length = Vector(points[0], points[1]).Length();
  for (size_t i = 0; i < points_number; ++i) {
    const double cur_length =
        Vector(points[i], points[(i + 1) % points_number]).Length();
    if (edge_length != cur_length) {
      throw std::runtime_error("not regular polygon");
    }
  }
}

double RegularPolygon::CalculatePerimeter() const {
  return points.size() * edge_length;
}

double RegularPolygon::CalculateSquare() const {
  const double pi = M_PI;
  const int32_t points_number = points.size();
  const double R = edge_length / 2 / std::sin(pi / points_number);
  const double r = R * std::cos(pi / points_number);

  return CalculatePerimeter() * r / 2;
}
