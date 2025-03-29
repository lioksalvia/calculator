#include <iostream>
#include <format>

#include "calculator_api.hpp"

using namespace lioksalvia::calculator;

int main() {
  constexpr auto a = 1;
  constexpr auto b = 2;
  std::cout << std::format("{} + {} = {}", a, b, calculator::add(a, b)) << std::endl;
  return 0;
}