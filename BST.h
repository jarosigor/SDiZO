#ifndef STD_LIB
#define STD_LIB
#include <iostream>
#include <cmath>
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
};


class BST {
private:
    TreeNode* root;

public:
    BST();
    BST(TreeNode* root);
    void transplant(TreeNode* u, TreeNode* v);
    TreeNode* find_BST(int key);
    int add(int value);
    int remove(int value);
    void rotate_right(TreeNode* node);
    void rotate_left(TreeNode* node);
    TreeNode* succ_BST(TreeNode* node);
    int make_bst_vine();
    void balance_tree_DSW();
    TreeNode* get_root();
    void print_BST(TreeNode *node, bool isLeft = false, const std::string &prefix = "");
};

#endif //SDIZO_BST_H
