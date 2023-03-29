//
// Created by igor on 29.03.23.
//

#ifndef SDIZO_BINARY_HEAP_H
#define SDIZO_BINARY_HEAP_H

class BinaryHeap {
public:
    BinaryHeap();
    BinaryHeap(int capacity);
    auto remove();
    auto add();
    auto heapify();
    auto get_parent(int index);
    auto get_left_child(int index);
    auto get_right_child(int index);
private:
    int capacity;
    int *heap;
    int heap_size;
};

#endif //SDIZO_BINARY_HEAP_H
