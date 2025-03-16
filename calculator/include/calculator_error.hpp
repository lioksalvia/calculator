#ifndef LIOKSALVIA_CALCULATOR_CALCULATOR_ERROR_HPP_
#define LIOKSALVIA_CALCULATOR_CALCULATOR_ERROR_HPP_

#include <string>
#include <system_error>

#include "export.hpp"

namespace lioksalvia::calculator {

enum class LIOKSALVIA_CALCULATOR_API calculator_errc {
  success = 0, not_implemented, division_by_zero, type_mismatch,
};

class LIOKSALVIA_CALCULATOR_API calculator_category final : public std::error_category {
  public:
    [[nodiscard]] const char* name() const noexcept override;
    [[nodiscard]] std::string message(int ev) const override;
};

LIOKSALVIA_CALCULATOR_API const calculator_category& get_calculator_category();
LIOKSALVIA_CALCULATOR_API std::error_code make_error_code(calculator_errc e);

} // namespace lioksalvia::calculator

template <>
struct std::is_error_code_enum<lioksalvia::calculator::calculator_errc> : true_type {
};

#endif // !LIOKSALVIA_CALCULATOR_CALCULATOR_ERROR_HPP_