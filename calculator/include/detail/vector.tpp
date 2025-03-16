#ifndef LIOKSALVIA_CALCULATOR_DETAIL_VECTOR_TPP_
#define LIOKSALVIA_CALCULATOR_DETAIL_VECTOR_TPP_

#ifdef LIOKSALVIA_CALCULATOR_DETAIL_VECTOR_HPP_

template <typename T, typename>
lioksalvia::calculator::detail::vector::vector(const std::vector<T>& elements){
  value_.reserve(elements.size());
  std::transform(
    elements.begin(),
    elements.end(),
    std::back_inserter(value_),
    [](const T& elem) -> value_t {
      if constexpr (std::is_convertible_v<T, number_t>) {
        return value_t{static_cast<number_t>(elem)};
      } else {
        return value_t{vector(elem)};
      }
    });
}

template <typename T, typename>
lioksalvia::calculator::detail::vector::vector(std::vector<T>&& elements){
  value_.reserve(elements.size());
  std::transform(
    std::make_move_iterator(elements.begin()),
    std::make_move_iterator(elements.end()),
    std::back_inserter(value_),
    [](T&& elem) -> value_t {
      if constexpr (std::is_convertible_v<T, number_t>) {
        return value_t{static_cast<number_t>(elem)};
      } else { return value_t{vector(std::move(elem))}; }
    });
}

template <typename ... Args, typename>
lioksalvia::calculator::detail::vector::vector(Args&&... args){
  value_.reserve(sizeof...(Args));
  auto add_value = [this]<typename T0>(T0&& arg) {
    using T = std::decay_t<T0>;
    if constexpr (std::is_convertible_v<T, number_t>) {
      value_.emplace_back(static_cast<number_t>(arg));
    } else {
      value_.emplace_back(vector(std::forward<T>(arg)));
    }
  };
  (add_value(std::forward<Args>(args)), ...);
}

#else
#error "Include vector.hpp before vector.tpp"
#endif

#endif // !LIOKSALVIA_CALCULATOR_DETAIL_VECTOR_TPP_