#include "Binary_heap.h"

BinaryHeap::BinaryHeap() {
    capacity = 1;
    heap_size = 0;
    heap = new int[capacity];
}

BinaryHeap::BinaryHeap(int capacity) {
    this->capacity = capacity;
    heap_size = 0;
    heap = new int[capacity];
}

// -1 as a result means our node is a root
auto BinaryHeap::get_parent(int index) {
    return (index-1)/2 < heap_size ? (index-1)/2 : -1;
}

// -1 as a result means our node is a leaf
auto BinaryHeap::get_left_child(int index) {
    return (index*2)+1 < heap_size ? index*2+1 : -1;

}
// -1 as a result means our node is a leaf
auto BinaryHeap::get_right_child(int index) {
    return (index*2)+2 < heap_size ? index*2+2 : -1;
}

auto BinaryHeap::heapify_up(int index) {
    while (index != 0) {
        int parent = get_parent(index);
        if (heap[index] > heap[parent]) {
            std::swap(heap[index], heap[parent]);
            index = parent;
        }
        else break;
    }
}

auto BinaryHeap::heapify_down(int index) {
    while (index != -1) {
        int left_child = get_left_child(index);
        int right_child = get_right_child(index);
        if (heap[index] < heap[left_child]) {
            std::swap(heap[index], heap[left_child]);
            index = left_child;
        } else if (heap[index] < heap[right_child]) {
            std::swap(heap[index], heap[right_child]);
            index = right_child;
        } else break;
    }
}

auto BinaryHeap::add(int value) {
    if (heap_size == capacity) {
        std::cerr << "!!!No more space available!!!";
    }

    int i = heap_size;
    heap[i] = value;
    heap_size++;

    heapify_up(i);
}

auto BinaryHeap::remove_top() {
    if (heap_size == 0) {
        std::cerr << "!!!Heap is already empty!!!";
        return false;
    }
    heap_size--;
    heap[0] = heap[heap_size];
    heap[heap_size] = NULL;
    heapify_down(0);
    return true;
}

auto BinaryHeap::print() {
    int num_levels = floor(log2(heap_size)) + 1;
    int curr_lvl = 0;
    int curr_idx = 0;

    for (int level = 0; level < num_levels; level++) {
        int num_nodes_in_level = pow(2, level);
        std::cout << "POZIOM-" << curr_lvl << ": ";
        for (int i = 0; i < num_nodes_in_level; i++) {
            int node_value = (curr_idx < heap_size) ? heap[curr_idx] : 0;
            std::cout << node_value << " ";
            curr_idx++;
            if (curr_idx >= heap_size) {
                break;
            }
        }

        curr_lvl++;
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    BinaryHeap binaryHeap = BinaryHeap(10);
    binaryHeap.add(4);
    binaryHeap.add(2);
    binaryHeap.add(49);
    binaryHeap.add(1);
    binaryHeap.add(169);
    binaryHeap.print();
    binaryHeap.remove_top();
    binaryHeap.print();
    return 0;
}



