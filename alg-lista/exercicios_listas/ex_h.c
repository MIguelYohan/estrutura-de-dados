#include "grader.h"

void list_remove_tail(list_t *l){ //[1][2][3][4]
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
        l->tail->next = NULL;
    }
    l->size--;
}