#include "vector.h"

#include <cmath>

using geometry::Vector;

double Vector::VectorProduct(const Vector& a) const {
  return -a.X() * y + a.Y() * x;
}

bool Vector::IsParallel(const Vector& a) const { return VectorProduct(a) == 0; }

double Vector::Length() const { return sqrt(x * x + y * y); }
