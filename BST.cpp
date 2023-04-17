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

TreeNode &TreeNode::operator=(const TreeNode &other) {
    TreeNode temp(other);
    std::swap(*this, temp);
    return *this;
}

TreeNode::TreeNode(const TreeNode &other) {
    operator=(other);
}

BST::BST() {
    root = nullptr;
}

BST::BST(TreeNode *root) {
    this->root = root;
}

BST::BST(const BST &other) {
    operator=(other);
}

BST &BST::operator=(const BST &other) {
    BST tmp(other);
    std::swap(*this, tmp);
    return *this;
}

// wyszukiwanie nastepnika dla podanego wezla
TreeNode* BST::succ_BST(TreeNode *node) {
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

// wyszukiwanie wezla po kluczu
TreeNode* BST::find_BST(int key) {
    TreeNode* curr_node = root;
    while (curr_node->value != key && curr_node != nullptr) {
        if (curr_node->value == key) {
            return curr_node;
        } else if (curr_node->value < key) {
            curr_node = curr_node->right_child;
        } else {
            curr_node = curr_node->left_child;
        }
    }
    return curr_node;
}

int BST::add(int value) {
    if (value < 0) {
        return -1;
    }
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

    auto new_node = new TreeNode(value, parent, nullptr, nullptr);
    // puste drzewo
    if (parent == nullptr) {
        root = new_node;
    } else if (new_node->value < parent->value) {
        parent->left_child = new_node;
    } else {
        parent->right_child = new_node;
    }
    return 0;
}

// funkcja przeszczepia poddrzewo v w miejsce wezla u
void BST::transplant(TreeNode* u, TreeNode* v) {
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

int BST::remove(int value) {
    auto rem_node = find_BST(value);

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
    return 0;
}

void BST::rotate_left(TreeNode* node) {
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

void BST::rotate_right(TreeNode* node) {
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

// funkcja przeksztalcajaca niezbalansowane drzewo do postaci winoroslii
int BST::make_bst_vine() {
    int n = 0;
    auto curr_node = root;
    while (curr_node != nullptr) {
        if (curr_node->left_child == nullptr) {
            n++;
            curr_node = curr_node->right_child;
        } else {
            rotate_right(curr_node);
            curr_node = curr_node->parent;
        }
    }
    return n;
}

// balansowanie drzewa wykorzystujac algorytm DSW
void BST::balance_tree_DSW() {
    int n = make_bst_vine();
    int n_of_leafs = n + 1 - int(log2(n + 1));
    TreeNode* curr_node;
    bool first_part = true;

    // rotacje w zaleznosci od fazy 1 lub 2
    while (n > 1 || first_part) {
        curr_node = root;
        int cycles;
        if (first_part) {
            cycles = n_of_leafs;
            n -= n_of_leafs;
            first_part = false;
        } else {
            n /= 2;
            cycles = n;
        }
        for (int i = 0; i < cycles && curr_node != nullptr; i++) {
            if (curr_node->parent != nullptr) {
                rotate_left(curr_node);
                curr_node = curr_node->parent->right_child;
            }
        }
    }
}

// inspiracja z SO
void BST::print_BST(TreeNode* node, bool isLeft, const std::string& prefix) {
    if (node != nullptr) {
        std::cout << prefix;
        if (node != root) {
            std::cout << (isLeft && node->parent != nullptr ? "L" : "R");
        }
        std::cout << "|--";
        std::cout << node->value << std::endl;

        print_BST(node->left_child, true, prefix + (isLeft ? " :  " : "    "));
        print_BST(node->right_child, false,  prefix + (isLeft ? " :  " : "    "));
    }
}

TreeNode* BST::get_root() {
    return root;
}


//
//int main() {
//    auto root = new TreeNode(114, nullptr, nullptr, nullptr);
//    BST bst = BST(root);
//
//    bst.add(90);
//    bst.add(46);
//    bst.add(32);
//    bst.add(12);
//    bst.add(24);
//    bst.add(89);
//    bst.add(11);
//
//    std::cout << "Unbalanced" << std::endl;
//    print_BST(bst.get_root());
//    bst.balance_tree_DSW();
//    std::cout << "Balanced" << std::endl;
//    print_BST(bst.get_root());
//}

