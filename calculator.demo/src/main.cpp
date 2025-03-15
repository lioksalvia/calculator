#include <iostream>

#include "../../calculator/include/vector.hpp"

using namespace calculator;

int main() {
  const std::vector a{1, 2};
  const auto b = Vector(1, Vector(a), Vector(std::vector{3}));
  std::cout << (Vector(a) + b) << std::endl;
  return 0;
}