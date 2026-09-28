#ifndef ADATSZERK_L04_LISTEXCEPTIONS_HPP
#define ADATSZERK_L04_LISTEXCEPTIONS_HPP

#include <exception>

class UnderFlowException : public std::exception {
public:
  const char *what() const noexcept override { return "Alulcsordulas!"; }
};

class CurNullException : public std::exception {
public:
  const char *what() const noexcept override {
    return "Nincs aktualis elem kivalasztva!";
  }
};

class InvalidIterator : public std::exception {
public:
  const char *what() const noexcept override { return "Ervenytelen iterator!"; }
};

#endif // ADATSZERK_L04_LISTEXCEPTIONS_HPP
