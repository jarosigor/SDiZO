#include <iostream>
#include "Doubly_linked_list.h"

auto Node::set_prev(Node* node) {
    previous = node;
}

auto Node::set_next(Node* node) {
    next = node;
}

Node::Node(int value, Node* prev, Node* next) {
    this->value = value;
    this->next = next;
    previous = prev;
}

Node::~Node() {
    delete previous;
    delete next;
}

auto Node::add_front(int value) {
    Node* curr_node = this;
    while (curr_node->previous != nullptr) {
        curr_node = curr_node->previous;
    }
    Node* new_node = new Node(value, nullptr, curr_node);
    curr_node->set_prev(new_node);
}

auto Node::add_back(int value) {
    Node* curr_node = this;
    while (curr_node->next != nullptr) {
        curr_node = curr_node->next;
    }
    Node* new_node = new Node(value, curr_node, nullptr);
    curr_node->set_next(new_node);
}

auto Node::add_at(int value, int position, Node* head) {
    Node* curr_node = head;
    int it = 0;
    while (it != position && curr_node != nullptr) {
        it++;
        curr_node = curr_node->next;
    }
    if (curr_node == nullptr) {
        std::cerr << "Position is not valid!";
        return -1;
    }
    Node* new_node = new Node(value, curr_node->previous, curr_node);
    (curr_node->previous)->set_next(new_node);
    curr_node->set_prev(new_node);
}

auto Node::remove_front() {
    Node* curr_node = this;
    while (curr_node->previous != nullptr) {
        curr_node = curr_node->previous;
    }
    (curr_node->next)->set_prev(nullptr);
    delete curr_node;
}

auto Node::remove_back() {
    Node* curr_node = this;
    while (curr_node->next != nullptr) {
        curr_node = curr_node->next;
    }
    (curr_node->previous)->set_next(nullptr);
    delete curr_node;
}

auto Node::remove_at(int position, Node* head) {
    Node* curr_node = head;
    int it = 0;
    while (it != position && curr_node != nullptr) {
        it++;
        curr_node = curr_node->next;
    }
    if (curr_node == nullptr) {
        std::cerr << "Position is not valid!";
        return -1;
    }
    Node* next_node = curr_node->next;
    Node* prev_node = curr_node->previous;
    next_node->set_prev(prev_node);
    prev_node->set_next(next_node);
}

auto Node::find(int position, Node* head) {
    Node* curr_node = head;
    int it = 0;
    while (it != position && curr_node != nullptr) {
        it++;
        curr_node = curr_node->next;
    }
    if (curr_node == nullptr) {
        std::cerr << "Position is not valid!";
    }
    return curr_node;
}

