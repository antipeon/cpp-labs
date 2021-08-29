#include <iostream>
#include <iterator>
#include <vector>

#include "primitive_algorithms.h"

using kinda_std::isEqual;
using kinda_std::LessThan;

void TestAllOf() {
  const int32_t constant = 6;
  const std::vector<int32_t> sample = {0, 11, 12, 8, 4};
  std::cout << "Predicate is "
            << (kinda_std::all_of(sample.cbegin(), sample.cend(),
                                  LessThan(constant))
                    ? "true"
                    : "false")
            << " for the range" << std::endl;
}

void TestFindNot() {
  const int32_t constant = 0;
  const std::vector<int32_t> sample = {0, 0, 0, 8, 4};
  const auto pos =
      kinda_std::find_not(sample.cbegin(), sample.cend(), constant);

  std::cout << "Distance from first to first not equal is: "
            << std::distance(sample.cbegin(), pos) << std::endl;
}

void TestFindBackward() {
  const int32_t constant = 0;
  const std::vector<int32_t> sample = {0, 0, 0, 8, 4};
  const auto pos =
      kinda_std::find_backward(sample.cbegin(), sample.cend(), constant);
  std::cout << "Distance from first to first equal from backward is: "
            << std::distance(sample.cbegin(), pos) << std::endl;
}

void TestIsPalindrome() {
  std::vector<int32_t> sample = {0, 1, 2, 2, 1, 0};
  const auto is_palindrome = kinda_std::is_palindrome(
      sample.cbegin(), sample.cend(), isEqual<int32_t>());
  std::cout << (is_palindrome ? "It is" : "It is not") << " a palindrome"
            << std::endl;
}

int main() {
  TestAllOf();
  TestFindNot();
  TestFindBackward();
  TestIsPalindrome();
  return 0;
}
