#ifndef EXCEPTIONS_L04_HPP
#define EXCEPTIONS_L04_HPP

#include <exception>

class OverflowException : std::exception {
  const char *what() const noexcept override { return "Overflow"; }
};

class UnderflowException : std::exception {
  const char *what() const noexcept override { return "Underflow"; }
};

class InternalError : std::exception {
  const char *what() const noexcept override { return "Internal error"; }
};

#endif // EXCEPTIONS_L04
