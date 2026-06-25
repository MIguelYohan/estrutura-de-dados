#include <stdio.h>

// Nó da arvore 
typedef struct tree_node_t{
    void *data; // Tipo genérico
    struct tree_node_t *left; // Se não tiver filhos aponta para NULL
    struct tree_node_t *right;
}tree_node_t;

// Nó raiz da arvore - Se comporta recursivamente
typedef struct tree{
    tree_node_t *root; // Se a arvore for vazia basta que root aponte para NULL
}tree;
