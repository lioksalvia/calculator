#include <format>
#include <sstream>

#include "../include/calculator_error.hpp"
#include "../include/value.hpp"

using namespace calculator;

Value::Value(number_t number) {
  value_ = std::make_unique<value_t>(number);
}

Value::Value(const vector_t& vector) {
  value_ = std::make_unique<value_t>(vector);
}

Value::Value(vector_t&& vector) {
  value_ = std::make_unique<value_t>(std::move(vector));
}

Value::Value(const Value& other) {
  value_ = std::make_unique<value_t>(*other.value_);
}

Value::Value(Value&& other) noexcept : value_(std::move(other.value_)) {
  other.value_ = nullptr;
}

Value& Value::operator=(const Value& other) {
  if (this != &other) {
    value_ = std::make_unique<value_t>(*other.value_);
  }
  return *this;
}

Value& Value::operator=(Value&& other) noexcept {
  value_ = std::move(other.value_);
  other.value_ = nullptr;
  return *this;
}

std::string Value::ToString(std::string_view delimiter, std::string_view number_format) const {
  if (isNumber()) {
    const std::string format = std::format("{{:{}f}}", number_format);
    return std::vformat(format, std::make_format_args(std::get<number_t>(*value_)));
  }

  std::ostringstream os;
  os << "[";
  const auto& vec = std::get<vector_t>(*value_);
  for (size_t i = 0, n = vec.size(); i < n; ++i) {
    if (i != 0) {
      os << delimiter;
    }
    os << vec[i].ToString(delimiter, number_format);
  }
  os << "]";
  return os.str();
}

bool Value::isNumber() const {
  return std::holds_alternative<number_t>(*value_);
}

bool Value::isVector() const {
  return std::holds_alternative<vector_t>(*value_);
}

const value_t& Value::value() const { return *value_; }


bool calculator::operator==(const Value& lhs, const Value& rhs) {
  if (lhs.value_->index() != rhs.value_->index()) {
    throw std::system_error(CalculatorErrc::TypeMismatch);
  }

  return *lhs.value_ == *rhs.value_;
}

bool calculator::operator!=(const Value& lhs, const Value& rhs) {
  return !(lhs == rhs);
}

bool calculator::operator<(const Value& lhs, const Value& rhs) {
  if (!lhs.isNumber() || !rhs.isNumber()) {
    throw std::system_error(CalculatorErrc::TypeMismatch);
  }
  return *lhs.value_ < *rhs.value_;
}

bool calculator::operator<=(const Value& lhs, const Value& rhs) {
  return lhs < rhs || lhs == rhs;
}

bool calculator::operator>(const Value& lhs, const Value& rhs) {
  return !(lhs <= rhs);
}

bool calculator::operator>=(const Value& lhs, const Value& rhs) {
  return !(rhs < lhs);
}

Value calculator::operator+(const Value& lhs, const Value& rhs) {
  if (lhs.isNumber()) {
    if (rhs.isNumber()) {
      return Value(std::get<number_t>(*lhs.value_) + std::get<number_t>(*rhs.value_));
    }
    auto value_to_add = Value(std::get<number_t>(*lhs.value_));
    auto temp = std::get<vector_t>(*rhs.value_);
    for (auto& val : temp) {
      val += value_to_add;
    }
    return Value(std::move(temp));
  }
  if (rhs.isNumber()) {
    auto value_to_add = Value(std::get<number_t>(*rhs.value_));
    auto temp = std::get<vector_t>(*lhs.value_);
    for (auto& val : temp) {
      val += value_to_add;
    }
    return Value(std::move(temp));
  }
  auto& vec1 = std::get<vector_t>(*lhs.value_);
  auto& vec2 = std::get<vector_t>(*rhs.value_);
  auto& longer_vec = vec1.size() >= vec2.size() ? vec1 : vec2;
  const auto& shorter_vec = &longer_vec == &vec1 ? vec2 : vec1;

  vector_t temp = std::move(longer_vec);
  for (size_t i = 0, n = shorter_vec.size(); i < n; ++i) {
    temp[i] += shorter_vec[i];
  }
  return Value(std::move(temp));
}

Value& calculator::operator+=(Value& lhs, const Value& rhs) {
  return lhs = lhs + rhs;
}

Value calculator::operator-(const Value& lhs, const Value& rhs) {
  throw std::system_error(CalculatorErrc::NotImplemented);
}

Value& calculator::operator-=(Value& lhs, const Value& rhs) {
  return lhs = lhs - rhs;
}

Value calculator::operator*(const Value& lhs, const Value& rhs) {
  throw std::system_error(CalculatorErrc::NotImplemented);
}

Value& calculator::operator*=(Value& lhs, const Value& rhs) {
  return lhs = lhs * rhs;
}

Value calculator::operator/(const Value& lhs, const Value& rhs) {
  throw std::system_error(CalculatorErrc::NotImplemented);
}

Value& calculator::operator/=(Value& lhs, const Value& rhs) {
  return lhs = lhs / rhs;
}

std::ostream& calculator::operator<<(std::ostream& os, const Value& value) {
  return os << value.ToString();
}