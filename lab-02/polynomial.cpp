#include "polynomial.h"

#include <algorithm>
#include <cstdio>
#include <iomanip>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>

Polynomial::Polynomial(const std::vector<double>& coefficients)
    : coefficients{coefficients}, degree(coefficients.size() - 1) {
  if (coefficients.empty()) {
    this->coefficients.push_back(0);
    degree = 0;
  }
}

Polynomial::Polynomial(
    const std::vector<std::pair<uint32_t, double>>& degrees_coefficients) {
  std::set<uint32_t> degrees;
  // check if there are same degrees
  for (const auto& item : degrees_coefficients) {
    const auto cur_degree = item.first;
    if (degrees.find(cur_degree) == degrees.end()) {
      degrees.insert(cur_degree);
    } else {
      throw std::runtime_error(
          "wrong input - "
          "can't construct polynomial");
    }
  }

  uint32_t max_degree = 0;
  for (const auto& item : degrees_coefficients) {
    const auto& cur_coefficient = item.second;
    if (cur_coefficient == 0) {
      continue;
    }
    const auto& cur_degree = item.first;
    max_degree = std::max(max_degree, cur_degree);
  }

  degree = max_degree;
  coefficients = std::vector<double>(degree + 1, 0);

  for (const auto& item : degrees_coefficients) {
    const auto cur_coefficient = item.second;
    if (cur_coefficient == 0) {
      continue;
    }
    const auto cur_degree = item.first;
    coefficients[cur_degree] = cur_coefficient;
  }
}

Polynomial::Polynomial(double number) : coefficients(1, number), degree(0) {}

Polynomial::Polynomial() : Polynomial(0) {}

void Polynomial::TidyIfZero() {
  for (auto it = std::rbegin(coefficients); it != std::rend(coefficients);
       ++it) {
    if (*it != 0) {
      return;
    }
    coefficients.pop_back();
    degree--;
  }
  if (coefficients.empty()) {
    *this = 0;
  }
}

double& Polynomial::operator[](size_t i) { return coefficients[i]; }

const double& Polynomial::operator[](size_t i) const { return coefficients[i]; }

bool operator==(const Polynomial& left_arg, const Polynomial& right_arg) {
  if (left_arg.degree != right_arg.degree) {
    return false;
  }
  return left_arg.coefficients == right_arg.coefficients;
}

bool operator!=(const Polynomial& left_arg, const Polynomial& right_arg) {
  return !(left_arg == right_arg);
}

Polynomial& Polynomial::operator+=(const Polynomial& right_arg) {
  for (size_t i = degree; i < right_arg.degree; ++i) {
    coefficients.push_back(0);
  }
  degree = std::max(degree, right_arg.degree);
  for (size_t i = 0; i < std::min(right_arg.degree, degree) + 1; ++i) {
    coefficients[i] += right_arg[i];
  }
  TidyIfZero();
  return *this;
}

const Polynomial operator+(const Polynomial& left_arg,
                           const Polynomial& right_arg) {
  auto result = left_arg;
  return result += right_arg;
}

Polynomial& Polynomial::operator-=(const Polynomial& right_arg) {
  for (size_t i = degree; i < right_arg.degree; ++i) {
    coefficients.push_back(0);
  }
  degree = std::max(degree, right_arg.degree);
  for (size_t i = 0; i < coefficients.size(); ++i) {
    coefficients[i] -= right_arg[i];
  }
  TidyIfZero();
  return *this;
}

const Polynomial operator-(const Polynomial& left_arg,
                           const Polynomial& right_arg) {
  auto result = left_arg;
  return result -= right_arg;
}

const Polynomial Polynomial::operator-() {
  auto result = *this;
  for (auto& coefficient : result.coefficients) {
    coefficient = -coefficient;
  }
  return result;
}

Polynomial& Polynomial::operator*=(double right_arg) {
  if (right_arg == 0) {
    return *this = 0;
  }
  for (auto& coefficient : coefficients) {
    coefficient *= right_arg;
  }
  return *this;
}

const Polynomial operator*(const Polynomial& left_arg, double right_arg) {
  auto result = left_arg;
  return result *= right_arg;
}

const Polynomial operator*(double left_arg, const Polynomial& right_arg) {
  auto result = right_arg;
  return result *= left_arg;
}

// multiplies polynomial by x^k
void Polynomial::ShiftModify(size_t k) {
  if (*this == 0) {
    return;
  }
  degree += k;
  coefficients.insert(std::begin(coefficients), k, 0);
}

Polynomial& Polynomial::operator*=(const Polynomial& right_arg) {
  Polynomial addition = *this;
  *this = Polynomial();
  for (size_t i = 0; i < right_arg.coefficients.size();
       ++i, addition.ShiftModify(1)) {
    *this += (addition * right_arg[i]);
  }
  TidyIfZero();
  return *this;
}

const Polynomial operator*(const Polynomial& left_arg,
                           const Polynomial& right_arg) {
  auto result = left_arg;
  return result *= right_arg;
}

