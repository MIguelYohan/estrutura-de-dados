# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>
# include <time.h>

// O mergesort se baseia no conceito de merge -> união de dois vetores
// função recursiva - caso base: sequência unitária ou vazia
// merge entre v1 e v2 -> v1 = [1,3,5] + v2 = [0,2,4] = [0,1,2,3,4,5]

void merge(int *v, int *v1, int *v2, size_t size){
    size_t size_v1 = size / 2;
    size_t size_v2 = size - size_v1;
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;

    // percorrendo os dois vetores ao mesmo tempo
    // j percorre o tamanho do v1 e k o tamanho do v2
    for (i = 0; j < size_v1 && k < size_v2; i ++){
        // se o valor do v1 for maior igual o do v2 coloca o valor do v1 primeiro e ja incrementa o j
        if (v1[j] <= v2[k]){
            v[i] = v1[j++]; // reutiliza o vetor original do comeco como vetor resultado
        }
        
        // se não então o valor a ser adicionado como primeiro é do v2 e incrementa k
        else{
            v[i] = v2[k++];
        }
    }
    
    // Se ainda restam elementos na primeira partição 
    while (j < size_v1) {
    // Copiamos os elementos para o vetor resultado 
        v[i++] = v1[j++];
    }

    // Se ainda restam elementos na segunda partição 
    while (k < size_v2) {
    // Copiamos os elementos para o vetor resultado 
        v[i++] = v2[k++];
    }
}


void merge_sort(int *v, size_t size){
    size_t mid;

    if (size > 1){ // Caso base da recursão
        mid = size / 2; // Tamanho da metade do vetor original

        // criamos dois vetores auxiliares
        int *v1 = malloc(sizeof(int) * mid); // primeira metade do vetor original
        int *v2 = malloc(sizeof(int) * size - mid); // segunda metade do vetor origina
        
        int i;
        for(i = 0; i < mid; i++){
            v1[i] = v[i]; // cópia da primeira metade do vetor original
        }

        for(i = mid; i < size; i++){
            v2[i - mid] = v[i]; // cópia da primeira metade do vetor original
        }

        // Divisoes recursivas dos vetores
        merge_sort(v1, mid);
        merge_sort(v2, size - mid);
        // Ao fim da recursão dos dois vetores parte para o merge que realmente ordena
        merge(v, v1, v2, size);
        // liberar espaço alocado
        free(v1);
        free(v2);
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

    merge_sort(v, size_v);

    for(int i = 0; i < size_v; i++){
        printf("[%d] ", v[i]);
    }

    return 0;
}