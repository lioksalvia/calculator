#include <boost/test/unit_test.hpp>

#include "calculator.hpp"

using namespace lioksalvia::calculator;

BOOST_AUTO_TEST_SUITE(calculator_tests)

BOOST_AUTO_TEST_CASE(should_return_sum_when_adding_two_numbers) {
  // Arrange
  struct TestCase {
    int a, b;
    int expected;
  };

  const std::vector<TestCase> test_cases{{2, 3, 5}, {-1, 1, 0}, {0, 0, 0}, {-5, -7, -12}};

  // Act, Assert
  for (const auto &[a, b, expected]: test_cases) {
    BOOST_TEST(calculator::add(a, b) == expected);
  }
}

BOOST_AUTO_TEST_SUITE_END()