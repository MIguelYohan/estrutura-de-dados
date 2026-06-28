#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void delete_node(bst_node_t *n){
    free(n);
}

bst_node_t *bst_find_rightmost(bst_node_t *n){
    if(n == NULL || n->right == NULL){
        return n;
    }
    else{
        return bst_find_rightmost(n->right);
    }
}

bst_node_t *bst_remove_helper(bst_node_t *x, int data){
    if(data < x->data){
        x->left = bst_remove_helper(x->left, data);
    }
    else if(data > x->data){
        x->right = bst_remove_helper(x->right, data);
    }
    else{ // Achou o dado ou seja, x->data = data
        if(x->left == NULL){ // Ele possui apenas filho para direita
            bst_node_t *y = x->right;
            delete_node(x);
            x = y;
        }
        else if(x->right == NULL){ // Ele possui apenas filho para esquerda
            bst_node_t *y = x->left;
            delete_node(x);
            x = y;
        }
        else{ // Ele possui os dois filhos -> Trocar de posição o atual com o seu antecessor
            bst_node_t *previous = bst_find_rightmost(x->left);
            int aux = x->data;
            x->data = previous->data;
            previous->data = aux;

            x->left = bst_remove_helper(x->left, data);
        }
    }
    return x;
}

void bst_remove(bst_t *t, int data){
    t->root = bst_remove_helper(t->root, data);
    t->size--;
}