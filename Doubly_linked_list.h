#ifndef SDIZO_DOUBLY_LINKED_LIST_H
#define SDIZO_DOUBLY_LINKED_LIST_H

class Node {
    private:
        Node* next = nullptr;
        Node* previous = nullptr;
        int value = 0;
    public:
        Node();
        Node(int value, Node* prev, Node* next);
        ~Node();
        auto add_front(int value);
        auto add_back(int value);
        auto add_at(int value, int position, Node* head);
        auto remove_front();
        auto remove_back();
        auto remove_at(int position, Node* head);
        auto find(int position, Node* head);
        auto set_prev(Node* node);
        auto set_next(Node* node);
};

#endif //SDIZO_DOUBLY_LINKED_LIST_H
