#ifndef ADATSZERK_L04_DYNAMICQUEUE_HPP
#define ADATSZERK_L04_DYNAMICQUEUE_HPP

#include "QueueExceptions.hpp"
#include <iostream>

template <class T> class DynamicQueue {
public:
  DynamicQueue() : head{nullptr}, tail{nullptr} {}
  DynamicQueue(const DynamicQueue &other) : head{nullptr}, tail{nullptr} {
    for (const Node *node = other.head; node != nullptr; node = node->pNext) {
      in(node->value);
    }
  }

  ~DynamicQueue() {
    while (!isEmpty()) {
      out();
    }
  }

  bool isEmpty() const {
    // TODO
    return true;
  }

  void in(T new_item) {
    // TODO
    static_cast<void>(new_item);
  }

  T out() {
    // TODO
    return T();
  }

  T first() const {
    // TODO
    return T();
  }

  void print() const {
    for (const Node *i = head; i != nullptr; i = i->pNext) {
      std::cout << i->value << " ";
    }
  }

  DynamicQueue(DynamicQueue &&other) : head{other.head}, tail{other.tail} {
    other.head = other.tail = nullptr;
  }

  DynamicQueue &operator=(DynamicQueue const &rhs) {
    if (&rhs != this) {
      // RAII -- copy ctor
      DynamicQueue temp{rhs};
      temp.swap(*this);
      // temp destruktora elintézi a mi régi implementációnkat
    }

    return *this;
  }

  DynamicQueue &operator=(DynamicQueue &&rhs) noexcept {
    swap(rhs);
    return *this;
  }

  void swap(DynamicQueue &other) noexcept {
    std::swap(this->head, other.head);
    std::swap(this->tail, other.tail);
  }

private:
  struct Node {
    T value;
    Node *pNext;

    Node() : value(), pNext(nullptr) {}
    explicit Node(T _value) : value(_value), pNext(nullptr) {}
    Node(T _value, Node *_pNext) : value(_value), pNext(_pNext) {}
  };

  Node *head, *tail;
};

#endif // ADATSZERK_L04_DYNAMICQUEUE_HPP
