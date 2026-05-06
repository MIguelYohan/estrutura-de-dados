#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct stack_t{
    int *stack;
    int size;
    int capacity;
} stack_t;


void stack_initialize(stack_t **s){
    (*s) = malloc(sizeof(stack_t));
    (*s)->capacity = 4;
    (*s)->size = 0;
    (*s)->stack = malloc(sizeof(int) * (*s)->capacity);
}


int stack_size(stack_t *s){
    return s->size;
}


bool stack_empty(stack_t *s){
    return s->size == 0;
}


void stack_expand(stack_t *s){
    s->capacity *= 2;
    s->stack = realloc(s->stack, sizeof(int) * s->capacity);
}


void stack_push(stack_t *s, int data){
    if(s->capacity == stack_size(s)){
        stack_expand(s);
    }
    s->stack[s->size++] = data;
}


void stack_shrink(stack_t *s){
    s->capacity /= 2;
    s->stack = realloc(s->stack, sizeof(int) * s->capacity);
}


void stack_pop(stack_t *s){
    if(stack_size(s) == s->capacity / 4 && s->capacity > 4){
        stack_shrink(s);
    }
    s->size--;
}


int stack_top(stack_t *s){
    assert(!stack_empty(s));
    return s->stack[s->size - 1];
}


void stack_delete(stack_t **s){
    free((*s)->stack);
    free(*s);
    *s = NULL;
}


int main(){
    stack_t *s;
    stack_initialize(&s);
    int n, v, i;
    scanf("%d", &n);
    for(i = 0; i < n; i++){
        scanf("%d", &v);
        stack_push(s, v);
    }
    printf("\n");
    for(i = 0; i < stack_size(s); i++){
        printf("%d\n", s->stack[i]);
        printf("-\n");
    }
    printf("FIM DA PILHA");
    stack_delete(&s);
}