Polynomial& Polynomial::operator/=(double right_arg) {
  if (right_arg == 0) {
    throw std::runtime_error("division_by_zero");
  }
  return *this *= (1. / right_arg);
}

const Polynomial operator/(const Polynomial& left_arg, double right_arg) {
  auto result = left_arg;
  return result /= right_arg;
}

// const Polynomial operator/(double left_arg, const Polynomial& right_arg) =
// delete;

const Polynomial Polynomial::Shift(size_t k) const {
  auto result = *this;
  result.ShiftModify(k);
  return result;
}

Polynomial& Polynomial::operator/=(const Polynomial& right_arg) {
  if (right_arg == 0) {
    throw std::runtime_error("division_by_zero");
  }
  if (right_arg.degree > degree) {
    return *this = 0;
  }
  std::vector<std::pair<uint32_t, double>> result_vector;
  auto cur_numerator = *this;
  while (cur_numerator.degree >= right_arg.degree) {
    const auto cur_coefficient =
        cur_numerator.coefficients.back() / right_arg.coefficients.back();
    const auto cur_degree = cur_numerator.degree - right_arg.degree;
    result_vector.push_back(std::make_pair(cur_degree, cur_coefficient));
    const auto bs = (right_arg.Shift(cur_degree) * cur_coefficient);
    cur_numerator -= bs;
  }
  return *this = Polynomial(result_vector);
}

const Polynomial operator/(const Polynomial& left_arg,
                           const Polynomial& right_arg) {
  auto result = left_arg;
  return result /= right_arg;
}

std::ostream& operator<<(std::ostream& out, const Polynomial& polynomial) {
  if (polynomial == 0) {
    return out << "0";
  }
  std::string output_string;
  for (int32_t cur_degree = polynomial.degree; cur_degree >= 0; --cur_degree) {
    if (polynomial[cur_degree] == 0) {
      continue;
    }
    char buffer[100];
    if (cur_degree == 0) {
      sprintf(buffer, "%.1lf", polynomial[cur_degree]);
    } else if (polynomial[cur_degree] == 1) {
      sprintf(buffer, "X^%d + ", cur_degree);
    } else {
      sprintf(buffer, "%.1lfX^%d + ", polynomial[cur_degree], cur_degree);
    }
    output_string += buffer;
  }

  // cut '+' at the end
  const auto output_string_length = output_string.length();
  const int32_t plus_pos = output_string_length - 2;
  if (plus_pos >= 0 && output_string[plus_pos] == '+') {
    output_string.resize(output_string_length - 3);
  }

  return out << output_string;
}

void AddNumber(Polynomial& polynomial, char operation, double coefficient) {
  if (operation == '+') {
    polynomial += coefficient;
  } else {
    polynomial -= coefficient;
  }
}

void AddMonomeOfDegreeOne(Polynomial& polynomial, char operation,
                          double coefficient) {
  const Polynomial monome({0, coefficient});
  if (operation == '+') {
    polynomial += monome;
  } else {
    polynomial -= monome;
  }
}

void AddMonome(Polynomial& polynomial, char operation,
               const Polynomial& monome) {
  if (operation == '+') {
    polynomial += monome;
  } else {
    polynomial -= monome;
  }
}

std::istream& operator>>(std::istream& in, Polynomial& polynomial) {
  const std::string incorrect_polynomial = "wrong polynomial input";
  polynomial = 0;

  std::string poly_unformatted;
  getline(in, poly_unformatted);
  std::istringstream read_polynomial(poly_unformatted);

  char next_operation = '+';
  while (!read_polynomial.eof()) {
    char next_char;
    while ((next_char = read_polynomial.get()) == ' ') {
      if (read_polynomial.eof()) {
        return in;
      }
    }

    if (next_char == '+' || next_char == '-') {
      next_operation = next_char;
      continue;
    }

    double next_coefficient;
    read_polynomial.unget();
    if (next_char == 'x' || next_char == 'X') {
      next_coefficient = 1;
    } else {
      // reading coefficient
      read_polynomial >> next_coefficient;
    }

    if (read_polynomial.eof()) {
      AddNumber(polynomial, next_operation, next_coefficient);

      return in;
    }

    // read 'x'
    read_polynomial.get(next_char);
    if (next_char != 'x' && next_char != 'X') {
      read_polynomial.unget();
      AddNumber(polynomial, next_operation, next_coefficient);

      continue;
    }

    // read '^' or eof
    read_polynomial.get(next_char);
    if (read_polynomial.eof()) {
      AddMonomeOfDegreeOne(polynomial, next_operation, next_coefficient);
      return in;
    }

    if (next_char != '^') {
      read_polynomial.unget();

      AddMonomeOfDegreeOne(polynomial, next_operation, next_coefficient);
      continue;
    }

    uint32_t degree;
    read_polynomial >> degree;
    const Polynomial monome({std::make_pair(degree, next_coefficient)});
    AddMonome(polynomial, next_operation, monome);
  }
  return in;
}
