#include <stdio.h>

void dfs_in_node(tree_node_t *n){
    if(n != NULL){
        dfs_in_node(n->left);
        printf("%d\n", n->data);
        dfs_in_node(n->right);
    }
}

void dfs_in(tree_t *t){
    if(t != NULL){
        dfs_in_node(t->root);
    }
}