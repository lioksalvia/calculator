#include "calculator_error.hpp"

using namespace lioksalvia::calculator;

const char *calculator_category::name() const noexcept {
  return "calculator";
}

std::string calculator_category::message(int ev) const {
  switch (static_cast<calculator_errc>(ev)) {
    case calculator_errc::success:
      return "no error";
    case calculator_errc::division_by_zero:
      return "division by zero";
    case calculator_errc::not_implemented:
      return "operation is not implemented yet";
    case calculator_errc::type_mismatch:
      return "type mismatch in operation";
    default:
      return "unknown error";
  }
}

std::error_code lioksalvia::calculator::make_error_code(calculator_errc e) {
  static calculator_category instance;
  return {static_cast<int>(e), instance};
}