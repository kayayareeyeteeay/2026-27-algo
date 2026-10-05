#include "BinaryTree.hpp"
#include "woodpecker.hpp"

#include<list>
#include<algorithm>

// Segédoperátor listák összehasonlításához
template<class T>
bool operator==(const std::list<T>& lhs, const std::list<T>& rhs) {
    if (lhs.size() != rhs.size()) return false;
    for (
      auto rit = lhs.begin(), lit = rhs.begin(); 
      rit != lhs.end() && lit != rhs.end();
      ++lit,++rit
    ){
        if (*rit != *lit) return false;
    }
    return true;
}

// Test for checking concept
// TEST("Cannot be compiled", 1) {
//     class valami {
//     public:
//         int a;
//     };
//
//     BinaryTree<valami> tree;
// }

TEST("Empty tree", 1) {
    const BinaryTree<float> bt;
    CHECK_EQ(bt.isempty(), true);
    CHECK_EQ(bt.size() , 0.0);
}

TEST("Basic insert", 1){
    BinaryTree<int> bt;
    bt.insert(10);
    CHECK_EQ(bt.find(10), true);
    bt.insert(5);
    CHECK_EQ(bt.find(5), true);
    bt.insert(15);
    CHECK_EQ(bt.find(15), true);
    CHECK_EQ(bt.size(), 3uz);
    CHECK_EQ(bt.min(), 5);
    CHECK_EQ(bt.max(), 15);
}

TEST("Insert more elements", 1) {
    std::list<int> myArray = { 44, 61, 68, 67, 40, 20, 74, 17, 36, 60 };

    BinaryTree<int> bt;
    for (const int &i : myArray) {
        bt.insert(i);
        CHECK_EQ(bt.find(i), true);
    }

    CHECK_EQ(bt.size(), myArray.size());
    CHECK_EQ(bt.min(), 17);
    CHECK_EQ(bt.max(), 74);
    myArray.sort();
    CHECK_EQ(myArray == bt.inorder(), true);
}

TEST("Copy tree", 1) {
    std::list<int> myArray = { 44, 61, 68, 67, 40, 20, 74, 17, 36, 60 };

    BinaryTree<int> bt;
    for (const int &i : myArray) bt.insert(i);
    CHECK_EQ(bt.size(), myArray.size());

    const BinaryTree<int> copy(bt);
    myArray.sort();
    CHECK_EQ(copy.isempty(), false);
    CHECK_EQ(copy.size(), myArray.size());
    CHECK_EQ(myArray == copy.inorder(), true);
}


TEST("Delete elements", 1) {
    BinaryTree<int> bt;
    bt.insert(10);
    bt.insert(5);
    bt.insert(15);
    CHECK_EQ(bt.size(), 3uz);
    CHECK_EQ(bt.min(), 5);
    CHECK_EQ(bt.max(), 15);

    bt.remove(10);
    CHECK_EQ(bt.size(), 2uz);
    CHECK_EQ(bt.min(), 5);
    CHECK_EQ(bt.max(), 15);

    bt.remove(5);
    CHECK_EQ(bt.size(), 1uz);
    CHECK_EQ(bt.min(), 15);
    CHECK_EQ(bt.max(), 15);

    bt.remove(15);
    CHECK_EQ(bt.size(), 0uz);
    CHECK_EQ(bt.isempty(), true);
}

TEST("Check exceptions", 1) {
    BinaryTree<float> bt;
    CHECK_EXC(internal_error, bt.min());
    CHECK_EXC(internal_error, bt.max());
    CHECK_EXC(internal_error, bt.getroot());

    bt.insert(1.0f);
    CHECK_NOEXC(bt.min());
    CHECK_NOEXC(bt.max());
    CHECK_NOEXC(bt.getroot());

    bt.remove(1.0f);
    CHECK_EXC(internal_error, bt.min());
    CHECK_EXC(internal_error, bt.max());
    CHECK_EXC(internal_error, bt.getroot());
}

TEST("Large test with random numbers", 1) {
    BinaryTree<long> bt;
    std::list<long> myArray;

    MEASURE("Measuring insertion efficiency", std::chrono::milliseconds(200L)) {
        for (size_t i = 0; i < 1e5L; i++) {
            long num = rand();
            bt.insert(num);
            myArray.push_back(num);
        }
    }

    myArray.sort();
    myArray.unique();
    std::list<long> treeArray = bt.inorder();
    CHECK_EQ(std::ranges::is_sorted(treeArray), true);
    CHECK_EQ(myArray == treeArray, true);

    for (const long &i : myArray) {
        bt.remove(i);
        CHECK_EQ(bt.find(i), false);
    }
    CHECK_EQ(bt.size(), 0uz);
    CHECK_EQ(bt.isempty(), true);
}

WOODPECKER_MAIN(1, 1);
