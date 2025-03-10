#ifndef CALCULATOR_VALUE_HPP_
#define CALCULATOR_VALUE_HPP_

#include <concepts>
#include <variant>
#include <vector>
#include <memory>

namespace calculator {

using number_t = long double;
class Value;
using vector_t = std::vector<Value>;
using value_t = std::variant<number_t, vector_t>;

class Value {
public:
  explicit Value(number_t number);

  explicit Value(const vector_t& vector);

  explicit Value(vector_t&& vector);

  template <typename TNumber> requires std::convertible_to<TNumber, number_t>
  Value(const TNumber& number) : Value(static_cast<number_t>(number)) {}

  template <typename TValue> requires std::convertible_to<TValue, Value>
  Value(const std::vector<TValue>& vector) : Value(vector_t{}) {
    vector_t vec;
    vec.reserve(vector.size());
    for (const auto& v : vector) {
      vec.emplace_back(v);
    }
    *value_ = vec;
  }

  Value(const Value& other);

  Value(Value&& other)
    noexcept;

  Value& operator=(const Value& other);

  Value& operator=(Value&& other) noexcept;

  [[nodiscard]] std::string ToString(std::string_view delimiter = ", ", std::string_view number_format = ".6") const;

  [[nodiscard]] bool isNumber() const;

  [[nodiscard]] bool isVector() const;

  [[nodiscard]] const value_t& value() const;

private:
  std::unique_ptr<value_t> value_;

  friend bool operator==(const Value& lhs, const Value& rhs);

  friend bool operator!=(const Value& lhs, const Value& rhs);

  friend bool operator<(const Value& lhs, const Value& rhs);

  friend bool operator>(const Value& lhs, const Value& rhs);

  friend bool operator<=(const Value& lhs, const Value& rhs);

  friend bool operator>=(const Value& lhs, const Value& rhs);

  friend Value operator+(const Value& lhs, const Value& rhs);

  friend Value& operator+=(Value& lhs, const Value& rhs);

  friend Value operator-(const Value& lhs, const Value& rhs);

  friend Value& operator-=(Value& lhs, const Value& rhs);

  friend Value operator*(const Value& lhs, const Value& rhs);

  friend Value& operator*=(Value& lhs, const Value& rhs);

  friend Value operator/(const Value& lhs, const Value& rhs);

  friend Value& operator/=(Value& lhs, const Value& rhs);

  friend std::ostream& operator<<(std::ostream& os, const Value& value);
};

bool operator==(const Value& lhs, const Value& rhs);

bool operator!=(const Value& lhs, const Value& rhs);

Value operator+(const Value& lhs, const Value& rhs);

Value operator-(const Value& lhs, const Value& rhs);

Value operator*(const Value& lhs, const Value& rhs);

Value operator/(const Value& lhs, const Value& rhs);

std::ostream& operator<<(std::ostream& os, const Value& value);

} // calculator

#endif // !CALCULATOR_VALUE_HPP_