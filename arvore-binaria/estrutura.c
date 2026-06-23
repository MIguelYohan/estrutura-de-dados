#include <stdio.h>

// Nó da arvore 
typedef struct tree_node{
    void *data; // Tipo genérico
    struct tree_node *left; // Se não tiver filhos aponta para NULL
    struct tree_node *right;
}tree_node;

// Nó raiz da arvore - Se comporta recursivamente
typedef struct tree{
    tree_node *root; // Se a arvore for vazia basta que root aponte para NULL
}tree;
