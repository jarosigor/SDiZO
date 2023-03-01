#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H
#include <stdio.h>
#include <iostream>
#endif

class Dynamic_array {
    private:
        int* array;
        int capacity;
        int size;
    public:
        Dynamic_array();
        ~Dynamic_array();
        auto add_front(int value) -> bool;
        auto add_back(int value) -> bool;
        auto add_at(int value, int position) -> bool;
        auto remove_front() -> bool;
        auto remove_back() -> bool;
        auto remove_at(int position) -> bool;
        auto increase_capacity() -> void;
        auto decrease_capacity() -> void;
        auto print();
};