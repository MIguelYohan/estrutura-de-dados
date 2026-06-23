#include "grader.h"

void stack_expand(stack_t *s){
    s->capacity *= 2;
    s->stack = realloc(s->stack, sizeof(int) * s->capacity);
}


void stack_push(stack_t *s, int data){
    if(stack_size(s) == s->capacity){
        stack_expand(s);
    }
    s->stack[s->size++] = data;
}