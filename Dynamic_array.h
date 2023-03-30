#ifndef STD_LIB
#define STD_LIB
#include <iostream>
#endif

#ifndef SDIZO_DYNAMIC_ARRAY_H
#define SDIZO_DYNAMIC_ARRAY_H

class Dynamic_array {
    private:
        int* array = NULL;
        int capacity;
        int size;
        int CAP_GROW = 2;
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

#endif