#include <stdio.h>

void dfs_pos_node(tree_node_t *node){
    if(node != NULL){
        dfs_pos_node(node->left);
        dfs_pos_node(node->right);
        printf("%d\n", node->data);
    }
}

void dfs_pos(tree_t *t){
    if(t->root != NULL){
        dfs_pos_node(t->root);
    }
}