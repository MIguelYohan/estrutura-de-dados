#include <stdio.h>

typedef struct tree_node_t{
    int data;
    struct tree_node_t *left;
    struct tree_node_t *right;
}tree_node_t;

typedef struct tree_t{
    tree_node_t *root;
}tree_t;

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