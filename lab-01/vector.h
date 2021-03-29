#ifndef VECTOR_H
#define VECTOR_H

#include "point.h"

namespace geometry {
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
}  // namespace geometry

#endif  // VECTOR_H
