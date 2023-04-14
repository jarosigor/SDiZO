#ifndef STD_LIB
#define STD_LIB
#include <iostream>
#include <bits/stdc++.h>
#endif

#ifndef SDIZO_BST_H
#define SDIZO_BST_H


struct TreeNode {
    int value;
    TreeNode *left_child;
    TreeNode *right_child;
    TreeNode *parent;
    TreeNode();
    TreeNode(int value, TreeNode *parent, TreeNode *left_child, TreeNode *right_child);
    ~TreeNode();
    auto is_leaf();
    auto is_left_child();
    auto is_right_child();
    auto print();
};


class BST {
private:
    TreeNode* root;

public:
    BST();
    BST(TreeNode* root);
    auto transplant(TreeNode* u, TreeNode* v);
    auto balance_tree();
    auto find_BST(int key);
    auto is_empty();
    auto add(int value);
    auto remove(int value);
    auto dsw();
    auto rotate_right(TreeNode* node);
    auto rotate_left(TreeNode* node);
    auto succ_BST(TreeNode* node);
    auto balance_tree(TreeNode* node);
    void print(TreeNode* curr_node);
    auto get_root();
};

#endif //SDIZO_BST_H
