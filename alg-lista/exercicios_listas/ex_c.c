#include "grader.h"

void list_prepend(list_t *l, int data){
    list_node_t *new_node = malloc(sizeof(list_node_t));
    new_node->data = data;
    new_node->next = l->head;
    l->head = new_node;

    if(list_empty(l)){
        l->tail = new_node;
    }

    l->size++;
}