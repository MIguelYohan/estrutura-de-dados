#include <stdio.h>
#include <stdbool.h>

bool bst_find_helper(bst_node_t *n, int data){
    if(n == NULL){
        return false;
    }
    if(data < n->data){
        return bst_find_helper(n->left, data);
    }
    else if(data > n->data){
        return bst_find_helper(n->right, data);
    }
    return true;
}

bool bst_find(bst_t *t, int data){
    if(t->root == NULL) return false;
    return bst_find_helper(t->root, data);
}