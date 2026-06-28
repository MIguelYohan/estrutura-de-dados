#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

bst_node_t *bst_create_node(int data){
    bst_node_t *n = malloc(sizeof(bst_node_t));
    n->data = data;
    n->left = NULL;
    n->right = NULL;

    return n;
}

bst_node_t *bst_insert_helper(bst_node_t *n, int data){
    if(n == NULL){
        return bst_create_node(data);
    }
    assert(n->data != data);
    if(data < n->data){
        n->left = bst_insert_helper(n->left, data);
    }
    else{
        n->right = bst_insert_helper(n->right, data);
    }
    return n;
}

void bst_insert(bst_t *t, int data){
    t->root = bst_insert_helper(t->root, data);
    t->size++;
}