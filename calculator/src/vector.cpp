#include "../include/vector.hpp"

#include <format>
#include <sstream>

#include "../include/calculator_error.hpp"

using namespace calculator;

Vector::Vector(const Vector&) = default;
Vector::Vector(Vector&&) noexcept = default;
Vector& Vector::operator=(const Vector&) = default;
Vector& Vector::operator=(Vector&&) = default;

std::string Vector::ToString() const {
  std::ostringstream os;
  os << *this;
  return os.str();
}

const std::vector<value_t>& Vector::value() const { return value_; }

bool calculator::operator==(const Vector& lhs, const Vector& rhs) {
  return lhs.value_ == rhs.value_;
}

bool calculator::operator!=(const Vector& lhs, const Vector& rhs) {
  return !(lhs == rhs);
}

Vector calculator::operator-(Vector value) {
  for (auto& val : value.value_) {
    val = std::visit(
        [](auto&& v) -> value_t {
          using T = std::decay_t<decltype(v)>;
          if constexpr (std::is_same_v<T, number_t>) {
            return -v;
          } else if constexpr (std::is_same_v<T, Vector>) {
            return -v;
          }
        },
        val);
  }
  return value;
}

Vector calculator::operator+(Vector lhs, const Vector& rhs) {
  return lhs += rhs;
}

Vector& calculator::operator+=(Vector& lhs, const Vector& rhs) {
  auto newSize = std::max(lhs.value_.size(), rhs.value_.size());
  lhs.value_.resize(newSize);

  for (size_t i = 0, n = rhs.value_.size(); i < n; ++i) {
    lhs.value_[i] = std::visit(
        [](auto& l, const auto& r) -> value_t {
          using L = std::decay_t<decltype(l)>;
          using R = std::decay_t<decltype(r)>;

          if constexpr (std::is_same_v<L, number_t> &&
                        std::is_same_v<R, number_t>) {
            return l += r;
          } else if constexpr (std::is_same_v<L, number_t> &&
                               std::is_same_v<R, Vector>) {
            return r + l;
          } else if constexpr (std::is_same_v<L, Vector> &&
                               std::is_same_v<R, number_t>) {
            return l += r;
          } else if constexpr (std::is_same_v<L, Vector> &&
                               std::is_same_v<R, Vector>) {
            return l += r;
          }
        },
        lhs.value_[i], rhs.value_[i]);
  }
  return lhs;
}

Vector calculator::operator-(Vector lhs, const Vector& rhs) {
  return lhs -= rhs;
}

Vector& calculator::operator-=(Vector& lhs, const Vector& rhs) {
  auto newSize = std::max(lhs.value_.size(), rhs.value_.size());
  lhs.value_.resize(newSize);

  for (size_t i = 0, n = rhs.value_.size(); i < n; ++i) {
    lhs.value_[i] = std::visit(
        [](auto& l, const auto& r) -> value_t {
          using L = std::decay_t<decltype(l)>;
          using R = std::decay_t<decltype(r)>;

          if constexpr (std::is_same_v<L, number_t> &&
                        std::is_same_v<R, number_t>) {
            return l -= r;
          } else if constexpr (std::is_same_v<L, number_t> &&
                               std::is_same_v<R, Vector>) {
            return r - l;
          } else if constexpr (std::is_same_v<L, Vector> &&
                               std::is_same_v<R, number_t>) {
            return l -= r;
          } else if constexpr (std::is_same_v<L, Vector> &&
                               std::is_same_v<R, Vector>) {
            return l -= r;
          }
        },
        lhs.value_[i], rhs.value_[i]);
  }
  return lhs;
}

Vector calculator::operator-(number_t lhs, Vector rhs) {
  for (auto& val : rhs.value_) {
    std::visit([](auto& v) { v = -v; }, val);
  }
  return lhs + rhs;
}

Vector calculator::operator*(const Vector& lhs, const Vector& rhs) {
  throw std::system_error(CalculatorErrc::NotImplemented);
}

Vector& calculator::operator*=(Vector& lhs, const Vector& rhs) {
  throw std::system_error(CalculatorErrc::NotImplemented);
}

Vector calculator::operator/(const Vector& lhs, const Vector& rhs) {
  throw std::system_error(CalculatorErrc::NotImplemented);
}

Vector& calculator::operator/=(Vector& lhs, const Vector& rhs) {
  throw std::system_error(CalculatorErrc::NotImplemented);
}

std::ostream& calculator::operator<<(std::ostream& os, const Vector& value) {
  os << "[";
  bool first = true;
  for (const auto& val : value.value_) {
    if (!first) os << ", ";
    std::visit([&os](const auto& v) { os << v; }, val);
    first = false;
  }
  os << "]";
  return os;
}

Vector calculator::operator+(Vector lhs, number_t rhs) { return lhs += rhs; }

Vector& calculator::operator+=(Vector& lhs, number_t rhs) {
  for (auto& val : lhs.value_) {
    std::visit([&rhs](auto& v) { v += rhs; }, val);
  }
  return lhs;
}

Vector calculator::operator+(number_t lhs, Vector rhs) { return rhs += lhs; }

Vector calculator::operator-(Vector lhs, number_t rhs) { return lhs -= rhs; }

Vector& calculator::operator-=(Vector& lhs, number_t rhs) {
  return lhs += (-rhs);
}

Vector calculator::operator*(Vector lhs, number_t rhs) { return lhs *= rhs; }

Vector& calculator::operator*=(Vector& lhs, number_t rhs) {
  for (auto& val : lhs.value_) {
    std::visit([&rhs](auto& v) { v *= rhs; }, val);
  }
  return lhs;
}

Vector calculator::operator*(number_t lhs, Vector rhs) { return rhs *= lhs; }

Vector calculator::operator/(Vector lhs, number_t rhs) { return lhs /= rhs; }

Vector& calculator::operator/=(Vector& lhs, number_t rhs) {
  for (auto& val : lhs.value_) {
    std::visit([&rhs](auto& v) { v /= rhs; }, val);
  }
  return lhs;
}