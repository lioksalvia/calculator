#ifndef LIOKSALVIA_CALCULATOR_DETAIL_VECTOR_HPP_
#define LIOKSALVIA_CALCULATOR_DETAIL_VECTOR_HPP_

#include <format>
#include <string>
#include <vector>

#include "value_t.hpp"

namespace lioksalvia::calculator::detail {

template<typename>
struct is_std_vector : std::false_type {
};

template<typename T, typename Alloc>
struct is_std_vector<std::vector<T, Alloc>> : std::true_type {
};

template<typename... Args> concept args_are_constructible_to_vector =
    sizeof...(Args) > 1 && std::conjunction_v<std::disjunction<
      std::is_convertible<Args, number_t>, std::is_constructible<Args, vector>, is_std_vector<std::decay_t<Args>>>...>;

class vector final {
public:
  explicit vector();

  vector(const vector &other);

  vector(vector &&other) noexcept;

  template<typename T> requires is_convertible_to_number_t<T> || is_constructible_to_vector<T>
  explicit vector(const std::vector<T> &other);

  template<typename T> requires is_convertible_to_number_t<T> || is_constructible_to_vector<T>
  explicit vector(std::vector<T> &&other);

  template<typename T> requires is_convertible_to_number_t<T>
  explicit vector(T &&element);

  template<typename... Args> requires args_are_constructible_to_vector<Args...>
  explicit vector(Args &&... args);

  vector &operator=(const vector &other);

  vector &operator=(vector &&other) noexcept;

  [[nodiscard]] std::string to_string() const;

  [[nodiscard]] const std::vector<value_t> &value() const;

private:
  std::vector<value_t> value_;

  friend bool operator==(const vector &lhs, const vector &rhs);

  friend bool operator!=(const vector &lhs, const vector &rhs);

  friend vector operator-(vector value);

  friend vector operator+(vector lhs, const vector &rhs);

  friend vector &operator+=(vector &lhs, const vector &rhs);

  friend vector operator-(vector lhs, const vector &rhs);

  friend vector &operator-=(vector &lhs, const vector &rhs);

  friend value_t operator*(const vector &lhs, const vector &rhs);

  friend vector matrix_product(const vector &lhs, const vector &rhs);

  friend std::ostream &operator<<(std::ostream &os, const vector &value);

  friend vector operator+(vector lhs, number_t rhs);

  friend vector &operator+=(vector &lhs, number_t rhs);

  friend vector operator+(number_t lhs, vector rhs);

  friend vector operator-(vector lhs, number_t rhs);

  friend vector &operator-=(vector &lhs, number_t rhs);

  friend vector operator-(number_t lhs, vector rhs);

  friend vector operator*(vector lhs, number_t rhs);

  friend vector &operator*=(vector &lhs, number_t rhs);

  friend vector operator*(number_t lhs, vector rhs);

  friend vector operator/(vector lhs, number_t rhs);

  friend vector &operator/=(vector &lhs, number_t rhs);
};

bool operator==(const vector &lhs, const vector &rhs);

bool operator!=(const vector &lhs, const vector &rhs);

vector operator-(vector value);

vector operator+(vector lhs, const vector &rhs);

vector &operator+=(vector &lhs, const vector &rhs);

vector operator-(vector lhs, const vector &rhs);

vector &operator-=(vector &lhs, const vector &rhs);

value_t operator*(const vector &lhs, const vector &rhs);

std::ostream &operator<<(std::ostream &os, const vector &value);

vector operator+(vector lhs, number_t rhs);

vector &operator+=(vector &lhs, number_t rhs);

vector operator+(number_t lhs, vector rhs);

vector operator-(vector lhs, number_t rhs);

vector &operator-=(vector &lhs, number_t rhs);

vector operator-(number_t lhs, vector rhs);

vector operator*(vector lhs, number_t rhs);

vector &operator*=(vector &lhs, number_t rhs);

vector operator*(number_t lhs, vector rhs);

vector operator/(vector lhs, number_t rhs);

vector &operator/=(vector &lhs, number_t rhs);

} // namespace lioksalvia::calculator::detail

template<>
struct std::formatter<lioksalvia::calculator::detail::vector> : formatter<std::string> { // NOLINT(*-dcl58-cpp)
  auto format(const lioksalvia::calculator::detail::vector &vec, format_context &ctx) const;
};

#include "vector.tpp"

#endif  // !LIOKSALVIA_CALCULATOR_DETAIL_VECTOR_HPP_