#ifndef POINT_H
#define POINT_H

namespace geometry {
struct Point {
  Point(double x, double y) : x{x}, y{y} {}
  double X() const { return x; }
  double Y() const { return y; }

  double DistanceTo(const Point& to) const;

 private:
  double x;
  double y;
};
}  // namespace geometry

#endif  // POINT_H
