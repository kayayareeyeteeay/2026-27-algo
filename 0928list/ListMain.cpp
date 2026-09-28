#include "List.hpp"
#include "woodpecker.hpp"
#include <cstdint>

TEST("Empty", 1) {
  const List<int> l;
  CHECK_EQ(l.isEmpty(), true);
  CHECK_EQ(l.isCurNull(), true);
  CHECK_EXC(UnderFlowException, l.getValue());
}

TEST("Insertion", 1) {

  {
    List<int> l;
    l.insertFirst(0);

    CHECK_EQ(l.getValue(), 0);
    CHECK_EQ(l.isFirst(), true);
    CHECK_EQ(l.isLast(), true);
    CHECK_EQ(l.isEmpty(), false);
    CHECK_EQ(l.isCurNull(), false);
    for (int i = 1; i < 14; i++) {
      l.insertLast(i);
      CHECK_EQ(l.getValue(), i);
    }
    l.insertFirst(-1);
    CHECK_EQ(l.getValue(), -1);
    l.insertAfter(0);
    CHECK_EQ(l.getValue(), 0);
    l.insertFirst(-3);
    CHECK_EQ(l.getValue(), -3);
    l.insertAfter(-2);
    CHECK_EQ(l.getValue(), -2);
  }

  {
    List<double> l = List<double>();
    l.insertFirst(0.0);
    l.insertBefore(-1.0);
    l.stepNext();
    l.insertAfter(1.0);

    l.toFirst();
    for (int i = -1; i <= 1; i++) {
      CHECK_EQ(l.getValue(), double(i));
      l.removeFirst();
      l.toFirst();
    }
    CHECK_EQ(l.isEmpty(), true);
  }
}

TEST("Removal", 1) {
  List<std::string> l;
  l.insertFirst("-10");
  CHECK_EQ(l.getValue(), "-10");
  l.insertAfter("-9");
  CHECK_EQ(l.getValue(), "-9");
  l.insertAfter("-8");
  CHECK_EQ(l.getValue(), "-8");
  l.insertLast("-7");
  CHECK_EQ(l.getValue(), "-7");

  l.removeFirst();
  l.toFirst();
  CHECK_EQ(l.getValue(), "-9");
  l.removeLast();
  l.toLast();
  CHECK_EQ(l.getValue(), "-8");
  l.toFirst();
  l.stepNext();
  l.removeCur();
  l.toLast();
  CHECK_EQ(l.getValue(), "-9");
}

TEST("Internal structure", 1) {
  const std::vector<int> expected = {-3, -2, -1, 0, 1,  2,  3,  4, 5,
                                     6,  7,  8,  9, 10, 11, 12, 13};
  List<int> l;
  for (const int &i : expected) {
    l.insertLast(i);
    CHECK_EQ(l.getValue(), i);
  }
  CHECK_EQ(l.isEmpty(), false);
  CHECK_EQ(l.isCurNull(), false);
  INFO("CHECKING LIST SIZE");
  const std::vector<int> actual = l.toVector();
  CAPTURE(actual.size());
  CAPTURE(expected.size());
  CHECK_EQ(actual.size(), expected.size());
  INFO("CHECKING LIST ELEMENTS");
  {
    for (size_t i = 0; i < expected.size(); i++) {
      CHECK_EQ(actual[i], expected[i]);
    }
  }
}

TEST("Copy constructor", 1) {
  const std::vector<int> v0 = {1, 2, 3};
  List<int> l1;
  for (int i : v0)
    l1.insertLast(i);

  List<int> l2(l1);
  CHECK_EQ(l1.isEmpty(), false);
  CHECK_EQ(l2.isEmpty(), false);

  l1.removeFirst();
  l2.insertLast(4);

  std::vector<int> act1 = l1.toVector();
  CHECK_EQ(act1.size(), 2uz);
  CHECK_EQ(act1[0], v0[1]);
  CHECK_EQ(act1[1], v0[2]);

  std::vector<int> act2 = l2.toVector();
  CHECK_EQ(act2.size(), 4uz);
  CHECK_EQ(act2[0], v0[0]);
  CHECK_EQ(act2[3], 4);
}

TEST("Copy assignment", 1) {
  const std::vector<int> v1 = {1, 2};
  const std::vector<int> v2 = {3, 4, 5};

  List<int> l1;
  List<int> l2;
  for (int i : v1)
    l1.insertLast(i);
  for (int i : v2)
    l2.insertLast(i);

  l1 = l2;

  std::vector<int> actual1 = l1.toVector();
  CHECK_EQ(actual1.size(), v2.size());
  for (size_t i = 0; i < actual1.size(); i++) {
    CHECK_EQ(actual1[i], v2[i]);
  }

  l2.removeFirst();
  CHECK_EQ(l2.toVector().size(), v2.size() - 1);
  CHECK_EQ(l1.toVector().size(), v2.size());

  l1 = l1;

  std::vector<int> actual_self = l1.toVector();
  CHECK_EQ(actual_self.size(), v2.size());
  for (size_t i = 0; i < actual_self.size(); i++) {
    CHECK_EQ(actual_self[i], v2[i]);
  }
}

TEST("Move assignment", 1) {
  const std::vector<int> expected_target = {1, 2, 3};
  const std::vector<int> expected_overwritten = {9, 8, 7, 6};

  List<int> l1;
  List<int> l2;
  for (int i : expected_target)
    l1.insertLast(i);
  for (int i : expected_overwritten)
    l2.insertLast(i);

  l2 = std::move(l1);

  CHECK_EQ(l1.isEmpty(), true);

  CHECK_EQ(l2.isEmpty(), false);
  std::vector<int> actual = l2.toVector();
  CHECK_EQ(actual.size(), expected_target.size());
  for (size_t i = 0; i < actual.size(); i++) {
    CHECK_EQ(actual[i], expected_target[i]);
  }

  l2.removeFirst();
  CHECK_EQ(l2.toVector().size(), expected_target.size() - 1);
}

WOODPECKER_MAIN(-1, -1)
