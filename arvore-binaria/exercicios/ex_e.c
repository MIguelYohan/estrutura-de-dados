#include <stdio.h>

void dfs_pre_node(tree_node_t *n){
    if(n != NULL){
        printf("%d\n", n->data);
        dfs_pre_node(n->left);
        dfs_pre_node(n->right);
    }
}

void dfs_pre(tree_t *t){
    if(t->root != NULL){
        dfs_pre_node(t->root);
    }
}
