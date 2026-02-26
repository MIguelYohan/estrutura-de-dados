#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

void swap(int *v, int a, int b ){
    int temp;
    temp = v[a];
    v[a] = v[b];
    v[b] = temp;
}

// Lento O(n^2)
void bubble_sort(int *v, size_t size){
    int swapped = 1; // Swapped precisa começar de 1 para pelo menos acontecer uma varredura
    for(int i = 0; i < size - 1 && swapped; i++){ // O laço externo garante no máximo n - 1 passadas, que é o número máximo necessário para ordenar o vetor no pior caso
        swapped = 0;
        for(int j = 0; j < size - i - 1; j++){ // size - i - 1 garante que o for não passe na parte do vetor que já está ordenada
            if (v[j] > v[j+1]){
                swap(v, j, j+1);
                swapped = 1; // se entrou no if quer dizer que o swap aconteceu
            }
        }
    }
}


void gerar_vetor_aleatorio(int *v, size_t size){
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        v[i] = rand() % 1000;  // números entre 0 e 999
    }
}


int main(){
    int v[20];
    gerar_vetor_aleatorio(v, 20);

    size_t size_v = sizeof(v) / sizeof(v[0]);

    bubble_sort(v, size_v);

    for(int i = 0; i < size_v; i++){
        printf("[%d] ", v[i]);
    }

    return 0;
}