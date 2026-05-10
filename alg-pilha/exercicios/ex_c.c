#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct index_data_t{
    int data;
    int index;
} index_data_t;


typedef struct stack_t{
    index_data_t *stack;
    int size;
    int capacity;
} stack_t;


void stack_initialize(stack_t **s){
    (*s) = malloc(sizeof(stack_t));
    (*s)->capacity = 4;
    (*s)->size = 0;
    (*s)->stack = malloc(sizeof(index_data_t) * (*s)->capacity);
}


int stack_size(stack_t *s){
    return s->size;
}


bool stack_empty(stack_t *s){
    return s->size == 0;
}


void stack_expand(stack_t *s){
    s->capacity *= 2;
    s->stack = realloc(s->stack, sizeof(index_data_t) * s->capacity);
}


void stack_push(stack_t *s, index_data_t data){
    if(s->capacity == stack_size(s)){
        stack_expand(s);
    }
    s->stack[s->size++] = data;
}


void stack_shrink(stack_t *s){
    s->capacity /= 2;
    s->stack = realloc(s->stack, sizeof(index_data_t) * s->capacity);
}


void stack_pop(stack_t *s){
    if(stack_size(s) == s->capacity / 4 && s->capacity > 4){
        stack_shrink(s);
    }
    s->size--;
}


index_data_t stack_top(stack_t *s){
    assert(!stack_empty(s));
    return s->stack[s->size - 1];
}


void stack_delete(stack_t **s){
    free((*s)->stack);
    free(*s);
    *s = NULL;
}

// Empilha cada valor do array na pilha, se o novo valor for menor que o ultimo da pilha, o mesmo já não será o menor mais próximo, se a pilha tiver um único valor após o empilhamento, não há valores menores que ele.
void solve(index_data_t *array, size_t n){ 
    stack_t *s;
    stack_initialize(&s);

    int i;
    for(i = 0; i < n; i++){
        // Enquanto existirem valores maiores que o atual, excluimos eles da pilha
        while(!stack_empty(s) && stack_top(s).data >= array[i].data){
            stack_pop(s);
        }
        // Após a exclusão, se sobrar algum valor, ele será o menor mais próximo do valor atual
        if(!stack_empty(s)){
            printf("%d", stack_top(s).index);
        }
        // Se não sobrar ninguem após a exclusão ou a pilha estiver vazia, printa 0
        else{
            printf("0");
        }
        // Adiciona o valor
        stack_push(s, array[i]);
        printf(" ");
    }

    stack_delete(&s);
}


int main(){
    size_t n;
    scanf("%d", &n);
    index_data_t *array = malloc(sizeof(index_data_t) * n);
    int i;
    for(i = 0; i < n; i++){
        scanf("%d", &array[i].data);
        array[i].index = i+1;
    }
    solve(array, n);
}