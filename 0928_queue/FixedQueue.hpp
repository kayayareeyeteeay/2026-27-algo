#ifndef ADATSZERK_L04_FIXEDQUEUE_HPP
#define ADATSZERK_L04_FIXEDQUEUE_HPP

#include "QueueExceptions.hpp"
#include <iostream>

template <class T> class FixedQueue {
public:
  FixedQueue() : array() {
    head = tail = 0;
    empty = true;
  }

  ~FixedQueue() = default;

  bool isEmpty() const {
    // TODO
    return empty;

  }

  bool isFull() const {
    // TODO
    return !empty and head == tail;

  }

  /*
   * Throws OverflowException when full
   */
  void in(T new_item) {
    // TODO
    if (isFull()) {
      throw OverflowException();
    }
    empty = false;
    array[tail] = new_item;
    tail = (tail + 1) % CAPACITY;
  }

  /*
   * Throws UnderflowException when empty
   */
  T out() {
    // TODO
    if (empty) {
      throw UnderflowException();
    }
     T ans = array[head];
    head = (head + 1) % CAPACITY;
    if (head == tail) {
      empty = true;
    }
    return ans;


  }

  /*
   * Throws UnderflowException when empty
   */
  T first() const {
    // TODO
    if (empty) {
      throw UnderflowException();
    }
    return array[head];

  }

  void print() const {
    if (isEmpty()) {
      return;
    }

    // Kerüljük el a segfaultot a hibás implementációnál
    if (head > CAPACITY || head < 0 || tail > CAPACITY || tail < 0)
      return;

    if (head < tail) { // alap eset, amíg a head elött van a tail
      for (int i = head; i < tail - 1; i++) {
        std::cout << array[i] << ", ";
      }
      std::cout << array[tail - 1] << std::endl;
    } else { // ha már körbe fordult a tail
      // akkor head-től a tömb végéig (ami valahol a sor közepén van)
      for (int i = head; i < CAPACITY; i++) {
        std::cout << array[i] << ", ";
      }
      for (int i = 0; i < tail; i++) { /// majd előről a tail-ig
        std::cout << array[i] << ", ";
      }
    }
  }

private:
  static const int CAPACITY = 10;
  T array[CAPACITY];
  int head, tail; // sor első eleme, sor első szabad helye
  bool empty;     // ha az előző kettő egyenlő akkor a sor vagy üres vagy teli
};

#endif // ADATSZERK_L04_FIXEDQUEUE_HPP
