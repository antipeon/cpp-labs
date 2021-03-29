#include "trapezoid.h"

#include <stdexcept>

#include "vector.h"

using geometry::Trapezoid;

Trapezoid::Trapezoid(const std::vector<Point>& points) : Polygon(points) {
  const auto points_number = points.size();
  if (points_number != 4) {
    throw std::runtime_error("not a trapezoid");
  }
  // make sure segments [1,2] and [3, 4] are basises of trapezoid
  const Vector a(points[2], points[3]);
  const Vector b(points[4], points[1]);
  if (a.IsParallel(b)) {
    const auto save = points[0];
    for (int32_t i = points_number - 1; i >= 1; --i) {
      this->points[(i + 1) % points_number] = this->points[i];
    }
    this->points[1] = save;
  }
}

double Trapezoid::CalculateSquare() const {
  const Vector base_one(points[3], points[2]);
  const Vector base_two(points[0], points[1]);
  const Vector edge(points[3], points[1]);
  const auto sinus = std::abs(base_one.VectorProduct(edge)) /
                     base_one.Length() / edge.Length();
  const auto height = sinus * edge.Length();
  return height / 2. * (base_one.Length() + base_two.Length());
}
