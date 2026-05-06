#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

// Em listas duplamente encadeadas seus nós fazem referência ao próximo e ao anterior

typedef struct dlist_node_t{
    int data;
    struct dlist_node_t *next;
    struct dlist_node_t *prev;
} dlist_node_t;


typedef struct dlist_t{
    dlist_node_t *head;
    dlist_node_t *tail;
    size_t size;
} dlist_t;


void dlist_initialize(dlist_t **l){
    (*l) = mallocx(sizeof(dlist_t));
    (*l)->head = NULL;
    (*l)->tail = NULL;
    (*l)->size = 0;
}


size_t dlist_size(dlist_t *l){
    return l->size;
}


bool dlist_empty(dlist_t *l) {
    return dlist_size(l) == 0 ? true : false;
}


void dlist_delete(dlist_t **l) {
    while (!dlist_empty(*l)) {
        dlist_remove_head(*l);
    }
    free(*l);
    *l = NULL;
}


void dlist_prepend(dlist_t *l, int data) {
    dlist_node_t *new_node = dlist_new_node(data);
    if (dlist_empty(l)) {
        l->tail = new_node;
    } else {
        l->head->prev = new_node;
    }
    new_node->next = l->head;
    l->head = new_node;
    l->size++;
}


void dlist_append(dlist_t *l, int data) {
    dlist_node_t *new_node = dlist_new_node(data);
    if (dlist_empty(l)) {
        l->head = new_node;
    } else {
        l->tail->next = new_node;
    }
    new_node->prev = l->tail;
    l->tail = new_node;
    l->size++;
}


void dlist_insert(dlist_t *l, int data, size_t i) {
    assert(i <= dlist_size(l));
    if (dlist_empty(l) || i == 0) {
        dlist_prepend(l, data);
    } else if (i == dlist_size(l)) {
        dlist_append(l, data);
    } else {
        dlist_node_t *new_node = dlist_new_node(data);
        dlist_node_t *aux = l->head;
        size_t k;
        for (k = 0; k < i - 1; k++) {
            aux = aux->next;
        }
        new_node->next = aux->next;
        new_node->prev = aux;
        aux->next->prev = new_node;
        aux->next = new_node;
        l->size++;
    }
}


void dlist_remove_head(dlist_t *l) {
    assert(!dlist_empty(l));
    dlist_node_t *node = l->head;
    l->head = l->head->next;
    if (dlist_size(l) == 1) {
        l->tail = NULL;
    } else {
        l->head->prev = NULL;
    }
    dlist_delete_node(node);
    l->size--;
}


void dlist_remove_tail(dlist_t *l) {
    assert(!dlist_empty(l));
    dlist_node_t *node = l->tail;
    l->tail = l->tail->prev;
    if (dlist_size(l) == 1) {
        l->head = NULL;
    } else {
        l->tail->next = NULL;
    }
    dlist_delete_node(node);
    l->size--;
}


void dlist_remove(dlist_t *l, size_t i) {
    assert(!dlist_empty(l) && i < dlist_size(l));
    dlist_node_t *node;
    if (dlist_size(l) == 1 || i == 0) {
        dlist_remove_head(l);
    } else if (i == dlist_size(l) - 1) {
        dlist_remove_tail(l);
    } else {
        dlist_node_t *aux = l->head;
        size_t k;
        for (k = 0; k < i; k++) {
            aux = aux->next;
        }
        node = aux;
        node->prev->next = node->next;
        node->next->prev = node->prev;
        dlist_delete_node(node);
        l->size--;
    }
}


int dlist_access(dlist_t *l, size_t i) {
    assert(!dlist_empty(l) && i < dlist_size(l));
    dlist_node_t *aux = l->head;
    int j;
    for (j = 0; j < i; j++) {
        aux = aux->next;
    }
    return (aux->data);
}


int dlist_access_head(dlist_t *l) {
    assert(!(dlist_empty(l)));
    return (l->head->data);
}


int dlist_access_tail(dlist_t *l) {
    assert(!dlist_empty(l));
    return (l->tail->data);
}


size_t dlist_size(dlist_t *l) {
    return l->size;
}
