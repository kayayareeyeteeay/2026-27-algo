#ifndef ADATSZERK_L03_FIXEDINTSTACK_HPP
#define ADATSZERK_L03_FIXEDINTSTACK_HPP

#include "exceptions.hpp"
#include <iostream>

class FixedIntStack {
public:
  FixedIntStack() : array() {
    head = 0;
    // TODO

  }

  ~FixedIntStack() = default;

  bool isEmpty() const {
    // TODO
    return head == 0;
  }

  void push(int new_item) {
    // TODO
    if (head == CAPACITY) {throw OverflowException();}
    array[head] = new_item;
    head++;
  }

  int top() const {
    // TODO
    if (head==0){throw UnderflowException();}
    return array[head-1];
  }

  int pop() {
    // TODO
    if (head==0){throw UnderflowException();}
    head--;
    return array[head];
  }

  void print() const {
    for (int i = 0; i < head; i++)
      std::cout << array[i] << (i == head - 1 ? "" : ", ");
  }

private:
  static const int CAPACITY = 10;
  int array[CAPACITY];
  int head;
};

#endif // ADATSZERK_L03_FIXEDINTSTACK_HPP
