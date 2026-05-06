#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

// Nó base da lista encadeada
typedef struct list_node_t{
    int data;                   // Dado
    struct list_node_t *next;   // Ponteiro para o próximo elemento
} list_node_t;


// Definição do tipo lista
typedef struct list_t{
    list_node_t *head; // Cabeça da lista
    list_node_t *tail; // Cauda da lista
    size_t size;
} list_t;


// Inicialização da lista
// "l" é um ponteiro duplo pois queremos alterar o funcionamento de l fora da função
void list_initialize(list_t **l) {
    (*l) = malloc(sizeof(list_t)); // Aloca espaço para a estrutura
    (*l)->head = NULL;
    (*l)->tail = NULL;
    (*l)->size = 0;
}


// Tamanho da lista
int list_size(list_t *l){
    return l->size;
}


// Retorna verdadeiro se e somente se a lista está vázia
bool list_empty(list_t *l){
    return list_size(l) == 0 ? true : false; // Operador ternário
}


// Cria um novo nó
static list_node_t *list_new_node(int data){ // static pois é uma função complementar
    list_node_t *new_node = malloc(sizeof(list_node_t));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}


// Deleta um nó de uma lista
static void list_delete_node(list_node_t *n){
    free(n);
}


// Inserção na cabeça
void list_prepend(list_t *l, int data){
    list_node_t *new_node = list_new_node(data);
    new_node->next = l->head;
    l->head = new_node;

    // Se a lista está vázia o nosso novo node é a cabeça e a cauda
    if(list_empty(l)){
        l->tail = new_node;
    }

    l->size++;
}


// Inserção na cauda
void list_append(list_t *l, int data){
    list_node_t *new_node = list_new_node(data);
    
    if(list_empty(l)){
        l->head = new_node;
    }
    else{
        l->tail->next = new_node;
    }

    l->tail = new_node;
    l->size++;
}


// Inserção em posição arbitrária
void list_insert(list_t *l, int data, size_t i){
    assert(i <= list_size(l));

    if (list_empty(l) || i == 0){
        list_prepend(l, data);
    }

    else if(i == list_size(l)){
        list_append(l, data);
    }

    else {
        list_node_t *new_node = list_new_node(data);

        list_node_t *aux = l->head;
        size_t k;
        for(k = 0; k < i - 1; k++){
            aux = aux->next;
        }

        new_node->next = aux->next;
        aux->next = new_node;

        l->size++;
    }
}


// Remoção da cabeça
void list_remove_head(list_t *l){
    assert(!list_empty(l));

    // Usamos um auxiliar para apontar para o valor da cabeça
    list_node_t *aux = l->head;

    // Se estamos deixando a lista vázia, logo ela não possui calda(tail = NULL), não fazemos o mesmo com a cabeça pois ainda podemos reutilizar a lista vázia.
    if(list_size(l) == 1){
        l->tail = NULL;
    }

    l->head = l->head->next;
    list_delete_node(aux);
    l->size--;
}


// Remoção na cauda
void list_remove_tail(list_t *l){
    assert(list_size(l) > 0);

    list_node_t *to_be_removed = l->tail;

    // Se a lista tem apenas um elemento a cauda e a cabeça apontam para NULL
    if(list_size(l) == 1){
        l->head = NULL;
        l->tail = NULL;
    }

    else{
        list_node_t *aux = l->head;
        while(aux->next != l->tail){
            aux = aux->next; // Auxiliar percorre a lista até chegar no penultimo node
        }

        aux->next = NULL;
        l->tail = aux;
    }

    list_delete_node(to_be_removed);

    l->size--;
}


// Remoção arbitrária
void list_remove(list_t *l, size_t i){
    assert(!list_empty(l) && i < list_size(l));

    if(list_size(l) == 1 || i == 0){
        list_remove_head(l);
    }

    else if(i == list_size(l) - 1){
        list_remove_tail(l);
    }

    else{
        list_node_t *node; // Node a ser removido

        list_node_t *aux = l->head;
        size_t k;

        for(k = 0; k < i - 1; k++){
            aux = aux->next; // Percorre a lista até chegar no valor anterior ao que será removido
        }
        node = aux->next; // Node a ser removido
        aux->next = node->next;
        list_delete_node(node);
        l->size--;
    }
}


// Acesso a cabeça
int list_acess_head(list_t *l){
    assert(!(list_empty(l)));
    return l->head->data;
}


// Acesso a cauda
int list_acess_tail(list_t *l){
    assert(!(list_empty(l)));
    return l->tail->data;
}


// Acesso arbitrário
int list_acess(list_t *l, size_t i){
    assert(!list_empty(l) && i < list_size(l));

    if(i == 0){
        return list_acess_head(l);
    }

    else if(i == l->size - 1){
        return list_acess_tail(l);
    }

    list_node_t *it = l->head;
    size_t k;
    for(k = 0; k < i; k++){
        it = it->next;
    }

    return it->data;
}


// Limpeza lista
void list_delete(list_t **l){
    while(!list_empty(*l)){ // Remove enquanto a lista não estiver vazia
        list_remove_head(*l);
    }

    free(*l);
    *l = NULL;
}


void print_list(list_t *l){
    list_node_t *n = l->head;
    for(int i = 0; i < l->size; i++){
        printf("[%d]", n->data);
        if(i < l->size - 1) printf(" -> ");
        n = n->next;
    }
    printf("\n");
}

// l1 e l2 devem estar ordenadas
void list_merge(list_t *l1, list_t *l2){
    int j = 0;

    while(list_size(l2) > 0){
        if(j >= list_size(l1)){
            list_append(l1, list_acess(l2, 0));
            list_remove(l2, 0);
        }
        else if(list_acess(l1, j) >= list_acess(l2, 0)){
            list_insert(l1, list_acess(l2, 0), j);
            list_remove(l2, 0);
        }
        else{
            j++;
        }
    }
}


int main(){
    list_t *l1, *l2;
    list_initialize(&l1);
    list_initialize(&l2);

    // Lista 1: [1][2][4]
    list_append(l1, 6);
    list_append(l1, 10);
    list_append(l1, 33);

    // Lista 2: [3][5][6]
    list_append(l2, 5);
    list_append(l2, 12);
    list_append(l2, 89);


    list_merge(l1, l2);
    print_list(l1);


    list_delete(&l1);
    list_delete(&l2);
}