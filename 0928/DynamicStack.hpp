#ifndef ADATSZERK_L03_DYNAMICSTACK_HPP
#define ADATSZERK_L03_DYNAMICSTACK_HPP

#include <iostream>
#include "exceptions.hpp"

template <class T>
class DynamicStack {
public:
  DynamicStack() { pHead = nullptr; }

  ~DynamicStack() {
    while (!isEmpty()) {
      pop();
    }
  }

  bool isEmpty() const {
    // TODO
    return pHead == nullptr;
  }

  void push(T new_item) {
    // TODO
    Node *new_node = new Node(new_item, pHead);
    pHead = new_node;

    //static_cast<void>(new_item);
  }

  T top() const {
    // TODO
    if (isEmpty()) {throw UnderflowException();}
    return pHead->value;

  }

  T pop() {
    // TODO
    if (isEmpty()) {throw UnderflowException();}
    T ans = pHead->value;
    Node *tmp = pHead;
    pHead = pHead->pNext;
    delete tmp;
    return ans;
  }

  void print() const {
    for (const Node *i = pHead; i != nullptr; i = i->pNext) {
      std::cout << i->value << " ";
    }
  }

  DynamicStack(const DynamicStack &other) {
    if (nullptr != other.pHead) {
      pHead = new Node(other.pHead->value);
      Node *copied = pHead;
      for (Node *i = other.pHead->pNext; i != nullptr; i = i->pNext) {
        copied->pNext = new Node(i->value);
        copied = copied->pNext;
      }
    }
  }

  DynamicStack(DynamicStack &&other) noexcept {
    // pHead = std::exchange(other.pHead, nullptr);
    pHead = other.pHead;
    other.pHead = nullptr;
  }

  DynamicStack &operator=(const DynamicStack &rhs) {
    if (this != &rhs) {
      while (!isEmpty()) {
        pop();
      }
      if (nullptr != rhs.pHead) {
        pHead = new Node(rhs.pHead->value);
        Node *copied = pHead;
        for (Node *i = rhs.pHead->pNext; i != nullptr; i = i->pNext) {
          copied->pNext = new Node(i->value);
          copied = copied->pNext;
        }
      }
    }
    return *this;
  }

  DynamicStack &operator=(DynamicStack &&rhs) noexcept {
    if (this != &rhs) {
      while (!isEmpty()) {
        pop();
      }
      // pHead = std::exchange(other.pHead, nullptr);
      pHead = rhs.pHead;
      rhs.pHead = nullptr;
    }
    return *this;
  }

private:
  class Node {
  public:
    T value;
    Node *pNext;

    Node() : value(0), pNext(nullptr) {}
    Node(const T &_value) : value(_value), pNext(nullptr) {}
    Node(const T &_value, Node *_pNext) : value(_value), pNext(_pNext) {}
  };
  Node *pHead;
};

#endif // ADATSZERK_L03_DYNAMICSTACK_HPP
