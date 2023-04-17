#include "BinaryHeap.h"

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



// -1 oznacza ze nasz wezel jest korzeniem
int BinaryHeap::get_parent(int index) {
    return (index-1)/2 < heap_size ? (index-1)/2 : -1;
}

// -1 oznacza lisc
int BinaryHeap::get_left_child(int index) {
    return (index*2)+1 < heap_size ? 2*index+1 : -1;

}
// -1 oznacza lisc
int BinaryHeap::get_right_child(int index) {
    return (index*2)+2 < heap_size ? 2*index+2 : -1;
}

// przywracanie wlasnosci kopca w gore kopca od danego indeksu
void BinaryHeap::heapify_up(int index) {
    while (index != 0) {
        int parent = get_parent(index);
        if (parent != -1 && heap[index] > heap[parent]) {
            std::swap(heap[index], heap[parent]);
            index = parent;
        }
        else break;
    }
}

// przywracanie wlasnosci kopca w dol od danego indeksu
void BinaryHeap::heapify_down(int index) {
    while (index != 0) {
        int left_child = get_left_child(index);
        int right_child = get_right_child(index);
        if (left_child != -1 && heap[index] < heap[left_child]) {
            std::swap(heap[index], heap[left_child]);
            index = left_child;
        } else if (right_child != -1 && heap[index] < heap[right_child]) {
            std::swap(heap[index], heap[right_child]);
            index = right_child;
        } else break;
    }
}

void BinaryHeap::add(int value) {
    if (heap_size == capacity) {
        std::cerr << "!!!No more space available!!!";
    }

    heap[heap_size] = value;
    heap_size++;

    heapify_up(heap_size - 1);
}

bool BinaryHeap::remove_top() {
    if (heap_size == 0) {
        std::cerr << "!!!Heap is already empty!!!";
        return false;
    }
    heap_size--;
    heap[0] = heap[heap_size];
    heapify_down(0);
    return true;
}

void BinaryHeap::print() {
    if (heap_size == 0) {
        std::cout << "Heap is empty!" << std::endl;
        return;
    }

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

int BinaryHeap::find(int value) {
    int i = 0;

    while (i < heap_size && i != -1) {
        if (heap[i] == value) {
            return i;
        }
        else if (heap[i] < value) {
            i = get_right_child(i);
        }
        else {
            i = get_left_child(i);
        }
    }

    return -1;
}

//
//int main() {
//    BinaryHeap binaryHeap = BinaryHeap(10);
//    binaryHeap.add(4);
//    binaryHeap.add(2);
//    binaryHeap.add(49);
//    binaryHeap.add(1);
//    binaryHeap.add(169);
//    binaryHeap.print();
//    binaryHeap.remove_top();
//    binaryHeap.print();
//    return 0;
//}



