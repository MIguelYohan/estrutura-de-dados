#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_mirrored_node(tree_node_t *a, tree_node_t *b){
    if(a == NULL && b == NULL){ // A e B são NULL ao mesmo tempo
        return true;
    }
    if(a == NULL || b == NULL){ // Se passou do primeiro if quer dizer que os dois não são ambos NULL, só resta que apenas um deles sejam NULL, oque é uma assimetria
        return false;
    }
    if(a->data != b->data){
        return false;
    }

    return is_mirrored_node(a->left, b->right) && is_mirrored_node(a->right, b->left);
}

bool is_mirrored(tree_t *t){
    if(t->root != NULL){
        return is_mirrored_node(t->root->left, t->root->right);
    }
    return true;
}