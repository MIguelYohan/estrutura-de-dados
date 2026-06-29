#include <stdio.h>
#include <stdbool.h>

typedef struct tree_node_t{
    int data;
    struct tree_node_t *left; 
    struct tree_node_t *right;
}tree_node_t;

typedef struct tree_t{
    tree_node_t *root;
}tree_t;

bool is_bst_helper(tree_node_t *n){
    if(n == NULL){
        return true;
    }
    if(n->left == NULL && n->right == NULL){
        return true;
    }
    if(n->left != NULL && n->left->data < n->data){
        return is_bst_helper(n->left);
    }
    if(n->right != NULL && n->right->data > n->data){
        return is_bst_helper(n->right);
    }
    return false;
}

bool is_bst(tree_t *t){
    return is_bst_helper(t->root);
}