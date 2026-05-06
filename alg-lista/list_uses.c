#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct list_node_t{
    int data;
    struct list_node_t *next;
} list_node_t;


typedef struct list_t{
    list_node_t *head;
    list_node_t *tail;
    size_t size;
}list_t;


void list_initialize(list_t **l){
    (*l) = malloc(sizeof(list_t));
    (*l)->head = NULL;
    (*l)->tail = NULL;
    (*l)->size = 0;
}


size_t list_size(list_t *l){
    return l->size;
}


bool list_empty(list_t *l){
    return list_size(l) == 0 ? true : false;
}


static list_node_t *list_new_node(int data){
    list_node_t *new_node = malloc(sizeof(list_node_t));
    new_node->data = data;
    new_node->next = NULL;

    return new_node;
}


static void list_delete_node(list_node_t *n){
    free(n);
}


void list_append(list_t *l, int data){
    list_node_t *new_node = list_new_node(data);

    if(list_empty(l)){
        l->head = new_node;
    }
    else{
        l->tail->next = new_node;
    }

    l->tail = new_node;
    l->size ++;
}


// Acesso a cabeça
int list_acess_head(list_t *l){
    assert(!(list_empty(l)));
    return l->head->data;
}


int list_acess_tail(list_t *l){
    assert(!(list_empty(l)));
    return l->tail->data;
}


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


void list_remove_head(list_t *l){
    assert(!list_empty(l));

    list_node_t *aux = l->head;

    if(list_size(l) == 1){
        l->tail = NULL;
    }

    l->head = l->head->next;
    list_delete_node(aux);
    l->size--;
}


void list_delete(list_t **l){
    while(!list_empty(*l)){
        list_remove_head(*l);
    }
    free(*l);
    *l = NULL;
}


int main(){
    list_t *l;
    list_initialize(&l);

    int n, i;
    scanf("%d", &n); // Quantidade de valores
    int data;
    for(i = 0; i < n; i++){
        scanf("%d", &data);
        list_append(l, data);
    }

    list_node_t *aux = l->head;
    for(size_t j = 0; j < l->size; j++){
        printf("[%d] ", aux->data);
        aux = aux->next;
    }

    list_delete(&l);
}