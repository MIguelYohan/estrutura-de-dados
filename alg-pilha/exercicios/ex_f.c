#include "grader.h"

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