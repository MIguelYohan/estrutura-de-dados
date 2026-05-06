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


void list_remove_tail(list_t *l){
    if(list_size(l) == 1){
        l->head = NULL;
        l->tail = NULL;
    }
    else{
        list_node_t *aux = l->head;
        int k;
        for(k = 0; k < list_size(l) - 2; k++){
            aux = aux->next;
        }
        free(l->tail);
        l->tail = aux;
        aux->next = NULL;
    }
    l->size--;
}


void list_remove(list_t *l, size_t i){ //[1][2][3]
    if(list_size(l) == 1 || i == 0){
        list_remove_head(l);
    }
    else if(i == list_size(l) - 1){
        list_remove_tail(l);
    }
    else{
        list_node_t *aux = l->head;
        int k;
        for(k = 0; k < i - 1; k++){
            aux = aux->next;
        }
        list_node_t *to_remove = aux->next;
        aux->next = to_remove->next;
        free(to_remove);
        l->size--;
    }
}