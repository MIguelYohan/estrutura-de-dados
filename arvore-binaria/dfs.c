#include <stdio.h>

typedef struct tree_node{
    void *data;
    struct tree_node *left;
    struct tree_node *right;
}tree_node;

typedef struct tree{
    tree_node *root;
}tree;

// Podemos implementar a busca em profundidade utilizando uma pilha
// porem é mais facil e eficiente utilizar recursão (pilha implícita)

// Pré-ordem
// Processa o nó antes de ir para os vizinhos/filhos
// -> processa o NÓ primeiro, depois esquerda, depois direita
void dfs_pre_ordem(tree_node *root){
    if(root != NULL){
        process(root);
        dfs(root->left);
        dfs(root->right);
    }
}

// Em-ordem
// procedemos recursivamente à esquerda, visitamos o nó, e procedemos recursivamente à direita.
// -> processa esquerda primeiro, depois o NÓ, depois direita
void dfs_em_ordem(tree_node *root){
    if(root != NULL){
        dfs(root->left);
        process(root);
        dfs(root->right);
    }
}

// Pós-ordem
// procedemos recursivamente à esquerda, procedemos recursivamente à direita, visitamos o nó
// -> processa esquerda, depois direita, depois o NÓ por último
void dfs_pos_ordem(tree_node *root){
    if(root != NULL){
        dfs(root->left);
        dfs(root->right);
        process(root);
    }
}