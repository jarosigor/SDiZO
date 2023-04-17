#ifndef STD_LIB
#define STD_LIB
#include <iostream>
#include <cmath>
#endif

#ifndef SDIZO_DYNAMIC_ARRAY_H
#define SDIZO_DYNAMIC_ARRAY_H

class DynamicArray {
    private:
        int* array = NULL;
        int capacity;
        int size;
        int CAP_GROW = 2;
    public:
        DynamicArray();
        DynamicArray(int arr_size);
        ~DynamicArray();
        bool add_front(int value);
        bool add_back(int value);
        bool add_at(int value, int position);
        bool remove_front();
        bool remove_back();
        bool remove_at(int position);
        void increase_capacity();
        void decrease_capacity();
        void print();
        int get_size();
};

#endif