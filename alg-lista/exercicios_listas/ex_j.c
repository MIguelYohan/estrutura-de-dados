#include "grader.h"

void list_reverse(list_t *l){
    if(list_size(l) == 1){
        return;
    }

    list_node_t *prev = NULL;
    list_node_t *curr = l->head;
    list_node_t *next = NULL;

    l->tail = l->head;

    while(curr != NULL){ // se curr == NULL é por que ele percorreu até o next do último node
        next = curr->next;
        curr->next = prev;
        // anda com os ponteiros frente
        prev = curr;
        curr = next;
    }

    l->head = prev; // prev termina como o ultimo valor da lista
}