#include <iostream>

#include "../../calculator/include/calculator.hpp"
#include "../../calculator/include/value.hpp"

using namespace calculator;

int main() {
  std::cout << (Value(std::vector<int>{3}) == Value(4)) << std::endl;
  return 0;
}