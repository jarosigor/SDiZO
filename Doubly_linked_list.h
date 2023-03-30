#ifndef STD_LIB
#define STD_LIB
#include <iostream>
#endif

#ifndef SDIZO_DOUBLY_LINKED_LIST_H
#define SDIZO_DOUBLY_LINKED_LIST_H

struct Node {
    int value;
    Node* prev;
    Node* next;

    Node(int value, Node* prev, Node* next) {
        this->value = value;
        this->prev = prev;
        this->next = next;
    }

    ~Node(){
        delete prev;
        delete next;
    }
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;
    int size;
public:
    DoublyLinkedList();
    auto add_front(int value);
    auto add_back(int value);
    auto add_at(int value, int position);
    auto remove_front();
    auto remove_back();
    auto remove_at(int position);
    auto find(int position);
    auto print();
};

#endif //SDIZO_DOUBLY_LINKED_LIST_H
