#include <iostream>
#include <vector>

#include "primitive_algorithms.h"


using kinda_std::LessThan;
using kinda_std::all_of;



void TestAllOf() {
  int32_t constant = 6;
  std::vector<int32_t> sample = {0, 11, 12, 8, 4};
  std::cout << all_of(sample.begin(),
                      sample.end(),
                      LessThan(constant)) <<
               std::endl;
}

int main()
{
  TestAllOf();
//  std::cout << "Hello World!" << std::endl;
  return 0;
}
