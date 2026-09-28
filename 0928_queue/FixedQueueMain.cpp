#include "FixedQueue.hpp"
#include "woodpecker.hpp"
#include <array>
#include <cstdint>

struct kilobyte {
private:
  std::array<uint8_t, 1024> data;

public:
  kilobyte() : data() {
    for (uint8_t &i : data)
      i = uint8_t(rand() % 255);
  }

  constexpr bool operator==(const kilobyte &other) const {
    for (size_t i = 0; i < data.size(); i++) {
      if (data[i] != other.data[i])
        return false;
    }
    return true;
  }

  friend std::ostream &operator<<(std::ostream &o, kilobyte k);
};

std::ostream &operator<<(std::ostream &o, kilobyte k) {
  uint32_t checksum = 0;
  for (uint8_t i : k.data)
    checksum += i;
  o << checksum;
  return o;
}

TEST("Empty Queue", 1) {
  std::cout << "EMPTY QUEUE TEST" << std::endl;
  FixedQueue<int> queue;
  CHECK_EQ(queue.isEmpty(), true);
  CHECK_EQ(queue.isFull(), false);
}

TEST("In and First Check", 1) {
  {
    std::cout << "IN AND FIRST CHECK" << std::endl;
    FixedQueue<int> queue;
    for (int i = 1; i <= 5; i++) {
      queue.in(i);
    }
    std::cout << "After 5 elements: ";
    queue.print();

    for (int i = 6; i <= 10; i++) {
      queue.in(i);
    }
    std::cout << "After 10 elements: ";
    queue.print();

    CHECK_EQ(queue.isEmpty(), false);
    CHECK_EQ(queue.isFull(), true);
  }

  {
    FixedQueue<kilobyte> queue;
    for (size_t i = 0; i < 10; i++) {
      queue.in(kilobyte());
    }

    CHECK_EQ(queue.isEmpty(), false);
    CHECK_EQ(queue.isFull(), true);
  }
}

TEST("Demonstration of circular representation", 1) {
  std::cout << "DEMONSTRATING CIRCULAR REPRESENTATION" << std::endl;
  FixedQueue<int> queue;
  std::cout << "Adding 10 elements" << std::endl;
  for (int i = 0; i < 10; i++)
    queue.in(i);
  CHECK_EQ(queue.isEmpty(), false);

  int element;
  std::cout << "First element: " << (element = queue.out()) << std::endl;
  CHECK_EQ(element, 0);
  std::cout << "Second element: " << (element = queue.out()) << std::endl;
  CHECK_EQ(element, 1);
  std::cout << "Third element: " << (element = queue.out()) << std::endl;
  CHECK_EQ(element, 2);
  std::cout << "The queue after removing 3 elements: ";
  queue.print();
  std::cout << "Adding 3 new elements" << std::endl;
  for (int i = 11; i <= 13; i++)
    queue.in(i);
  std::cout << "Queue after adding 11, 12, 13 as new elements: ";
  queue.print();

  CHECK_EQ(queue.isEmpty(), false);
  CHECK_EQ(queue.isFull(), true);
}

TEST("Out Check", 1) {
  {
    std::cout << "OUT CHECK" << std::endl;
    FixedQueue<int> queue;
    for (int i = 0; i < 10; i++)
      queue.in(i);

    CHECK_EQ(queue.isEmpty(), false);
    CHECK_EQ(queue.isFull(), true);

    for (int i = 0; i < 10; i++) {
      std::cout << "Removing " << i << ". element" << std::endl;
      CHECK_EQ(queue.out(), i);
    }

    CHECK_EQ(queue.isEmpty(), true);
    CHECK_EQ(queue.isFull(), false);
  }
  {
    std::array<kilobyte, 10> expected{};
    FixedQueue<kilobyte> queue;
    for (size_t i = 0; i < expected.size(); i++)
      queue.in(expected[i]);

    CHECK_EQ(queue.isEmpty(), false);
    CHECK_EQ(queue.isFull(), true);

    for (size_t i = 0; i < expected.size(); i++) {
      CHECK_EQ(queue.out(), expected[i]);
    }

    CHECK_EQ(queue.isEmpty(), true);
    CHECK_EQ(queue.isFull(), false);
  }
}

TEST("Exceptions", 1) {

  {
    FixedQueue<int> queue;
    CHECK_EXC(UnderflowException, queue.first());
    CHECK_EXC(UnderflowException, queue.out());
    CHECK_NOEXC(queue.isEmpty());
    CHECK_NOEXC(queue.isFull());

    for (int i = 0; i < 10; i++)
      queue.in(i);

    CHECK_EXC(OverflowException, queue.in(1));
    CHECK_NOEXC(queue.first());
    CHECK_NOEXC(queue.out());
    CHECK_NOEXC(queue.isEmpty());
    CHECK_NOEXC(queue.isFull());

    for (int i = 0; i < 9; i++)
      queue.out();

    CHECK_EXC(UnderflowException, queue.first());
    CHECK_EXC(UnderflowException, queue.out());
    CHECK_NOEXC(queue.isEmpty());
    CHECK_NOEXC(queue.isFull());
  }

  {
    FixedQueue<kilobyte> queue;
    CHECK_EXC(UnderflowException, queue.first());
    CHECK_EXC(UnderflowException, queue.out());
    CHECK_NOEXC(queue.isEmpty());
    CHECK_NOEXC(queue.isFull());

    for (int i = 0; i < 10; i++)
      queue.in(kilobyte());

    CHECK_EXC(OverflowException, queue.in(kilobyte()));
    CHECK_NOEXC(queue.first());
    CHECK_NOEXC(queue.out());
    CHECK_NOEXC(queue.isEmpty());
    CHECK_NOEXC(queue.isFull());

    for (int i = 0; i < 9; i++)
      queue.out();

    CHECK_EXC(UnderflowException, queue.first());
    CHECK_EXC(UnderflowException, queue.out());
    CHECK_NOEXC(queue.isEmpty());
    CHECK_NOEXC(queue.isFull());
  }
}

WOODPECKER_TEST_MAIN(1, 1)
