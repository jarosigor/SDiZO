#include "BST.h"

TreeNode::TreeNode() {
    value = 0;
    parent = nullptr;
    left_child = nullptr;
    right_child = nullptr;
}

TreeNode::TreeNode(int value, TreeNode *parent, TreeNode *left_child, TreeNode *right_child) {
    this->value = value;
    this->parent = parent;
    this->left_child = left_child;
    this->right_child = right_child;
}

TreeNode::~TreeNode() {
    delete parent;
    delete left_child;
    delete right_child;
}

auto TreeNode::is_leaf() {
    return right_child == nullptr && left_child == nullptr;
}

auto TreeNode::is_left_child() {
    return parent->left_child == this;
}

auto TreeNode::is_right_child() {
    return parent->right_child == this;
}

auto TreeNode::print() {
    std::cout << value << " ";
    if (parent == nullptr)
        std::cout << " root ";
    else if (is_leaf()) {
        std::cout << " leaf ";
    }
    if (left_child != nullptr) {
        std::cout << " left child " << left_child->value;
    }
    if (right_child != nullptr) {
        std::cout << " right child " << right_child->value;
    }

    std::cout << std::endl;
}

BST::BST() {
    root = nullptr;
}

BST::BST(TreeNode *root) {
    this->root = root;
}

auto BST::is_empty() {
    return root == nullptr;
}

auto BST::succ_BST(TreeNode *node) {
    TreeNode* successor = node->right_child;
    if (successor != nullptr) {
        while (successor->left_child != nullptr) {
            successor = successor->left_child;
        }
    } else {
        successor = node->parent;
        while (successor != nullptr && successor->is_right_child()) {
            node = successor;
            successor = successor->parent;
        }
    }
    return successor;
}

auto BST::find_BST(int key) {
    TreeNode* curr_node = root;
    while (curr_node->value != key && curr_node != nullptr) {
        if (curr_node->value < key) {
            curr_node = curr_node->left_child;
        } else {
            curr_node = curr_node->right_child;
        }
    }
    return curr_node->value == key ? curr_node : nullptr;
}

auto BST::add(int value) {
    TreeNode* curr_node = root;
    TreeNode* parent = nullptr;
    // wyszukujemy liścia/parenta nowego noda
    while (curr_node != nullptr) {
        parent = curr_node;
        if (value < curr_node->value) {
            curr_node = curr_node->left_child;
        } else {
            curr_node = curr_node->right_child;
        }
    }

    TreeNode* new_node = new TreeNode(value, parent, nullptr, nullptr);
    // puste drzewo
    if (parent == nullptr) {
        root = new_node;
    } else if (new_node->value < parent->value) {
        parent->left_child = new_node;
    } else {
        parent->right_child = new_node;
    }

}

// funkcja przeszczepia poddrzewo v w miejsce wezla u
auto BST::transplant(TreeNode* u, TreeNode* v) {
    if (u->parent == nullptr) {
        root = v;
    } else if (u->is_left_child()) {
        u->parent->left_child = v;
    } else {
        u->parent->right_child = v;
    }
    if (v != nullptr) {
        v->parent = u->parent;
    }
}

auto BST::remove(int value) {
    TreeNode* rem_node = find_BST(value);

    if (rem_node == nullptr) {
        std::cerr << "!!!Given node value does not appear in BST!!!";
        return -1;
    }

    TreeNode* successor = succ_BST(rem_node);
    // przypadki gdy usuwany node ma jednego syna
    if (rem_node->left_child == nullptr) {
        transplant(rem_node, rem_node->right_child);
    } else if (rem_node->right_child == nullptr) {
        transplant(rem_node, rem_node->left_child);
    } else {
        if (successor != rem_node->right_child) {
            transplant(successor, successor->right_child);
            successor->right_child = rem_node->right_child;
            successor->right_child->parent = successor;
        }
        // wstawiamy nastepnik w miejsce usuwanego node a
        transplant(rem_node, successor);
        successor->left_child = rem_node->left_child;
        successor->left_child->parent = successor;
        delete rem_node;
    }
}

void BST::print(TreeNode* curr_node) {
    curr_node->print();
    if (curr_node->left_child != nullptr) {
        print(curr_node->left_child);
    }
    if (curr_node->right_child != nullptr) {
        print(curr_node->right_child);
    }
}

auto BST::balance_tree(TreeNode *node) {

}

auto BST::rotate_left(TreeNode* node) {
    TreeNode* node_r_kid = node->right_child;
    // lewe poddrzewo prawego dziecka zmieniamy w prawe
    node->right_child = node_r_kid->left_child;
    if (node_r_kid->left_child != nullptr) {
        node_r_kid->left_child->parent = node;
    }
    node_r_kid->parent = node->parent;
    if (node->parent == nullptr) {
        root = node_r_kid;
    } else if (node->is_left_child()) {
        node->parent->left_child = node_r_kid;
    } else {
        node->parent->right_child = node_r_kid;
    }
    node_r_kid->left_child = node;
    node->parent = node_r_kid;
}

auto BST::rotate_right(TreeNode* node) {
    TreeNode* node_l_kid = node->left_child;
    // lewe poddrzewo prawego dziecka zmieniamy w prawe
    node->left_child = node_l_kid->right_child;
    if (node_l_kid->right_child != nullptr) {
        node_l_kid->right_child->parent = node;
    }
    node_l_kid->parent = node->parent;
    if (node->parent == nullptr) {
        root = node_l_kid;
    } else if (node->is_left_child()) {
        node->parent->left_child = node_l_kid;
    } else {
        node->parent->right_child = node_l_kid;
    }
    node_l_kid->right_child = node;
    node->parent = node_l_kid;
}

auto BST::get_root() {
    return root;
}

int main() {

    TreeNode* root = new TreeNode(12, nullptr, nullptr, nullptr);
    BST bst = BST(root);

    bst.add(3);
    bst.add(51);
    bst.add(1);
    bst.print(root);
    std::cout << std::endl;
    bst.rotate_right(root);
    bst.print(bst.get_root());
}

