#include <stdio.h>
# include <stddef.h>
#include <stdlib.h>
#include <time.h>

// Escolha de um pivô (aleatório)
// Divisao em dois vetores a partir do original
// -> Maiores ou iguais que o pivô e Menores que o pivô
// A escolha do pivô ocorre novamente
// Isso ocorre recursivamente até que o vetor seja mínimo

void swap(int *v, int ind_a, int ind_b){
    int aux;
    aux = v[ind_a];
    v[ind_a] = v[ind_b];
    v[ind_b] = aux; 
}


// Toda iteração do quick sort tem com base dividir o vetor em 2 e achar a posição certa do pivô
static size_t partition(int *vet, int esq,int dir,int pivot){
    size_t pos, i;

    swap(vet, pivot, dir); // joga o pivô pro final do vetor
    pos = esq; // pos marca o próximo lugar onde deve-se colocar um número menor que o pivô

    for(i = esq; i < dir; i++){ // Varre o vetor até o valor antes do pivô pois este está em dir
        if (vet[i] < vet[dir]){ // Se o valor for menor que o pivô
            swap(vet, i, pos); // Coloca ele no final da parte dos menores e vet[pos] é maior ou igual ao pivô (ou ainda não classificado)
            pos++; // Agora o valor para preencher no vetor menor é o próximo
        }
    }
    swap(vet, dir, pos); // Troca o pivô para o final dos valores menores ou seja, no meio entre menores e maiores
    return pos;
}


void quick_sort_helper(int*v, int l,int r){
    if (l < r){ // Fim da recursão quando o vetor for mínimo
        size_t pos = partition(v,l,r,r); // Particiona o vetor (pos = posicao do pivô) -> Neste caso o pivô está sendo escolhido como o ultimo valor do vetor, r
        quick_sort_helper(v, l, pos - 1); // Recursão pela parte esquerda do vetor (valores menores)
        quick_sort_helper(v, pos + 1, r); // Recursão pela parte direita do vetor (valores maiores) 
    }
}


void quick_sort(int *v, size_t size){
    quick_sort_helper(v,0,size-1);
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

    quick_sort(v, size_v);

    for(int i = 0; i < size_v; i++){
        printf("[%d] ", v[i]);
    }

    return 0;
}