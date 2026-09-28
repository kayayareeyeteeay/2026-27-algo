cmake_minimum_required(VERSION 4.3)
project(0928dynamic)

set(CMAKE_CXX_STANDARD 20)

add_executable(0928dynamic
        woodpecker.hpp
        DynamicQueue.hpp
        DynamicQueue.hpp
        QueueExceptions.hpp
        DynamicQueueMain.cpp)
