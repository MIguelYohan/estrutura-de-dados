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
    printf("\nTOPO\n");

    for(int i = stack_size(s) - 1; i >= 0; i--){
        printf("%d\n", s->stack[i]);

        if(i != 0){
            printf("|\n");
        }
    }

    printf("BASE\n");
}


void solve(stack_t *s, int d){
    stack_t *aux;
    stack_initialize(&aux);
    int deletes = d;

    while(stack_size(s) > 0){
        while(deletes > 0 && !stack_empty(aux) && stack_top(aux) < stack_top(s)){
            stack_pop(aux);
            deletes--;
        }
        // Se estiver vazia, logicamente precisamos dar o push no top da aux
        stack_push(aux, stack_top(s));
        stack_pop(s);
    }

    // deletes restantes: remove do topo de aux
    while(deletes > 0){
        stack_pop(aux);
        deletes--;
    }

    for(int i = 0; i < stack_size(aux); i++){
        printf("%d", aux->stack[i]);
    }
    printf("\n");
}



int main(){
    stack_t *s;
    stack_initialize(&s);
    int n, d;
    while(true){
        scanf("%d %d", &n, &d);
        if(n == 0 && d == 0){
            break;
        }
        int *num_int = malloc(sizeof(int) * n);

        // Recebe o número e divide os algarismos em num_int
        char *num_char = malloc(sizeof(char) * n + 1);
        scanf("%s", num_char);
        for(int i = 0; i < n; i++){
            num_int[i] = num_char[i] - '0';
        }
        free(num_char);
        for(int j = n - 1; j >= 0; j--){
            stack_push(s, num_int[j]); // Temos a stack com os números na ordem correta
        }
        free(num_int);

        solve(s, d);
    }
}