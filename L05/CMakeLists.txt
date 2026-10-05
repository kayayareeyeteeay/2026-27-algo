cmake_minimum_required(VERSION 3.31)
project(adatszerk_L05)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic")

include_directories("../" "./")

add_executable(L05_BinaryTree BinaryTree/BinaryTreeMain.cpp BinaryTree/BinaryTree.hpp BinaryTree/BinaryTreeExceptions.hpp)
add_executable(L05_Heap heap/HeapMain.cpp heap/heap.hpp heap/heap_exceptions.hpp)

set_target_properties(L05_BinaryTree PROPERTIES OUTPUT_NAME "L05_BinaryTree.out")
set_target_properties(L05_Heap PROPERTIES OUTPUT_NAME "L05_Heap.out")
