#include "grader.h"

void list_remove_head(list_t *l){
    if(list_size(l) == 1){
        l->head = NULL;
        l->tail = NULL;
    }
    else{
        list_node_t *aux = l->head;
        l->head = l->head->next;
        free(aux);
    }
    l->size--;
}