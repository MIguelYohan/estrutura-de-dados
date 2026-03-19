#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char name[30];
    int publications;
    int ind_h;
    int *quotes;
}Author;

void merge_quotes(int *v, int *v1, int *v2, size_t size){
    size_t size_v1 = size / 2;
    size_t size_v2 = size - size_v1;
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;

    for (i = 0; j < size_v1 && k < size_v2; i ++){
        if (v1[j] >= v2[k]){
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

void merge_sort_quotes(int *v, size_t size){
    size_t mid;

    if (size > 1){
        mid = size / 2; 

        int *v1 = malloc(sizeof(int) * mid);
        int *v2 = malloc(sizeof(int) * size - mid);
        
        int i;
        for(i = 0; i < mid; i++){
            v1[i] = v[i];
        }

        for(i = mid; i < size; i++){
            v2[i - mid] = v[i];
        }

        merge_sort_quotes(v1, mid);
        merge_sort_quotes(v2, size - mid);
        merge_quotes(v, v1, v2, size);

        free(v1);
        free(v2);
    }
}

void merge(Author *v, Author *v1, Author *v2, size_t size){
    size_t size_v1 = size / 2;
    size_t size_v2 = size - size_v1;
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;

    for (i = 0; j < size_v1 && k < size_v2; i ++){
        if (v1[j].ind_h > v2[k].ind_h ||(v1[j].ind_h == v2[k].ind_h && strcmp(v1[j].name, v2[k].name) < 0)){ // Ordena por indice_h ou se forem iguais, por nome lexicograficamente
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

void merge_sort(Author *v, size_t size){
    size_t mid;

    if (size > 1){
        mid = size / 2;

        Author *v1 = malloc(sizeof(Author) * mid);
        Author *v2 = malloc(sizeof(Author) * size - mid);
        
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

void calculate_h_index(Author *v, size_t size){
    int i, j;
    for(i = 0; i < size; i++){
        int ind_h = 0;
        int quotes_amount = v[i].publications;
        for(j = 0; j < quotes_amount; j++){ // Navegando no numero de citações
            if(j + 1 <= v[i].quotes[j]){
                ind_h = j + 1;
            }
            else{
                break;
            }
        }
        v[i].ind_h = ind_h;
    }
}

int main(){
    int n;
    int i, j;
    scanf("%d", &n);
    Author v[n];

    for(i = 0; i < n; i++){
        scanf("%s %d", v[i].name, &v[i].publications);
        int quotes_amount = v[i].publications;
        v[i].quotes = malloc(sizeof(int) * quotes_amount); // Aloca um vetor para cada autor
        for(j = 0; j < quotes_amount; j++){
            scanf("%d", &v[i].quotes[j]); // Recebendo os valores em uma única linha
            getchar();
        }
        merge_sort_quotes(v[i].quotes, quotes_amount); // Ordena o quotes de cada autor
    }

    calculate_h_index(v, n);

    merge_sort(v, n); // Ordenando antes de mostrar os autores

    for(i = 0; i < n; i++){
        printf("%s %d\n", v[i].name, v[i].ind_h);
    }
    
    // libera memória de cada vetor quotes depois da execução
    for(i = 0; i < n; i++){
        free(v[i].quotes);
}

    return 0;
}