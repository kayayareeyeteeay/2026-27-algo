#ifndef HEAP_EXCEPTIONS_HPP
#define HEAP_EXCEPTIONS_HPP

#include <exception>

class HeapException : public std::exception {
};

class InvalidIterator : public HeapException {
public:
    const char *what() const noexcept override { return "Az iterator invalid."; }
};

class InvalidIndex : public HeapException {
public:
    const char *what() const noexcept override { return "Az index invalid."; }
};

class EmptyHeap : public HeapException {
public:
    const char *what() const noexcept override { return "A kupac ures."; }
};

class HeapOverflow : public HeapException {
public:
    const char *what() const noexcept override { return "A kupac tele."; }
};

#endif // HEAP_EXCEPTIONS_HPP
