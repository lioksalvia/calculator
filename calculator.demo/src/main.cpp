#include <iostream>

#include "../../calculator/include/calculator.hpp"
#include "../../calculator/include/value.hpp"

using namespace calculator;

int main() {
  std::vector<int> a{1, 2};
  vector_t b{1, a, 3};
  std::cout << (Value(a) + Value(b)) << std::endl;
  return 0;
}