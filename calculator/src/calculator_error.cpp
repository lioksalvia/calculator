#include "../include/calculator_error.hpp"

using namespace calculator;

const char* CalculatorErrorCategory::name() const noexcept {
  return "calculator";
}

std::string CalculatorErrorCategory::message(int ev) const {
  switch (static_cast<CalculatorErrc>(ev)) {
    case CalculatorErrc::Success:
      return "no error";
    case CalculatorErrc::NotImplemented:
      return "operation is not implemented yet";
    case CalculatorErrc::DivisionByZero:
      return "division by zero";
    case CalculatorErrc::TypeMismatch:
      return "type mismatch in operation";
    default:
      return "unknown error";
  }
}

const CalculatorErrorCategory& calculator::calculator_error_category() {
  static CalculatorErrorCategory instance;
  return instance;
}

std::error_code calculator::make_error_code(CalculatorErrc e) {
  return {static_cast<int>(e), calculator_error_category()};
}