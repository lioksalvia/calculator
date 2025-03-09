#ifndef CALCULATOR_VALUE_HPP_
#define CALCULATOR_VALUE_HPP_

#include <concepts>
#include <variant>
#include <vector>
#include <memory>

namespace calculator {

using number_t = long double;
class Value;
using vector_t = std::vector<std::unique_ptr<Value> >;
using value_t = std::variant<number_t, vector_t>;

class Value {
public:
  template <typename TNumber> requires std::convertible_to<TNumber, number_t>
  Value(const TNumber& number) : value_(static_cast<number_t>(number)) {}

  template <typename TValue> requires std::convertible_to<TValue, Value>
  Value(const std::vector<TValue>& vector) {
    vector_t temp;
    temp.reserve(vector.size());
    for (const auto& v : vector) {
      temp.push_back(std::make_unique<Value>(v));
    }
    value_ = std::move(temp);
  }


  template <typename TValue> requires std::convertible_to<TValue, Value>
  Value(const std::vector<std::unique_ptr<TValue> >& vector) {
    vector_t temp;
    temp.reserve(vector.size());
    for (auto& p : vector) {
      temp.push_back(std::make_unique<Value>(p));
    }
    value_ = std::move(temp);
  }

  Value(const Value& other);

  Value(Value&& other)
    noexcept;

  Value& operator=(const Value& other);

  Value& operator=(Value&& other) noexcept;

  [[nodiscard]] constexpr bool isNumber() const;

  [[nodiscard]] constexpr bool isVector() const;

  [[nodiscard]] const value_t& value() const;

private:
  value_t value_;

  friend bool operator==(const Value& lhs, const Value& rhs);

  friend bool operator!=(const Value& lhs, const Value& rhs);

  friend std::common_comparison_category_t<
    std::compare_three_way_result_t<number_t>,
    std::compare_three_way_result_t<vector_t> > operator<=>(const Value& lhs, const Value& rhs);

  friend Value operator+(const Value& lhs, const Value& rhs);

  friend Value operator-(const Value& lhs, const Value& rhs);

  friend Value operator*(const Value& lhs, const Value& rhs);

  friend Value operator/(const Value& lhs, const Value& rhs);
};

bool operator==(const Value& lhs, const Value& rhs);

bool operator!=(const Value& lhs, const Value& rhs);

std::common_comparison_category_t<
  std::compare_three_way_result_t<number_t>,
  std::compare_three_way_result_t<vector_t> > operator<=>(const Value& lhs, const Value& rhs);

Value operator+(const Value& lhs, const Value& rhs);

Value operator-(const Value& lhs, const Value& rhs);

Value operator*(const Value& lhs, const Value& rhs);

Value operator/(const Value& lhs, const Value& rhs);

} // calculator

#endif // !CALCULATOR_VALUE_HPP_