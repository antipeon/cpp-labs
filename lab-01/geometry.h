#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <cmath>
#include <vector>

struct Point {
  Point(double x, double y) : x{x}, y{y} {}
  double X() const { return x; }
  double Y() const { return y; }

  double DistanceTo(const Point& to) const;

 private:
  double x;
  double y;
};

struct BrokenLine {
  explicit BrokenLine(const std::vector<Point>& points) : points(points) {}
  virtual double CalculatePerimeter() const;

  virtual ~BrokenLine() = default;

  // generated by default
  //  BrokenLine(const BrokenLine& constuct_from) { points =
  //  constuct_from.points; } BrokenLine& operator=(const BrokenLine& right_arg)
  //  {
  //    points = right_arg.points;
  //    return *this;
  //  }

 protected:
  std::vector<Point> points;
};

struct CycledBrokenLine : protected BrokenLine {
  explicit CycledBrokenLine(const std::vector<Point>& points)
      : BrokenLine(points) {}
  double CalculatePerimeter() const override;

  virtual ~CycledBrokenLine() = default;
};

struct Vector {
  Vector(const Point& a, const Point& b) : x(b.X() - a.X()), y(b.Y() - a.Y()) {}
  double X() const { return x; }
  double Y() const { return y; }
  double VectorProduct(const Vector& a) const;
  bool IsParallel(const Vector& a) const;
  double Length() const;

 private:
  double x;
  double y;
};

struct Polygon : protected CycledBrokenLine {
  explicit Polygon(const std::vector<Point>& points);
//  virtual double CalculatePerimeter() const;
  using CycledBrokenLine::CalculatePerimeter;
  virtual double CalculateSquare() const;

  virtual ~Polygon() = default;
};

struct Triangle final : protected Polygon {
  explicit Triangle(const std::vector<Point>& points);
  double CalculateSquare() const override;
  using Polygon::CalculatePerimeter;
};

struct Trapezoid final : protected Polygon {
  explicit Trapezoid(const std::vector<Point>& points);
  double CalculateSquare() const override;
  using Polygon::CalculatePerimeter;
};

struct RegularPolygon final : protected Polygon {
  explicit RegularPolygon(const std::vector<Point>& points);
  double CalculateSquare() const override;
  double CalculatePerimeter() const override;

 private:
  double edge_length;
};

#endif  // GEOMETRY_H
