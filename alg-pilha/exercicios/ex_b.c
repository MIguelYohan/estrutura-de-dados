#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>

typedef struct stack_t{
    char *stack;
    int size;
    int capacity;
} stack_t;


void stack_initialize(stack_t **s){
    (*s) = malloc(sizeof(stack_t));
    (*s)->capacity = 4;
    (*s)->size = 0;
    (*s)->stack = malloc(sizeof(char) * (*s)->capacity);
}


int stack_size(stack_t *s){
    return s->size;
}


bool stack_empty(stack_t *s){
    return s->size == 0;
}


void stack_expand(stack_t *s){
    s->capacity *= 2;
    s->stack = realloc(s->stack, sizeof(char) * s->capacity);
}


void stack_push(stack_t *s, char data){
    if(s->capacity == stack_size(s)){
        stack_expand(s);
    }
    s->stack[s->size++] = data;
}


void stack_shrink(stack_t *s){
    s->capacity /= 2;
    s->stack = realloc(s->stack, sizeof(char) * s->capacity);
}


void stack_pop(stack_t *s){
    if(stack_size(s) == s->capacity / 4 && s->capacity > 4){
        stack_shrink(s);
    }
    s->size--;
}


char stack_top(stack_t *s){
    assert(!stack_empty(s));
    return s->stack[s->size - 1];
}


void stack_delete(stack_t **s){
    free((*s)->stack);
    free(*s);
    *s = NULL;
}


int precedence(int op){
    if(op == '+' || op == '-'){return 1;}
    else if(op == '*' || op == '/'){return 2;}
    return 0;
}


// Resumo da lógica: se aparecer um número, printar na hora
// Guardar os operadores na pilha em ordem de precedência e printar depois
// Quando aparecer um parenteses guardar os operadores junto dos parenteses dentro da pilha
void solve(char *expression){
    stack_t *s;
    stack_initialize(&s);

    int i = 0;
    while(expression[i] != '\0'){
        // Se for um digito, printa na hora
        if(isdigit(expression[i])){
            while(isdigit(expression[i])){
                printf("%c", expression[i]);
                i++;
            }
            printf(" ");
        }
        // Se for um espaço, apenas pula
        else if(expression[i] == ' '){
            i++;
        }
        // Coloca o parentese na pilha e pula ela
        else if(expression[i] == '('){
            stack_push(s, expression[i]);
            i++;
        }
        // Após terminar a expressão dos parenteses, printar os operadores da pilha
        else if(expression[i] == ')'){
            // Diferencia a precedência de operadores dentro do parenteses do contexto externo
            while(stack_top(s) != '('){
                printf("%c ", stack_top(s));
                stack_pop(s);
            }
            stack_pop(s); // Remove da pilha o '('
            i++;
        }
        // É um operador, precisamos adiciona-lo na pilha em ordem de precedência
        // !stack_empty(s) -> se acessarmos stack_top na pilha vazia o assert acionaria
        // stack_top(s) != '(' -> para que '(' não seja confundido com um operador
        // precedence(stack_top(s)) >= precedence(expression[i] -> empilha por precedência
        else{
            while(!stack_empty(s)
            && stack_top(s) != '('
            && precedence(stack_top(s)) >= precedence(expression[i])){
                printf("%c ", stack_top(s));
                stack_pop(s);
            }
            stack_push(s, expression[i]);
            i++;
        }
    }

    // Se sobrar operadores, imprime eles
    while(!stack_empty(s)){
        printf("%c ", stack_top(s));
        stack_pop(s);
    }

    stack_delete(&s);
}


int main(){
    char *expression = malloc(sizeof(char) * 1000000);
    fgets(expression, 1000000, stdin);
    solve(expression);
    free(expression);
}