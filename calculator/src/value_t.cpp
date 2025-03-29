#include <ostream>

#include "detail/number_t.hpp"
#include "detail/value_t.hpp"
#include "detail/vector.hpp"

using namespace lioksalvia::calculator::detail;

std::ostream &lioksalvia::calculator::detail::operator<<(std::ostream &os, const value_t &val) {
  std::visit([&os](const auto &v) { os << v; }, val);
  return os;
}