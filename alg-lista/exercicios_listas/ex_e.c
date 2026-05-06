#include "grader.h"

void list_insert(list_t *l, int data, size_t i){
    list_node_t *new_node = malloc(sizeof(list_node_t));
    new_node->data = data;
    if(list_empty(l)){
        l->head = new_node;
        l->tail = new_node;
        new_node->next = NULL;
    }
    else if(i == 0){ // Prepend
        new_node->next = l->head;
        l->head = new_node;
    }
    else if(i == list_size(l)){ // Append
        l->tail->next = new_node;
        l->tail = new_node;
        new_node->next = NULL;
    }
    else{
        list_node_t *aux = l->head;
        for(int k = 0; k < i - 1; k++){
            aux = aux->next;
        }
        new_node->next = aux->next;
        aux->next = new_node;
    }
    l->size++;
}