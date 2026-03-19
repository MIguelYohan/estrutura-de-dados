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
        if (abs(v1[j]) <= abs(v2[k])){ // Para que o count_zeros nao pule os negativos
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

int count_zeros(int *v, size_t size){
    int count_zeros = 0;
    for(int i = 0; i < size; i++){
        if(v[i] == 0){
            count_zeros ++;
        }
    }
    return count_zeros;
}

int is_balanced(int *v, size_t size, size_t count_zeros){
    int i;
    for(int i = count_zeros; i < size - 1; i++){
        if((v[i] != 0 && (v[i] % v[i+1] != 0)) && (v[i+1] != 0 && (v[i+1] % v[i] != 0))){
            return 0;
        }
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
    int count = count_zeros(v, n);
    int response = is_balanced(v, n, count);

    if(response){
        printf("Sim");
    }
    else{
        printf("Nao");
    }

    return 0;
}