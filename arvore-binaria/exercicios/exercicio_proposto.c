#include <stdio.h>
#include <stdlib.h>

typedef struct tree_node{
    void *data;
    struct tree_node *left;
    struct tree_node *right;
}tree_node;

typedef struct tree{
    tree_node *root;
}tree;

// Busca em profundidade
void dfs(tree_node *root){
    if(root != NULL){
        printf("%d -> ", *(int*) root->data);
        dfs(root->left);
        dfs(root->right);
    }
}

tree_node* new_node(int value){
    tree_node *n = malloc(sizeof(tree_node)); // Aloca memoria para um node
    int *data = malloc(sizeof(int)); // Aloca memoria de tamanho int para um dado
    *data = value; // data aponta para o int value
    n->data = data; // data aponta para o novo valor
    n->left = NULL;
    n->right = NULL;
    return n;
}

tree* create_example_tree(){
    tree *t = malloc(sizeof(tree));
    // Nó raiz
    tree_node *r = new_node(2);
    t->root = r;

    // Variaveis de cada nó
    tree_node *n7_1 = new_node(7);
    tree_node *n5_1 = new_node(5);
    tree_node *n2_2 = new_node(2);
    tree_node *n6_2 = new_node(6);
    tree_node *n9_2 = new_node(9);
    tree_node *n5_3 = new_node(5);
    tree_node *n11_3 = new_node(11);
    tree_node *n4_3 = new_node(4);

    // Conexão
    r->left = n7_1;
    r->right = n5_1;
    
    n7_1->left = n2_2;
    n7_1->right = n6_2;
    n5_1->right = n9_2;

    n6_2->left = n5_3;
    n6_2->right = n11_3;

    n9_2->left = n4_3;

    return t;
}

int main(){
    tree *t = create_example_tree();
    dfs(t->root);
    printf("END");
}