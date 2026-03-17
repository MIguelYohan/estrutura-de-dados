#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

// Ordenar o vetor por ordem de chegada
// Duas estadias ao mesmo tempo anula a outra (1, -1)
// Ao final imprimir o valor final de cadeiras necessárias para o dia

typedef struct{
    char time[18]; // Formato "HH:MM:SS HH:MM:SS\0" possui 17 caracteres + \0
    char arrival_time[9];
    char exit_time[9];
}Reserve;

// Implementação do merge_sort
void merge(Reserve *v, Reserve *v1, Reserve *v2, size_t size){
    size_t size_v1 = size / 2;
    size_t size_v2 = size - size_v1;
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;

    for (i = 0; j < size_v1 && k < size_v2; i ++){
        if(strcmp(v1[j].arrival_time, v2[k].arrival_time) <= 0){
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
        Reserve *v2 = malloc(sizeof(Reserve) * size - mid);
        
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
    int chairs = 1;
    for(i = 0; i < size - 1; i++){
        // Logica para saber se duas pessoas estão ao mesmo tempo no local
        
    }

    return chairs;
}

int main(){
    int n;
    scanf("%d", &n);
    getchar();
    
    Reserve v[n];

    for(int i = 0; i < n; i++){
        scanf("%17[^\n]", v[i].time);
        getchar();
        // Separação dos valores de chegada e saída
        strncpy(v[i].arrival_time, v[i].time, 8);
        v[i].arrival_time[8] = '\0';

        strncpy(v[i].exit_time, v[i].time+9, 8);
        v[i].exit_time[8] = '\0';
    }

    merge_sort(v, n);
    int min_c = minimum_chair(v, n);

    printf("%d", min_c);

    return 0;
}