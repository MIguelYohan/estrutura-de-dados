# include <stdio.h>
# include <stddef.h>
#include <stdlib.h>
#include <time.h>

// Depende muito de entender o estado do vetor em cada momento - muito condensado
// Ótimo para conjuntos pequenos de dados.
// O(n^2) comparavel ao bubble sort em conjuntos grandes de dados.
void insertion_sort(int *v, size_t size){
    int i, j, chosen;

    for(i = 1; i < size; i++){ // controla a parte não ordenada, começando do segundo valor (próximo a ordenadar)
        chosen = v[i]; // primeiro valor dos não ordenados
        for(j = i - 1; (j >= 0) && (chosen < v[j]); j--){ // controla a parte posta como já ordenada, j = i representa o proximo indice que o for exerterno iria examinar, -1 para pegar o ultimo ordenado.
            v[j+1] = v[j]; // abre espaço para incluir o valor chosen
        }
        v[j+1] = chosen; // ao final do for, ou seja, quando achou um valor menor ou o fim do vetor, adiciona o chosen neste local
    }
}


void gerar_vetor_aleatorio(int *v, size_t size){
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        v[i] = rand() % 100;  // números entre 0 e 99
    }
}


int main(){
    int v[20];
    gerar_vetor_aleatorio(v, 20);

    size_t size_v = sizeof(v) / sizeof(v[0]);

    insertion_sort(v, size_v);

    for(int i = 0; i < size_v; i++){
        printf("[%d] ", v[i]);
    }

    return 0;
}