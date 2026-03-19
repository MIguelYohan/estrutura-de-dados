#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

void merge(int *v, int *v1, int *v2, size_t size){
    size_t size_v1 = size / 2;
    size_t size_v2 = size - size_v1;
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;

    for (i = 0; j < size_v1 && k < size_v2; i ++){
        if (v1[j] <= v2[k]){ // O menor divide o maior
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


void merge_sort(int *v, size_t size){
    size_t mid;

    if (size > 1){
        mid = size / 2;

        int *v1 = malloc(sizeof(int) * mid);
        int *v2 = malloc(sizeof(int) * (size - mid));
        
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

int is_balanced(int *v, size_t size){
    int i;
    for(int i = 0; i < size - 1; i++){
        // Pensar na lógica para condicoes em que a sequencia ja ordenada e equilibrada
    }
    return 1;
}

int main(){
    int n, i;
    scanf("%d", &n);
    int v[n];

    for(i = 0;i < n; i++){
        scanf("%d", &v[i]);
    }

    merge_sort(v, n);

    int response = is_balanced(v, n);

    if(response){
        printf("Sim");
    }
    else{
        printf("Nao");
    }

    return 0;
}