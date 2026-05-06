#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct stack_t{
    int *stack;
    int capacity;
    int size;
} stack_t;


void stack_initialize(stack_t **s){
    *s = malloc(sizeof(stack_t));
    (*s)->capacity = 4; // Capacidade inicial é 4
    (*s)->stack = malloc(sizeof(int) * (*s)->capacity);
    (*s)->size = 0;
}


int stack_size(stack_t *s){
    return s->size;
}


bool stack_empty(stack_t *s){
    return stack_size(s) == 0;
}


// Empilhar
void stack_push(stack_t *s, int data){
    if(stack_size(s) == s->capacity){
        stack_expand(s);
    }
    s->stack[s->size++] = data;
}


void stack_expand(stack_t *s){
    s->capacity *= 2;
    s->stack = realloc(s->stack, sizeof(int) * s->capacity);
}


// Desempilhar
void stack_pop(stack_t *s){
    // A segunda condição garante que a capacidade não seja menor que 4
    if(stack_size(s) == s->capacity / 4 && s->capacity > 4){
        stack_shrink(s);
    }
    s->size--; // Redimensionar o vetor para menor é como retirar o ultimo elemento
}


void stack_shrink(stack_t *s){
    s->capacity /= 2;
    s->stack = realloc(s->stack, sizeof(int) * s->capacity);
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