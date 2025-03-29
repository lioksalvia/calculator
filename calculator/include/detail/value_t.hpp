#ifndef LIOKSALVIA_CALCULATOR_DETAIL_VALUE_T_HPP_
#define LIOKSALVIA_CALCULATOR_DETAIL_VALUE_T_HPP_

#include <ostream>
#include <variant>

#include "number_t.hpp"

namespace lioksalvia::calculator::detail {

class vector;
using value_t = std::variant<number_t, vector>;

template<typename T> concept is_convertible_to_number_t = std::is_convertible_v<T, number_t>;
template<typename T> concept is_constructible_to_number_t = std::is_constructible_v<T, number_t>;

template<typename T> concept is_convertible_to_vector = std::is_convertible_v<T, vector>;
template<typename T> concept is_constructible_to_vector = std::is_constructible_v<T, vector>;

std::ostream &operator<<(std::ostream &os, const value_t &val);

} // !lioksalvia::calculator::detail

#endif // !LIOKSALVIA_CALCULATOR_DETAIL_VALUE_T_HPP_
