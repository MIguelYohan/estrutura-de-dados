#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
// Utilizando o merge sort

typedef struct{
    char palavra[10];
    size_t tamanho;
} String;


void merge(String *v, String *v1, String *v2, size_t size){
    size_t size_v1 = size / 2;
    size_t size_v2 = size - size_v1;
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;

    for (i = 0; j < size_v1 && k < size_v2; i ++){
        if (v1[j].tamanho <= v2[k].tamanho){
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


void merge_sort(String *v, size_t size){
    size_t mid;

    if (size > 1){ 
        mid = size / 2;

        String *v1 = malloc(sizeof(String) * mid);
        String *v2 = malloc(sizeof(String) * size - mid); 
        
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


int main(){
    int n;

    scanf("%d", &n);
    String vet[n];

    for(int i = 0; i < n; i++){
        scanf("%s", vet[i].palavra);
        vet[i].tamanho = strlen(vet[i].palavra);
    }

    merge_sort(vet, n);

    for(int i = 0; i < n; i++){
        printf("%s\n", vet[i].palavra);
    }

    return 0;
}