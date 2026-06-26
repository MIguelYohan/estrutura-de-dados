#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct tree_node_t{
    int data;
    struct tree_node_t *left;
    struct tree_node_t *right;
}tree_node_t;

typedef struct tree_t{
    tree_node_t *root;
}tree_t;
