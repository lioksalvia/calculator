#include <iostream>

#include "../../calculator/include/calculator.hpp"
#include "../../calculator/include/vector.hpp"

using namespace calculator;

int main() {
  std::vector<int> a{1, 2};
  Vector b(1, 2, 3);
  std::cout << (Vector(a) + Vector(b)) << std::endl;
  return 0;
}