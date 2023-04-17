cmake_minimum_required(VERSION 3.24)
project(SDiZO)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(SDiZO
        DynamicArray.cpp
        DoublyLinkedList.cpp
        BinaryHeap.cpp
        BST.cpp
        Main.cpp)
