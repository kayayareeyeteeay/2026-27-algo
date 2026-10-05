#include "heap.hpp"
#include "woodpecker.hpp"

#include <list>

TEST("Empty heap", 1) {
    Heap<float> h;
    CHECK_EQ(h.isempty(), true);
    CHECK_EXC(EmptyHeap, h.max());
    CHECK_EXC(EmptyHeap, h.delmax());
}

TEST("Basic insert", 1){
    Heap<int> h;
    h.insert(10);
    CHECK_EQ(h.max(), 10);
    CHECK_EQ(h.isempty(), false);
    CHECK_EQ(h.max(), 10);
    CHECK_EQ(h.delmax(), 10);
    CHECK_EQ(h.isempty(), true);
}

TEST("Basic insert2", 1){
    Heap<float> h;
    h.insert(10);
    CHECK_EQ(h.max(), 10);
    CHECK_EQ(h.isempty(), false);
    h.insert(8.5);
    CHECK_EQ(h.max(), 10);
    h.insert(12);
    CHECK_EQ(h.max(), 12);
}

TEST("Insert more elements", 1) {
    Heap<int> h;
    std::list<int> arr;
    int max = 0;
    for (int i = 0; i<13;i++) {
        if (i < 12) {
            int next = rand();
            arr.push_back(next);
            if (next > max)
                max = next;
            h.insert(next);
            CHECK_EQ(h.max(), max);
        } else {
            CHECK_EXC(HeapOverflow, h.insert(12));
        }
    }
    arr.sort();
    arr.reverse();
    for (int e: arr) {
        CHECK_EQ(h.isempty(), false);
        CHECK_EQ(h.max(), e);
        CHECK_EQ(h.delmax(), e);
    }
    CHECK_EQ(h.isempty(), true);
}

WOODPECKER_MAIN(1, 1);
