#include <iostream>
#include <iterator>
#include <vector>

#include "primitive_algorithms.h"

using kinda_std::isEqual;
using kinda_std::LessThan;

void TestAllOf() {
  int32_t constant = 6;
  std::vector<int32_t> sample = {0, 11, 12, 8, 4};
  std::cout << kinda_std::all_of(sample.cbegin(), sample.cend(),
                                 LessThan(constant))
            << std::endl;
}

void TestFindNot() {
  int32_t constant = 0;
  std::vector<int32_t> sample = {0, 0, 0, 8, 4};
  const auto pos =
      kinda_std::find_not(sample.cbegin(), sample.cend(), constant);

  std::cout << std::distance(sample.cbegin(), pos) << std::endl;
}

void TestFindBackward() {
  int32_t constant = 0;
  std::vector<int32_t> sample = {0, 0, 0, 8, 4};
  const auto pos =
      kinda_std::find_backward(sample.cbegin(), sample.cend(), constant);
  std::cout << std::distance(sample.cbegin(), pos) << std::endl;
}

void TestIsPalindrome() {
  std::vector<int32_t> sample = {0, 1, 2, 2, 1, 0};
  const auto is_palindrome = kinda_std::is_palindrome(
      sample.cbegin(), sample.cend(), isEqual<int32_t>());
  std::cout << (is_palindrome ? "it is" : "it is not") << " a palindrome"
            << std::endl;
}

int main() {
  TestAllOf();
  TestFindNot();
  TestFindBackward();
  TestIsPalindrome();
  return 0;
}
