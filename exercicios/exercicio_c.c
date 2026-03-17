#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

// Ordenar o vetor por ordem de chegada
// Duas estadias ao mesmo tempo anula a outra (1, -1)
// Ao final imprimir o valor final de cadeiras necessárias para o dia

typedef struct{
    char time[9]; // Formato "HH:MM:SS"
    int status;
}Reserve;

// Implementação do merge_sort
void merge(Reserve *v, Reserve *v1, Reserve *v2, size_t size){
    size_t size_v1 = size / 2;
    size_t size_v2 = size - size_v1;
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;

    for (i = 0; j < size_v1 && k < size_v2; i ++){
        int cmp = strcmp(v1[j].time, v2[k].time);
        if(cmp < 0 || (cmp == 0 && v1[j].status > v2[k].status)){
            // Entradas vem antes de saídas no vetor ordenado quando entrada e saída são iguais
            v[i] = v1[j++];
        }
        
        else{
            v[i] = v2[k++];
        }
    }
    
    while (j < size_v1) {
        v[i++] = v1[j++];
    }

    while (k < size_v2) {
        v[i++] = v2[k++];
    }
}

void merge_sort(Reserve *v, size_t size){
    size_t mid;

    if (size > 1){
        mid = size / 2;

        Reserve *v1 = malloc(sizeof(Reserve) * mid);
        Reserve *v2 = malloc(sizeof(Reserve) * (size - mid));
        
        int i;
        for(i = 0; i < mid; i++){
            v1[i] = v[i];
        }

        for(i = mid; i < size; i++){
            v2[i - mid] = v[i]; 
        }

        merge_sort(v1, mid);
        merge_sort(v2, size - mid);

        merge(v, v1, v2, size);
        free(v1);
        free(v2);
    }
}

int minimum_chair(Reserve *v, size_t size){
    int i;
    int chairs = 0;
    int max_chairs = 0;

    for(i = 0; i < size; i++){
        chairs += v[i].status;
        if(chairs > max_chairs){
            max_chairs = chairs;
        }
    }

    return max_chairs;
}

int main(){
    int n;
    scanf("%d", &n);
    getchar();
    
    Reserve v[2 * n]; // Recebe o dobro do valor pois recebe dois valores por vez

    for(int i = 0; i < n; i++){
    scanf("%s %s", v[2*i].time, v[2*i + 1].time);

    v[2*i].status = 1;      // chegada
    v[2*i + 1].status = -1; // saída
}
    
    merge_sort(v, 2*n);
    int min_c = minimum_chair(v, 2*n);

    printf("%d\n", min_c);

    return 0;
}