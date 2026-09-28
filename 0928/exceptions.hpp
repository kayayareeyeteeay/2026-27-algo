#ifndef EXCEPTIONS_L03_HPP
#define EXCEPTIONS_L03_HPP

#include <exception>

class OverflowException : std::exception {
  const char *what() const noexcept override { return "Overflow"; }
};

class UnderflowException : std::exception {
  const char *what() const noexcept override { return "Underflow"; }
};

#endif // EXCEPTIONS_L03
