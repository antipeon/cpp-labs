#include <iostream>

#include "polynomial.h"

void TestAddition(const Polynomial& polynomial1,
                  const Polynomial& polynomial2) {
  std::cout << "First polynomial is: " << polynomial1 << std::endl;
  std::cout << "Second polynomial is: " << polynomial2 << std::endl;
  std::cout << "Result of addition is: " << polynomial1 + polynomial2
            << std::endl;
  std::cout << std::endl;
}

void TestSubtraction(const Polynomial& polynomial1,
                     const Polynomial& polynomial2) {
  std::cout << "First polynomial is: " << polynomial1 << std::endl;
  std::cout << "Second polynomial is: " << polynomial2 << std::endl;
  std::cout << "Result of subtraction is: " << polynomial1 - polynomial2
            << std::endl;
  std::cout << std::endl;
}

void TestDivision(const Polynomial& polynomial, const Polynomial& divisor) {
  std::cout << "Polynomial is: " << polynomial << std::endl;
  std::cout << "Divisor is: " << divisor << std::endl;
  std::cout << "Result of division is: " << polynomial / divisor << std::endl;
  std::cout << std::endl;
}

void TestMultiplication(const Polynomial& polynomial1,
                        const Polynomial& polynomial2) {
  std::cout << "First polynomial is: " << polynomial1 << std::endl;
  std::cout << "Second polynomial is: " << polynomial2 << std::endl;
  std::cout << "Result of multiplication is: " << polynomial1 * polynomial2
            << std::endl;
  std::cout << std::endl;
}

void TestInput() {
  Polynomial polynome;
  std::cin >> polynome;
  std::cout << "This is the polynome you input: " << polynome << std::endl;
  std::cout << std::endl;
}

int main() {
  const Polynomial polynomial1({1, -2, 1});
  const Polynomial divisor({-1, 1});
  const Polynomial polynomial2({6, 5, 1});
  //  const Polynomial polynomial2({-1, 0, 1});

  // polynomial3 = polynomial2
  const Polynomial polynomial3(
      {std::make_pair(1, 5.), std::make_pair(2, 1.), std::make_pair(0, 6.)});

  TestDivision(polynomial1, divisor);
  TestMultiplication(polynomial1, polynomial2);
  TestMultiplication(polynomial1, polynomial3);
  TestInput();

  const Polynomial polynomial4 = -4;
  const Polynomial polynomial5({std::make_pair(100, -4)});
  TestAddition(polynomial4, polynomial5);

  const Polynomial polynomial6({-5, 1.});
  const Polynomial polynomial7({std::make_pair(1, 1.), std::make_pair(2, -5.)});
  TestSubtraction(polynomial6, polynomial7);

  //  const Polynomial should_this_be_banned = 'a';

  return 0;
}
