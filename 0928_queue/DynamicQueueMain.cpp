#include "DynamicQueue.hpp"
#include "woodpecker.hpp"
#include <cstdint>
#include <vector>

TEST("Empty Queue", 1) {
  DynamicQueue<int> queue;
  CHECK_EQ(queue.isEmpty(), true);
}

TEST("In Check", 1) {
  DynamicQueue<int> queue;
  for (int i = 1; i <= 500; i++)
    queue.in(i);
  CHECK_EQ(queue.isEmpty(), false);
}

TEST("Out and First Check", 1) {
  DynamicQueue<int> queue;
  for (int i = 0; i < 150; i++) {
    queue.in(i);
  }

  CHECK_EQ(queue.isEmpty(), false);

  for (int i = 0; i < 150; i++) {
    CHECK_EQ(queue.first(), i);
    CHECK_EQ(queue.out(), i);
  }

  CHECK_EQ(queue.isEmpty(), true);
}

TEST("Exceptions", 1) {
  DynamicQueue<int> queue;
  CHECK_EXC(UnderflowException, queue.first());
  CHECK_EXC(UnderflowException, queue.out());
}

struct bigobject {
private:
  std::vector<uint64_t> data;

public:
  bigobject() {
    data = std::vector<uint64_t>(100);
    for (uint64_t &i : data)
      i = random();
  }

  bool operator==(const bigobject &other) const {
    for (size_t i = 0; i < data.size(); i++)
      if (data[i] != other.data[i])
        return false;
    return true;
  }

  friend std::ostream &operator<<(std::ostream &o, const bigobject &obj);
};

std::ostream &operator<<(std::ostream &o, const bigobject &obj) {
  o << &obj;
  return o;
}

TEST("Performance test", 1) {
  {
    DynamicQueue<int> queue;

    MEASURE("Inserting and removing", 1500ms) {
      for (int i = 0; i < 5e6; i++) {
        queue.in(i);
      }

      for (int i = 0; i < 5e6; i++) {
        CHECK_EQ(queue.first(), i);
        CHECK_EQ(queue.out(), i);
      }
      CHECK_EQ(queue.isEmpty(), true);
    }
  }

  {
    const size_t SIZE = 50000;
    std::vector<bigobject> expected(SIZE);
    DynamicQueue<bigobject> queue;

    MEASURE("Inserting and removing", 1500ms) {
      for (size_t i = 0; i < SIZE; i++) {
        queue.in(expected[i]);
      }

      for (size_t i = 0; i < SIZE; i++) {
        CHECK_EQ(queue.first(), expected[i]);
        CHECK_EQ(queue.out(), expected[i]);
      }
      CHECK_EQ(queue.isEmpty(), true);
    }
  }
}

WOODPECKER_MAIN(-1, -1)
