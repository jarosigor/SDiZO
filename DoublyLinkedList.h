#ifndef STD_LIB
#define STD_LIB
#include <iostream>
#include <cmath>
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
    int add_front(int value);
    int add_back(int value);
    int add_at(int value, int position);
    int remove_front();
    int remove_back();
    int remove_at(int position);
    Node* find(int position);
    void print();
    int get_size();
};

#endif //SDIZO_DOUBLY_LINKED_LIST_H
