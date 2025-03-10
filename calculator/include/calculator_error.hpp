#ifndef CALCULATOR_CALCULATOR_ERROR_HPP_
#define CALCULATOR_CALCULATOR_ERROR_HPP_

#include <system_error>
#include <string>

namespace calculator {
enum class CalculatorErrc {
  Success = 0,
  NotImplemented,
  DivisionByZero,
  TypeMismatch,
};

class CalculatorErrorCategory final : public std::error_category {
public:
  [[nodiscard]] const char* name() const noexcept override;

  [[nodiscard]] std::string message(int ev) const override;
};

const CalculatorErrorCategory& calculator_error_category();

std::error_code make_error_code(CalculatorErrc e);

} // namespace calculator

template <>
struct std::is_error_code_enum<calculator::CalculatorErrc> : true_type {};

#endif // !CALCULATOR_CALCULATOR_ERROR_HPP_