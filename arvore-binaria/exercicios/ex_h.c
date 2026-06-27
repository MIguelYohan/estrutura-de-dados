#include <stdio.h>
#include <stdbool.h>

bool is_equal_root(tree_node_t *a, tree_node_t *b){
    if(a == NULL && b == NULL){
        return true;
    }
    if((a == NULL) != (b == NULL)){
        return false;
    }
    if(a->data != b->data){
        return false;
    }

    return is_equal_root(a->left, b->left) && is_equal_root(a->right, b->right);
}

bool is_equal(tree_t *t1, tree_t *t2){
    return is_equal_root(t1->root, t2->root);
}