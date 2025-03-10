#ifndef CALCULATOR_NUMBER_HPP_
#define CALCULATOR_NUMBER_HPP_

#include <algorithm>
#include <concepts>
#include <memory>
#include <string>
#include <variant>
#include <vector>

namespace calculator {

using number_t = long double;
class Vector;
using value_t = std::variant<number_t, Vector>;

class Vector final {
 public:
  explicit Vector(const Vector& other);

  explicit Vector(Vector&& other) noexcept;

  Vector& operator=(const Vector& other);

  Vector& operator=(Vector&& other) noexcept;

  template <typename T,
            typename = std::enable_if_t<std::is_convertible_v<T, number_t> ||
                                        std::is_convertible_v<T, Vector>>>
  explicit Vector(const std::vector<T>& elements) {
    value_.resize(elements.size());
    std::transform(
        elements.begin(), elements.end(), value_.begin(),
        [](const T& elem) -> value_t {
          if constexpr (std::is_convertible_v<T, number_t>) {
            return static_cast<number_t>(elem);
          } else /*if constexpr (std::is_convertible_v<T, Vector>)*/ {
            return Vector(elem);
          }
        });
  }

  template <typename T,
            typename = std::enable_if_t<std::is_convertible_v<T, number_t> ||
                                        std::is_convertible_v<T, Vector>>>
  explicit Vector(std::vector<T>&& elements) {
    value_.resize(elements.size());
    std::transform(
        std::make_move_iterator(elements.begin()),
        std::make_move_iterator(elements.end()), value_.begin(),
        [](T&& elem) -> value_t {
          if constexpr (std::is_convertible_v<T, number_t>) {
            return static_cast<number_t>(elem);
          } else /*if constexpr (std::is_convertible_v<T, Vector>)*/ {
            return Vector(std::move(elem));
          }
        });
  }

  template <typename... Args, typename = std::enable_if_t<
                                  (std::conjunction_v<std::disjunction<
                                       std::is_convertible<Args, number_t>,
                                       std::is_convertible<Args, Vector>>...>)>>
  explicit Vector(Args&&... args) {
    value_.reserve(sizeof...(args));
    (value_.emplace_back(std::forward<Args>(args)), ...);
  }

  std::string ToString() const;

  const std::vector<value_t>& value() const;

 private:
  std::vector<value_t> value_;

  friend bool operator==(const Vector& lhs, const Vector& rhs);

  friend bool operator!=(const Vector& lhs, const Vector& rhs);

  friend Vector operator-(Vector value);

  friend Vector operator+(Vector lhs, const Vector& rhs);

  friend Vector& operator+=(Vector& lhs, const Vector& rhs);

  friend Vector operator-(Vector lhs, const Vector& rhs);

  friend Vector& operator-=(Vector& lhs, const Vector& rhs);

  friend Vector operator*(const Vector& lhs, const Vector& rhs);

  friend Vector& operator*=(Vector& lhs, const Vector& rhs);

  friend Vector operator/(const Vector& lhs, const Vector& rhs);

  friend Vector& operator/=(Vector& lhs, const Vector& rhs);

  friend std::ostream& operator<<(std::ostream& os, const Vector& value);

  friend Vector operator+(Vector lhs, number_t rhs);
  friend Vector& operator+=(Vector& lhs, number_t rhs);
  friend Vector operator+(number_t lhs, Vector rhs);
  friend Vector operator-(Vector lhs, number_t rhs);
  friend Vector& operator-=(Vector& lhs, number_t rhs);
  friend Vector operator-(number_t lhs, Vector rhs);
  friend Vector operator*(Vector lhs, number_t rhs);
  friend Vector& operator*=(Vector& lhs, number_t rhs);
  friend Vector operator*(number_t lhs, Vector rhs);
  friend Vector operator/(Vector lhs, number_t rhs);
  friend Vector& operator/=(Vector& lhs, number_t rhs);
};

bool operator==(const Vector& lhs, const Vector& rhs);

bool operator!=(const Vector& lhs, const Vector& rhs);

Vector operator-(Vector value);

Vector operator+(Vector lhs, const Vector& rhs);

Vector operator-(Vector lhs, const Vector& rhs);

Vector operator*(const Vector& lhs, const Vector& rhs);

Vector operator/(const Vector& lhs, const Vector& rhs);

std::ostream& operator<<(std::ostream& os, const Vector& value);

Vector operator+(Vector lhs, number_t rhs);

Vector& operator+=(Vector& lhs, number_t rhs);

Vector operator+(number_t lhs, Vector rhs);

Vector operator-(Vector lhs, number_t rhs);

Vector& operator-=(Vector& lhs, number_t rhs);

Vector operator-(number_t lhs, Vector rhs);

Vector operator*(Vector lhs, number_t rhs);

Vector& operator*=(Vector& lhs, number_t rhs);

Vector operator*(number_t lhs, Vector rhs);

Vector operator/(Vector lhs, number_t rhs);

Vector& operator/=(Vector& lhs, number_t rhs);

}  // namespace calculator

#endif  // !CALCULATOR_NUMBER_HPP_