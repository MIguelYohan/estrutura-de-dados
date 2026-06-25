#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct tree_node_t{
    int data;
    struct tree_node_t *left;
    struct tree_node_t *right;
}tree_node_t;

typedef struct tree_t{
    tree_node_t *root;
}tree_t;

bool is_zigzag_node(tree_node_t *n){
    int last_mov = 0;

    tree_node_t *actual = n;
    while(true){
        if(actual->left == NULL && actual->right == NULL){
            return true;
        }
        if(actual->right != NULL && actual->left != NULL){
            return false;
        }
        if(actual->right != NULL){
            if(last_mov == 1){
                return false;
            }
            last_mov = 1;
            actual = actual->right;
        }
        else if(actual->left != NULL){
            if(last_mov == -1){
                return false;
            }
            last_mov = -1;
            actual = actual->left;
        }
    }
}

bool is_zigzag(tree_t *t){
    if(t->root != NULL){
        return is_zigzag_node(t->root);
    }
    else{
        return true;
    }
}

