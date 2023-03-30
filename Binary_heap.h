#ifndef STD_LIB
#define STD_LIB
#include <iostream>
#include <bits/stdc++.h>
#endif

#ifndef SDIZO_BINARY_HEAP_H
#define SDIZO_BINARY_HEAP_H

//Max binary heap implementation
class BinaryHeap {
private:
    int capacity;
    int *heap;
    int heap_size;
public:
    BinaryHeap();
    BinaryHeap(int capacity);
    auto remove_top();
    auto add(int value);
    auto heapify_up(int index);
    auto heapify_down(int index);
    auto get_parent(int index);
    auto get_left_child(int index);
    auto get_right_child(int index);
    auto print();
};

#endif //SDIZO_BINARY_HEAP_H
