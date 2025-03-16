#include <format>
#include <sstream>

#include "../include/calculator_error.hpp"
#include "../include/detail/vector.hpp"

using namespace lioksalvia::calculator;
using namespace lioksalvia::calculator::detail;

vector::vector() = default;

vector::vector(const vector &other) = default; // NOLINT(*-no-recursion)

vector::vector(vector &&other) noexcept = default;

vector &vector::operator=(const vector &other) = default; // NOLINT(*-no-recursion)

vector &vector::operator=(vector &&other) noexcept = default;

std::string vector::ToString() const {
  std::ostringstream os;
  os << *this;
  return os.str();
}

const std::vector<value_t> &vector::value() const { return value_; }

bool detail::operator==(const vector &lhs, const vector &rhs) { // NOLINT(*-no-recursion)
  return lhs.value_ == rhs.value_;
}

bool detail::operator!=(const vector &lhs, const vector &rhs) {
  return !(lhs == rhs);
}

vector detail::operator-(vector value) { // NOLINT(*-no-recursion)
  for (auto &val: value.value_) {
    val = std::visit([]<typename T0>(T0 &&v) -> value_t { // NOLINT(*-no-recursion)
        using T = std::decay_t<T0>;
        if constexpr (std::is_same_v<T, number_t> || std::is_same_v<T, vector>) {
          return -v;
        }
        throw std::system_error(calculator_errc::type_mismatch);
      }, val);
  }
  return value;
}

vector detail::operator+(vector lhs, const vector &rhs) {
  return lhs += rhs;
}

vector &detail::operator+=(vector &lhs, const vector &rhs) {
  const auto new_size = std::max(lhs.value_.size(), rhs.value_.size());
  lhs.value_.resize(new_size);

  for (size_t i = 0, n = rhs.value_.size(); i < n; ++i) {
    lhs.value_[i] = std::visit([]<typename T0, typename T1>(T0 &l, const T1 &r) -> value_t {
      using L = std::decay_t<T0>;
      using R = std::decay_t<T1>;

      if constexpr ((std::is_same_v<L, number_t> && std::is_same_v<R, number_t>) || (
                      std::is_same_v<L, vector> && std::is_same_v<R, number_t>) || (
                      std::is_same_v<L, vector> && std::is_same_v<R, vector>)) {
        return l += r;
      } else if constexpr (std::is_same_v<L, number_t> && std::is_same_v<R, vector>) {
        return r + l;
      }
      throw std::system_error(calculator_errc::type_mismatch);
    }, lhs.value_[i], rhs.value_[i]);
  }
  return lhs;
}

vector detail::operator-(vector lhs, const vector &rhs) {
  return lhs -= rhs;
}

vector &detail::operator-=(vector &lhs, const vector &rhs) {
  const auto new_size = std::max(lhs.value_.size(), rhs.value_.size());
  lhs.value_.resize(new_size);

  for (size_t i = 0, n = rhs.value_.size(); i < n; ++i) {
    lhs.value_[i] = std::visit([]<typename T0, typename T1>(T0 &l, const T1 &r) -> value_t {
      using L = std::decay_t<T0>;
      using R = std::decay_t<T1>;

      if constexpr ((std::is_same_v<L, number_t> && std::is_same_v<R, number_t>) || (
                      std::is_same_v<L, vector> && std::is_same_v<R, number_t>) || (
                      std::is_same_v<L, vector> && std::is_same_v<R, vector>)) {
        return l -= r;
      } else if constexpr (std::is_same_v<L, number_t> && std::is_same_v<R, vector>) {
        return r - l;
      }
      throw std::system_error(calculator_errc::type_mismatch);
    }, lhs.value_[i], rhs.value_[i]);
  }
  return lhs;
}

vector detail::operator-(number_t lhs, vector rhs) {
  for (auto &val: rhs.value_) { std::visit([](auto &v) { v = -v; }, val); }
  return lhs + rhs;
}

vector detail::operator*(const vector & /*lhs*/, const vector & /*rhs*/) {
  throw std::system_error(calculator_errc::not_implemented);
}

vector &detail::operator*=(vector & /*lhs*/, const vector & /*rhs*/) {
  throw std::system_error(calculator_errc::not_implemented);
}

vector detail::operator/(const vector & /*lhs*/, const vector & /*rhs*/) {
  throw std::system_error(calculator_errc::not_implemented);
}

vector &detail::operator/=(vector & /*lhs*/, const vector & /*rhs*/) {
  throw std::system_error(calculator_errc::not_implemented);
}

std::ostream &detail::operator<<(std::ostream &os, const vector &value) { // NOLINT(*-no-recursion)
  os << "[";
  auto first = true;
  for (const auto &val: value.value_) {
    if (!first) { os << ", "; }
    std::visit([&os](const auto &v) { os << v; }, val); // NOLINT(*-no-recursion)
    first = false;
  }
  os << "]";
  return os;
}

vector detail::operator+(vector lhs, number_t rhs) { return lhs += rhs; }

vector &detail::operator+=(vector &lhs, number_t rhs) { // NOLINT(*-no-recursion)
  for (auto &val: lhs.value_) {
    std::visit([rhs](auto &v) { v += rhs; }, val); // NOLINT(*-no-recursion)
  }
  return lhs;
}

vector detail::operator+(number_t lhs, vector rhs) { return rhs += lhs; }

vector detail::operator-(vector lhs, number_t rhs) { return lhs -= rhs; }

vector &detail::operator-=(vector &lhs, number_t rhs) {
  return lhs += -rhs;
}

vector detail::operator*(vector lhs, number_t rhs) {
  lhs *= rhs;
  return lhs;
}

vector &detail::operator*=(vector &lhs, number_t rhs) { // NOLINT(*-no-recursion)
  for (auto &val: lhs.value_) {
    std::visit([&rhs](auto &v) { v *= rhs; }, val); // NOLINT(*-no-recursion)
  }
  return lhs;
}

vector detail::operator*(number_t lhs, vector rhs) {
  rhs *= lhs;
  return rhs;
}

vector detail::operator/(vector lhs, number_t rhs) {
  lhs /= rhs;
  return lhs;
}

vector &detail::operator/=(vector &lhs, number_t rhs) { // NOLINT(*-no-recursion)
  for (auto &val: lhs.value_) {
    std::visit([&rhs](auto &v) { v /= rhs; }, val); // NOLINT(*-no-recursion)
  }
  return lhs;
}