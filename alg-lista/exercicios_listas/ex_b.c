#include "grader.h"

void list_concat(list_t *l1, list_t *l2){
    if(list_empty(l2)){
        return;
    }
    else if(list_empty(l1)){
        l1->head = l2->head;
        l1->tail = l2->tail;
    }
    else{
        l1->tail->next = l2->head;
        l1->tail = l2->tail;
    }

    l1->size += l2->size;

    l2->head = NULL;
    l2->tail = NULL;
    l2->size = 0;
}