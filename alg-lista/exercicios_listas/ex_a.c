#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct Person{
    char name[30];
} Person;


typedef struct list_node_t{
    Person data;
    struct list_node_t *next;
} list_node_t;


typedef struct list_t{
    list_node_t *head;
    list_node_t *tail;
    size_t size;
} list_t;


void list_initialize(list_t **l){
    (*l) = malloc(sizeof(list_t));
    (*l)->head = NULL;
    (*l)->tail = NULL;
    (*l)->size = 0;
}


int list_size(list_t *l){
    return l->size;
}


bool list_empty(list_t *l){
    return list_size(l) == 0 ? true : false;
}


static list_node_t *list_new_node(Person data){
    list_node_t *new_node = malloc(sizeof(list_node_t));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}


// Deleta um nó de uma lista
static void list_delete_node(list_node_t *n){
    free(n);
}


// Inserção na cabeça
void list_prepend(list_t *l, Person data){
    list_node_t *new_node = list_new_node(data);
    new_node->next = l->head;
    l->head = new_node;

    if(list_empty(l)){
        l->tail = new_node;
    }

    l->size++;
}


// Inserção na cauda
void list_append(list_t *l, Person data){
    list_node_t *new_node = list_new_node(data);
    
    if(list_empty(l)){
        l->head = new_node;
    }
    else{
        l->tail->next = new_node;
    }

    l->tail = new_node;
    l->size++;
}


void list_insert(list_t *l, Person data, size_t i){
    assert(i <= list_size(l));

    if (list_empty(l) || i == 0){
        list_prepend(l, data);
    }

    else if(i == list_size(l)){
        list_append(l, data);
    }

    else {
        list_node_t *new_node = list_new_node(data);

        list_node_t *aux = l->head;
        size_t k;
        for(k = 0; k < i - 1; k++){
            aux = aux->next;
        }

        new_node->next = aux->next;
        aux->next = new_node;

        l->size++;
    }
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


void list_remove_tail(list_t *l){
    assert(list_size(l) > 0);

    list_node_t *to_be_removed = l->tail;

    if(list_size(l) == 1){
        l->head = NULL;
        l->tail = NULL;
    }

    else{
        list_node_t *aux = l->head;
        while(aux->next != l->tail){
            aux = aux->next;
        }
        aux->next = NULL;
        l->tail = aux;
    }
    list_delete_node(to_be_removed);
    l->size--;
}


void list_remove(list_t *l, size_t i){
    assert(!list_empty(l));

    if(list_size(l) == 1 || i == 0){
        list_remove_head(l);
    }

    else if(i == list_size(l) - 1){
        list_remove_tail(l);
    }

    else{
        list_node_t *node;

        list_node_t *aux = l->head;
        size_t k;

        for(k = 0; k < i - 1; k++){
            aux = aux->next;
        }
        node = aux->next;
        aux->next = node->next;
        list_delete_node(node);
        l->size--;
    }
}


Person list_acess_head(list_t *l){
    assert(!(list_empty(l)));
    return l->head->data;
}


Person list_acess_tail(list_t *l){
    assert(!(list_empty(l)));
    return l->tail->data;
}


Person list_acess(list_t *l, size_t i){
    assert(!list_empty(l));

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


void list_delete(list_t **l){
    while(!list_empty(*l)){
        list_remove_head(*l);
    }

    free(*l);
    *l = NULL;
}


void link_list(list_t *l){
    l->tail->next = l->head;
}


void deslink_list(list_t *l){
    l->tail->next = NULL;
}


Person solve(list_t *l, int x){
    x--;
    int i = 0;
    while(list_size(l) > 1){
        i  = (i + x) % list_size(l); // O módulo permite que i volte pro inicio quando passar o fim
        list_remove(l, i);
    }
    return l->head->data;
}


int main(){
    int n, x;
    list_t *l;
    list_initialize(&l);

    scanf("%d %d", &n, &x);
    int i;
    for(i = 0; i < n; i++){
        Person data;
        scanf("%s", data.name);
        list_append(l, data);
    }
    link_list(l);
    Person result = solve(l, x);
    printf("%s", result.name);

    deslink_list(l); // Precisamos deslinkar a lista para que o list_delete funcione
    list_delete(&l);
}