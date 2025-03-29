#ifndef LIOKSALVIA_CALCULATOR_DETAIL_VECTOR_TPP_
#define LIOKSALVIA_CALCULATOR_DETAIL_VECTOR_TPP_

#ifdef LIOKSALVIA_CALCULATOR_DETAIL_VECTOR_HPP_

#include <algorithm>

#include "calculator_error.hpp"

namespace lioksalvia::calculator::detail {

template<typename T> requires is_convertible_to_number_t<T> || is_constructible_to_vector<T>
vector::vector(const std::vector<T> &other) {
  value_.reserve(other.size());
  std::transform(other.begin(), other.end(), std::back_inserter(value_), [](const T &elem) -> value_t {
    if constexpr (is_convertible_to_number_t<T>) {
      return value_t{static_cast<number_t>(elem)};
    } else if constexpr (is_constructible_to_vector<T>) {
      return value_t{vector{elem}};
    } else {
      throw std::system_error(calculator_errc::type_mismatch);
    }
  });
}

template<typename T> requires is_convertible_to_number_t<T> || is_constructible_to_vector<T>
vector::vector(std::vector<T> &&other) {
  value_.reserve(other.size());
  std::transform(std::make_move_iterator(other.begin()), std::make_move_iterator(other.end()),
    std::back_inserter(value_), [](T &&elem) {
      if constexpr (is_convertible_to_number_t<T>) {
        return value_t{static_cast<number_t>(elem)};
      } else if constexpr (is_constructible_to_vector<T>) {
        return value_t{vector(std::move(elem))};
      } else {
        throw std::system_error(calculator_errc::type_mismatch);
      }
    });
}

template<typename T> requires is_convertible_to_number_t<T>
vector::vector(T &&element) {
  value_.emplace_back(static_cast<number_t>(std::forward<T>(element)));
}

template<typename... Args> requires args_are_constructible_to_vector<Args...>
vector::vector(Args &&... args) {
  value_.reserve(sizeof...(Args));
  auto add_value = [this]<typename T0>(T0 &&arg) {
    using T = std::decay_t<T0>;
    if constexpr (is_convertible_to_number_t<T>) {
      value_.emplace_back(static_cast<number_t>(arg));
    } else if constexpr (is_constructible_to_vector<T>) {
      value_.emplace_back(vector(std::forward<T>(arg)));
    } else {
      throw std::system_error(calculator_errc::type_mismatch);
    }
  };
  (add_value(std::forward<Args>(args)), ...);
}

} // namespace lioksalvia::calculator::detail

inline auto std::formatter<lioksalvia::calculator::detail::vector>::format(
  const lioksalvia::calculator::detail::vector &vec, format_context &ctx) const {
  return formatter<std::string>::format(vec.to_string(), ctx);
}

#else
#error "Include vector.hpp before vector.tpp"
#endif

#endif // !LIOKSALVIA_CALCULATOR_DETAIL_VECTOR_TPP_