#include "grader.h"

void list_append(list_t *l, int data){
    list_node_t *new_node = malloc(sizeof(list_node_t));
    new_node->data = data;

    if(list_empty(l)){
        l->head = new_node;
    }
    else{
        l->tail->next = new_node;
    }
    l->tail = new_node;
    l->size++;
}