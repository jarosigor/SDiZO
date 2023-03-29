cmake_minimum_required(VERSION 3.24)
project(SDiZO)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(SDiZO
        Dynamic_array.cpp
        Dynamic_array.h Doubly_linked_list.h Doubly_linked_list.cpp Doubly_linked_list.cpp Binary_heap.h Binary_heap.cpp)
