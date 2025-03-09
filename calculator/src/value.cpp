#include "../include/value.hpp"

#include <stdexcept>

using namespace calculator;

Value::Value(const Value& other) = default;

Value::Value(Value&& other) noexcept = default;

Value& Value::operator=(const Value& other) = default;

Value& Value::operator=(Value&& other) noexcept = default;

constexpr bool Value::isNumber() const {
  return std::holds_alternative<number_t>(value_);
}

constexpr bool Value::isVector() const {
  return std::holds_alternative<vector_t>(value_);
}

const value_t& Value::value() const { return value_; }


bool calculator::operator==(const Value& lhs, const Value& rhs) = default;

bool calculator::operator!=(const Value& lhs, const Value& rhs) = default;

std::common_comparison_category_t<
  std::compare_three_way_result_t<number_t>,
  std::compare_three_way_result_t<vector_t> > calculator::operator<=>(const Value& lhs, const Value& rhs) {
  if (!lhs.isNumber() || !rhs.isNumber()) {
    throw std::logic_error("Ordering comparisons are only supported for numbers.");
  }
  return lhs.value_ <=> rhs.value_;
}

Value calculator::operator+(const Value& lhs, const Value& rhs) { throw std::exception{}; }

Value calculator::operator-(const Value& lhs, const Value& rhs) { throw std::exception{}; }

Value calculator::operator*(const Value& lhs, const Value& rhs) { throw std::exception{}; }

Value calculator::operator/(const Value& lhs, const Value& rhs) { throw std::exception{}; }