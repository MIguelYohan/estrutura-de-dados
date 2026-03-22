#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct{
    int value;
    int index;
}NumIndex;

int busca_binaria(NumIndex *v, size_t size, int key){
    int l = 0;
    int r = size - 1;

    while (l <= r){
        int mid = l + (r - l)/2;

        if(key == v[mid].value){
            return mid;
        }

        else if(key > v[mid].value){
            l = mid + 1;
        }

        else{
            r = mid - 1;
        }
    }
    return -1;
}

void merge(NumIndex *v, NumIndex *v1, NumIndex *v2, size_t size){
    size_t size_v1 = size / 2;
    size_t size_v2 = size - size_v1;
    int i = 0;
    int j = 0;
    int k = 0;

    for(i = 0; j < size_v1 && k < size_v2; i++){
        if(v1[j].value <= v2[k].value){
            v[i] = v1[j++];
        }

        else{
            v[i] = v2[k++];
        }
    }

    while(j < size_v1){
            v[i++] = v1[j++]; 
        }

    while(k < size_v2){
        v[i++] = v2[k++];
    }
}

void merge_sort(NumIndex *v, size_t size){
    size_t mid;

    if(size > 1){
        mid = size / 2;

        NumIndex *v1 = malloc(sizeof(NumIndex) * mid);
        NumIndex *v2 = malloc(sizeof(NumIndex) * (size - mid));
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
    int c;

    scanf("%d %d", &n, &c);
    NumIndex v[n];
    int i;
    for(i = 0; i < n; i++){
        scanf("%d", &v[i].value);
        v[i].index = i; // Guarda o indice original antes de ordenar
    }
    merge_sort(v, n);

    for(i = 0; i < n; i++){
        int r = c - v[i].value;

        int response = busca_binaria(v, n, r);

        if(response != -1 && response != i){ // Garante que a responsta não seja o mesmo valor 
            printf("%d %d", v[i].index + 1, v[response].index + 1);
            return 0;
        }
    }

    printf("%d", -1);
    return 0;
}