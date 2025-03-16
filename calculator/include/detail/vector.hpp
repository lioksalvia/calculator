#ifndef LIOKSALVIA_CALCULATOR_DETAIL_VECTOR_HPP_
#define LIOKSALVIA_CALCULATOR_DETAIL_VECTOR_HPP_

#include <algorithm>
#include <memory>
#include <string>
#include <variant>
#include <vector>

namespace lioksalvia::calculator::detail {

using number_t = long double;
class vector;
using value_t = std::variant<number_t, vector>;

template <typename>
struct is_std_vector : std::false_type {
};

template <typename T, typename Alloc>
struct is_std_vector<std::vector<T, Alloc> > : std::true_type {
};

class vector final {
  public:
    explicit vector();
    vector(const vector& other);
    vector(vector&& other) noexcept;

    vector& operator=(const vector& other);
    vector& operator=(vector&& other) noexcept;

    template <typename T, typename = std::enable_if_t<
      std::is_convertible_v<T, number_t> || std::is_convertible_v<T, vector>> >
    explicit vector(const std::vector<T>& elements) ;

    template <typename T, typename = std::enable_if_t<
      std::is_convertible_v<T, number_t> || std::is_convertible_v<T, vector>> >
    explicit vector(std::vector<T>&& elements) ;

    template <typename... Args, typename = std::enable_if_t<
      (sizeof...(Args) > 1) /* avoid conflict with copy/move constructors */ &&
        std::conjunction_v<std::disjunction<
          std::is_convertible<Args, number_t>,
          std::is_convertible<Args, vector>,
          is_std_vector<std::decay_t<Args> > >...>> >
    explicit vector(Args&&... args) ;

    [[nodiscard]] std::string ToString() const;

    [[nodiscard]] const std::vector<value_t>& value() const;

  private:
    std::vector<value_t> value_;

    friend bool operator==(const vector& lhs, const vector& rhs);
    friend bool operator!=(const vector& lhs, const vector& rhs);

    friend vector operator-(vector value);

    friend vector operator+(vector lhs, const vector& rhs);
    friend vector& operator+=(vector& lhs, const vector& rhs);

    friend vector operator-(vector lhs, const vector& rhs);
    friend vector& operator-=(vector& lhs, const vector& rhs);

    friend vector operator*(const vector& lhs, const vector& rhs);
    friend vector& operator*=(vector& lhs, const vector& rhs);

    friend vector operator/(const vector& lhs, const vector& rhs);
    friend vector& operator/=(vector& lhs, const vector& rhs);

    friend std::ostream& operator<<(std::ostream& os, const vector& value);

    friend vector operator+(vector lhs, number_t rhs);
    friend vector& operator+=(vector& lhs, number_t rhs);
    friend vector operator+(number_t lhs, vector rhs);

    friend vector operator-(vector lhs, number_t rhs);
    friend vector& operator-=(vector& lhs, number_t rhs);
    friend vector operator-(number_t lhs, vector rhs);

    friend vector operator*(vector lhs, number_t rhs);
    friend vector& operator*=(vector& lhs, number_t rhs);
    friend vector operator*(number_t lhs, vector rhs);

    friend vector operator/(vector lhs, number_t rhs);
    friend vector& operator/=(vector& lhs, number_t rhs);
};

bool operator==(const vector& lhs, const vector& rhs);
bool operator!=(const vector& lhs, const vector& rhs);

vector operator-(vector value);

vector operator+(vector lhs, const vector& rhs);
vector& operator+=(vector& lhs, const vector& rhs);

vector operator-(vector lhs, const vector& rhs);
vector& operator-=(vector& lhs, const vector& rhs);

vector operator*(const vector& lhs, const vector& rhs);
vector& operator*=(vector& lhs, const vector& rhs);

vector operator/(const vector& lhs, const vector& rhs);
vector& operator/=(vector& lhs, const vector& rhs);

std::ostream& operator<<(std::ostream& os, const vector& value);

vector operator+(vector lhs, number_t rhs);
vector& operator+=(vector& lhs, number_t rhs);
vector operator+(number_t lhs, vector rhs);

vector operator-(vector lhs, number_t rhs);
vector& operator-=(vector& lhs, number_t rhs);
vector operator-(number_t lhs, vector rhs);

vector operator*(vector lhs, number_t rhs);
vector& operator*=(vector& lhs, number_t rhs);
vector operator*(number_t lhs, vector rhs);

vector operator/(vector lhs, number_t rhs);
vector& operator/=(vector& lhs, number_t rhs);

} // namespace lioksalvia::calculator::detail

#include "vector.tpp"

#endif  // !LIOKSALVIA_CALCULATOR_DETAIL_VECTOR_HPP_