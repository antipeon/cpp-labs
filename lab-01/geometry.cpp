#include "geometry.h"

#include <cmath>
#include <stdexcept>
#include <string>

double Point::DistanceTo(const Point& to) const {
  const double diff_x = x - to.X();
  const double diff_y = y - to.Y();
  return sqrt(diff_x * diff_x + diff_y * diff_y);
}

double BrokenLine::CalculatePerimeter() const {
  double perimeter = 0;
  for (size_t i = 0; i < points.size() - 1; ++i) {
    perimeter += points[i].DistanceTo(points[i + 1]);
  }
  return perimeter;
}

double CycledBrokenLine::CalculatePerimeter() const {
  double perimeter = BrokenLine::CalculatePerimeter();
  const auto first_point = points[0];
  const auto last_point = points[points.size() - 1];
  perimeter += first_point.DistanceTo(last_point);
  return perimeter;
}

double Vector::VectorProduct(const Vector& a) const {
  return -a.X() * y + a.Y() * x;
}

bool Vector::IsParallel(const Vector& a) const { return VectorProduct(a) == 0; }

double Vector::Length() const { return sqrt(x * x + y * y); }

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

double Polygon::CalculatePerimeter() const {
  return CycledBrokenLine::CalculatePerimeter();
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

Trapezoid::Trapezoid(const std::vector<Point>& points) : Polygon(points) {
  const auto points_number = points.size();
  if (points_number != 4) {
    throw std::runtime_error("not a schizoid, btw trapezoids are gay");
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
