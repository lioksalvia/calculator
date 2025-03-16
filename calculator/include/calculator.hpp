#ifndef LIOKSALVIA_CALCULATOR_CALCULATOR_HPP_
#define LIOKSALVIA_CALCULATOR_CALCULATOR_HPP_

#include "export.hpp"

namespace lioksalvia::calculator {

class LIOKSALVIA_CALCULATOR_API calculator final {
  public:
    static int add(int a, int b);
};

} // namespace lioksalvia::calculator

#endif  // !LIOKSALVIA_CALCULATOR_CALCULATOR_HPP_