#ifndef ADATSZERK_L05_BINARYTREEEXCEPTIONS_HPP
#define ADATSZERK_L05_BINARYTREEEXCEPTIONS_HPP

#include <exception>

class copy_not_implemented : public std::exception
{
public:
    const char *what() const throw() { return "Masolas nincs implementalva!"; }
};

class internal_error : public std::exception
{
    const char *message;

public:
    internal_error(const char *msg = "Hiba van az implementacioban!") : message(msg) {}

    const char *what() const throw() { return message; }
};

class invalid_binary_search_tree : public std::exception
{
public:
    const char *what() const throw() { return "Serulnek a binaris keresofa kriteriumok!"; }
};

class method_not_implemented : public std::exception {
public:
    const char *what() const throw() { return "A metodus nincs implementalva!"; }
};

#endif //ADATSZERK_L05_BINARYTREEEXCEPTIONS_HPP
