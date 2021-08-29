#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <cstdint>
#include <fstream>
#include <string>
#include <utility>
#include <vector>

class Polynomial {
 public:
  explicit Polynomial(
      const std::vector<std::pair<uint32_t, double>>& degrees_coefficients);
  explicit Polynomial(const std::vector<double>& coefficients);
  Polynomial(double number);
  //  Polynomial(char) = delete;
  Polynomial();

  double& operator[](size_t i);
  const double& operator[](size_t i) const;
  friend bool operator==(const Polynomial& left_arg,
                         const Polynomial& right_arg);

  Polynomial& operator+=(const Polynomial& right_arg);

  Polynomial& operator-=(const Polynomial& arg);

  const Polynomial operator-();

  Polynomial& operator*=(double right_arg);
  Polynomial& operator*=(const Polynomial& right_arg);

  Polynomial& operator/=(double right_arg);
  Polynomial& operator/=(const Polynomial& right_arg);

  friend std::ostream& operator<<(std::ostream& out,
                                  const Polynomial& polynomial);

 private:
  std::vector<double> coefficients;
  uint32_t degree;

  const Polynomial Shift(size_t k) const;
  void ShiftModify(size_t k);
  void TidyIfZero();
};

bool operator!=(const Polynomial& left_arg, const Polynomial& right_arg);

const Polynomial operator+(const Polynomial& left_arg,
                           const Polynomial& right_arg);

const Polynomial operator-(const Polynomial& left_arg,
                           const Polynomial& right_arg);

const Polynomial operator*(const Polynomial& left_arg, double right_arg);

const Polynomial operator*(double left_arg, const Polynomial& right_arg);

const Polynomial operator*(const Polynomial& left_arg,
                           const Polynomial& right_arg);

const Polynomial operator/(const Polynomial& left_arg, double right_arg);

const Polynomial operator/(const Polynomial& left_arg,
                           const Polynomial& right_arg);

std::istream& operator>>(std::istream& in, Polynomial& polynomial);

#endif  // POLYNOMIAL_H
