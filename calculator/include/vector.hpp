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

template <typename T>
struct is_std_vector : std::false_type {};

template <typename T, typename Alloc>
struct is_std_vector<std::vector<T, Alloc> > : std::true_type {};

class Vector final {
public:
  explicit Vector();

  Vector(const Vector& other);

  Vector(Vector&& other) noexcept;

  Vector& operator=(const Vector& other);

  Vector& operator=(Vector&& other) noexcept;

  template <typename T,
            typename = std::enable_if_t<std::is_convertible_v<T, number_t> ||
                                        std::is_convertible_v<T, Vector>> >
  explicit Vector(const std::vector<T>& elements) {
    value_.reserve(elements.size());
    std::transform(
        elements.begin(), elements.end(), std::back_inserter(value_),
        [](const T& elem) -> value_t {
          if constexpr (std::is_convertible_v<T, number_t>) {
            return value_t{static_cast<number_t>(elem)};
          } else {
            return value_t{Vector(elem)};
          }
        });
  }

  template <typename T,
            typename = std::enable_if_t<std::is_convertible_v<T, number_t> ||
                                        std::is_convertible_v<T, Vector>> >
  explicit Vector(std::vector<T>&& elements) {
    value_.reserve(elements.size());
    std::transform(
        std::make_move_iterator(elements.begin()),
        std::make_move_iterator(elements.end()), std::back_inserter(value_),
        [](T&& elem) -> value_t {
          if constexpr (std::is_convertible_v<T, number_t>) {
            return value_t{static_cast<number_t>(elem)};
          } else {
            return value_t{Vector(std::move(elem))};
          }
        });
  }

  template <typename... Args,
            typename = std::enable_if_t<
              (sizeof...(Args) > 1) && // avoid conflict with copy/move constructors
              (std::conjunction_v<
                std::disjunction<
                  std::is_convertible<Args, number_t>,
                  std::is_convertible<Args, Vector>,
                  is_std_vector<std::decay_t<Args> >
                >...
              >)
            > >
  explicit Vector(Args&&... args) {
    value_.reserve(sizeof...(Args));
    auto add_value = [this]<typename T0>(T0&& arg) {
      using T = std::decay_t<T0>;
      if constexpr (std::is_convertible_v<T, number_t>) {
        value_.emplace_back(static_cast<number_t>(arg));
      } else if constexpr (is_std_vector<T>::value) {
        value_.emplace_back(Vector(std::forward<T>(arg)));
      } else {
        value_.emplace_back(Vector(std::forward<T>(arg)));
      }
    };
    (add_value(std::forward<Args>(args)), ...);
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

Vector& operator+=(Vector& lhs, const Vector& rhs);

Vector operator-(Vector lhs, const Vector& rhs);

Vector& operator-=(Vector& lhs, const Vector& rhs);

Vector operator*(const Vector& lhs, const Vector& rhs);

Vector& operator*=(Vector& lhs, const Vector& rhs);

Vector operator/(const Vector& lhs, const Vector& rhs);

Vector& operator/=(Vector& lhs, const Vector& rhs);

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

} // namespace calculator

#endif  // !CALCULATOR_NUMBER_HPP_