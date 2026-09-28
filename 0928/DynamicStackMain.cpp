#include "DynamicStack.hpp"
#include "woodpecker.hpp"

TEST("Empty stack", 1) {
  DynamicStack<int> stack;
  CHECK_EQ(stack.isEmpty(), true);
}

TEST("Adding elements", 1) {
  DynamicStack<int> stack;
  CHECK_EQ(stack.isEmpty(), true);
  for (int i = 0; i < 10; i++) {
    stack.push(i);
    CHECK_EQ(stack.top(), i);
    CHECK_EQ(stack.isEmpty(), false);
  }
  CHECK_EQ(stack.isEmpty(), false);
}

TEST("Removing elements", 1) {
  DynamicStack<int> stack;
  CHECK_EQ(stack.isEmpty(), true);
  for (int i = 0; i < 10; i++) {
    stack.push(i);
    CHECK_EQ(stack.top(), i);
    CHECK_EQ(stack.isEmpty(), false);
  }

  for (int i = 9; i >= 0; i--) {
    CHECK_EQ(stack.top(), i);
    CHECK_EQ(stack.pop(), i);
  }
  CHECK_EQ(stack.isEmpty(), true);
}

TEST("Exceptions", 1){
  DynamicStack<int> stack;
  CHECK_EXC(UnderflowException, stack.top());
  CHECK_EXC(UnderflowException, stack.pop());
}

WOODPECKER_MAIN(-1, -1)
