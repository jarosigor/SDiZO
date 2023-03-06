#ifndef SDIZO_DOUBLY_LINKED_LIST_H
#define SDIZO_DOUBLY_LINKED_LIST_H

class Node {
    private:
        Node* next;
        Node* previous;
        int value;
    public:
        auto add_front(int value);
        auto add_back(int value);
        auto add_at(int value, int position);
        auto remove_front();
        auto remove_back();
        auto remove_at(int position);
        auto find(int position) -> int;
};

#endif //SDIZO_DOUBLY_LINKED_LIST_H
