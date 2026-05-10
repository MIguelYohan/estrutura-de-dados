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


void print_stack(stack_t *s){
    int i;
    for(i = 0; i < stack_size(s); i++){
        printf("%c", s->stack[i]);
    }
    printf("\n");
}

// Manter sempre os maiores valores na pilha enquanto não aparecem valores maiores, até que acabem as deleções
void solve(char *num, int digits, int d){
    stack_t *s;
    stack_initialize(&s);
    stack_t *aux;
    stack_initialize(&aux);

    // Copiando a string para a pilha
    int i;
    for(i = digits - 1; i >= 0; i--){
        stack_push(s, num[i]);
    }

    int deletes = d;
    while(stack_size(s) > 0){
        while(!stack_empty(aux) && deletes > 0 && stack_top(aux) < stack_top(s)){
            stack_pop(aux);
            deletes --;
        }
        stack_push(aux, stack_top(s));
        stack_pop(s);
    }

    while(deletes > 0){
        stack_pop(aux);
        deletes --;
    }

    print_stack(aux);
    
    stack_delete(&s);
    stack_delete(&aux);
}


int main(){
    while(true){
        int n, d;
        scanf("%d %d", &n, &d);
        if(n == 0 && d == 0){
            return 0;
        }
        char *num = malloc(sizeof(char) * (n + 1));
        scanf("%s", num);
        solve(num, n, d);
        free(num);
    }
}