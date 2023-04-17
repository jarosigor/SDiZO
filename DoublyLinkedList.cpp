#include <iostream>
#include "DoublyLinkedList.h"

DoublyLinkedList::DoublyLinkedList() {
    size = 0;
    head = nullptr;
    tail = nullptr;
}

int DoublyLinkedList::add_front(int value) {
    Node* new_node = new Node(value, nullptr, head);
    if (size == 0) {
        head = new_node;
        tail = new_node;
    }
    else {
        head->prev = new_node;
        head = new_node;
    }
    size++;
    return 0;
}

int DoublyLinkedList::add_back(int value) {
    Node* new_node = new Node(value, tail, nullptr);
    if (size == 0) {
        tail = new_node;
        head = new_node;
    } else {
        tail->next = new_node;
        tail = new_node;
    }
    size++;
    return 0;
}

int DoublyLinkedList::add_at(int value, int position) {
    if (position  < 0 || position > size) {
        std::cerr << "Position is not valid!";
        return -1;
    }
    if (position == 0) return add_front(value);
    if (position == size) return add_back(value);

    Node* curr_node = head;
    int it = 0;
    while (it != position && curr_node->next != nullptr) {
        it++;
        curr_node = curr_node->next;
    }

    Node* new_node = new Node(value, curr_node->prev, curr_node);
    (curr_node->prev)->next = new_node;
    curr_node->prev = new_node;
    return 0;
}

int DoublyLinkedList::remove_front() {
    if (size != 0) {
        Node* new_head = head->next;
        new_head->prev = nullptr;
        head = new_head;
        size--;
        return 0;
    }
    else {
        std::cout << "List is empty!" << std::endl;
        return -1;
    }
}

int DoublyLinkedList::remove_back() {
    if (size != 0) {
        Node* new_tail = tail->prev;
        new_tail->next = nullptr;
        tail = new_tail;
        size--;
        return 0;
    }
    else {
        std::cout << "List is empty!" << std::endl;
        return -1;
    }
}

int DoublyLinkedList::remove_at(int position) {
    if (position  < 0 || position >= size) {
        std::cerr << "Position is not valid!";
        return -1;
    }

    Node* curr_node = head;
    int it = 0;
    while (it != position) {
        it++;
        curr_node = curr_node->next;
    }
    curr_node->next->prev = curr_node->prev;
    curr_node->prev->next = curr_node->next;
    size--;

    return 0;
}

Node* DoublyLinkedList::find(int position) {
    Node* curr_node = nullptr;
    if (position  < 0 || position >= size) {
        std::cerr << "Position is not valid!";
        return curr_node;
    }

    curr_node = head;
    int it = 0;
    while (it != position && curr_node->next != nullptr) {
        it++;
        curr_node = curr_node->next;
    }

    return curr_node;
}

void DoublyLinkedList::print() {
    if (size == 0) {
        std::cout << "List is empty!" << std::endl;
        return;
    }
    //std::cout << "head " << this->head->value << " tail " << this->tail->value << std::endl;
    Node* curr_node = head;
    while (curr_node != nullptr) {
        std::cout << curr_node->value << " ";
        curr_node = curr_node->next;
    }
    std::cout << std::endl;
}

int DoublyLinkedList::get_size() {
    return size;
}

//using namespace std;
//int main() {
//    int check_success = 0;
//    DoublyLinkedList list;
//
//    cout << "Added elem to front" << endl;
//    check_success = list.add_front(12);
//    list.print();
//
//    cout << "Added elem to back" << endl;
//    check_success = list.add_back(69);
//    list.print();
//
//    cout << "Added elem to front" << endl;
//    check_success = list.add_front(9);
//    list.print();
//
//    cout << "Added elem to front" << endl;
//    check_success = list.add_front(321);
//    list.print();
//
//    cout << "Removed elem at 2 position" << endl;
//    check_success = list.remove_at(2);
//    list.print();
//
//    cout << "Added elem at 1 position" << endl;
//    check_success = list.add_at(83, 1);
//    list.print();
//
//    cout << "Removed back elem" << endl;
//    check_success = list.remove_back();
//    list.print();
//
//    cout << "Removed front elem" << endl;
//    check_success = list.remove_front();
//    list.print();
//
//    return 0;
//}

