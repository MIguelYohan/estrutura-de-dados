// Receber valores para um vetor do tipo Ocorrency
// Para cada valor do vetor guardar a ocorrencia dele usando a funcao search_count (usar busca bin)
// ordenar o vetor por ocorrencia

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct{
    int value;
    int ocurrence;
}Occurrece;

void merge_value(Occurrece *v, Occurrece *v1, Occurrece *v2, size_t size){
    size_t size_v1 = size / 2;
    size_t size_v2 = size - size_v1;
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;

    for (i = 0; j < size_v1 && k < size_v2; i ++){
        if (v1[j].value <= v2[k].value){
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

void merge_sort_value(Occurrece *v, size_t size){
    size_t mid;

    if (size > 1){ 
        mid = size / 2; 

        Occurrece *v1 = malloc(sizeof(Occurrece) * mid); 
        Occurrece *v2 = malloc(sizeof(Occurrece) * size - mid);
        
        int i;
        for(i = 0; i < mid; i++){
            v1[i] = v[i]; 
        }

        for(i = mid; i < size; i++){
            v2[i - mid] = v[i]; 
        }

        merge_sort_value(v1, mid);
        merge_sort_value(v2, size - mid);

        merge_value(v, v1, v2, size);

        free(v1);
        free(v2);
    }
}

void merge_ocurrence(Occurrece *v, Occurrece *v1, Occurrece *v2, size_t size){
    size_t size_v1 = size / 2;
    size_t size_v2 = size - size_v1;
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;

    for (i = 0; j < size_v1 && k < size_v2; i ++){
        if((v1[j].ocurrence == v2[k].ocurrence) && (v1[j].value > v2[k].value)){
            v[i] = v1[j++];
        }

        else if((v1[j].ocurrence == v2[k].ocurrence) && (v1[j].value < v2[k].value)){
            v[i] = v2[k++];
        }

        else if (v1[j].ocurrence > v2[k].ocurrence){
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

void merge_sort_ocurrence(Occurrece *v, size_t size){
    size_t mid;

    if (size > 1){ 
        mid = size / 2; 

        Occurrece *v1 = malloc(sizeof(Occurrece) * mid); 
        Occurrece *v2 = malloc(sizeof(Occurrece) * size - mid);
        
        int i;
        for(i = 0; i < mid; i++){
            v1[i] = v[i]; 
        }

        for(i = mid; i < size; i++){
            v2[i - mid] = v[i]; 
        }

        merge_sort_ocurrence(v1, mid);
        merge_sort_ocurrence(v2, size - mid);

        merge_ocurrence(v, v1, v2, size);

        free(v1);
        free(v2);
    }
}

int busca_binaria_i(Occurrece *v, size_t n, int key) {
    int l = 0;
    int r = n - 1;
    int res = -1;

    while (l <= r) {
        int mid = l + (r - l) / 2;

        if (key == v[mid].value) {
            res = mid;
            r = mid - 1;
        }
        else if (key < v[mid].value) {
            r = mid - 1;
        }
        else {
            l = mid + 1;
        }

    }
    return res;
}

int busca_binaria_f(Occurrece *v, size_t n, int key) {
    int l = 0;
    int r = n - 1;
    int res = -1;

    while (l <= r) {
        int mid = l + (r - l) / 2;

        if (key == v[mid].value) {
            res = mid;
            l = mid + 1;
        }
        else if (key < v[mid].value) {
            r = mid - 1;
        }
        else {
            l = mid + 1;
        }

    }
    return res;
}

int search_count(Occurrece *v, size_t size, int x){
    int start = busca_binaria_i(v, size, x);
    int finish = busca_binaria_f(v, size, x);

    return finish - start + 1;
}

int main(){
    int n;
    scanf("%d", &n);
    Occurrece v[n];

    int i;
    for(i = 0; i < n; i++){
        scanf("%d", &v[i].value);
    }

    merge_sort_value(v, n);

    for(i = 0; i < n; i++){
        int c = search_count(v, n, v[i].value);
        v[i].ocurrence = c;
    }

    merge_sort_ocurrence(v, n);

    for(i = 0; i < n; i++){
        printf("%d ", v[i].value);
    }

    return 0;
}