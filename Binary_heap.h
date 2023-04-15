#ifndef STD_LIB
#define STD_LIB
#include <iostream>
#include <cmath>
#endif

#ifndef SDIZO_BINARY_HEAP_H
#define SDIZO_BINARY_HEAP_H

// Kopiec maksymalny
class BinaryHeap {
private:
    int capacity;
    int *heap;
    int heap_size;
public:
    BinaryHeap();
    BinaryHeap(int capacity);
    bool remove_top();
    void add(int value);
    void heapify_up(int index);
    void heapify_down(int index);
    int get_parent(int index);
    int get_left_child(int index);
    int get_right_child(int index);
    void print();
};

#endif //SDIZO_BINARY_HEAP_H
