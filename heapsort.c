// Heap: Árvore de valores com as seguintes propriedades:
// -> O elemento pai é >= do que os seus filhos (caso existam)
// -> O filho a esquerda é uma heap
// -> O filho da direita também é uma heap.

// É possivel representar a árvore como um vetor
// Regra básica para navegar na heap usando um vetor:
// Filho da esquerda está na posição 2i + 1
// Filho da direita está na posição 2i + 2

// O processo de Heapify consiste em corrigir a violação da propriedade de heap em um nó
// Você assume que os filhos já são heaps válidos, e então ajusta o nó atual para que ele também respeite a propriedade.

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>

static void heapify(int *v, size_t i, size_t size) { // i -> pai do nó a ser ajustado
    int left;
    int right;
    int largest;
    while (i < size) { // Garante que as trocas não invadam a parte ordenada
        left = (i * 2) + 1;
        right = (i * 2) + 2;
        largest = i;
        if (left < size && v[left] > v[largest]) { // "left < size" garante que o valor está na heap
            // Compara o pai do nó com o valor da esquerda
            largest = left; // guarda o indice do maior valor
        }
        if (right < size && v[right] > v[largest]) {
            largest = right;
        }
        if (i == largest) { // Se o valor pai já for o maior entre os filhos, não faz nada
            break;
        }
        // Acontece a troca
        int swp = v[i]; // Guarda o valor do pai atual
        v[i] = v[largest]; // O pai do nó recebe o maior valor
        v[largest] = swp; // Completa a trroca
        i = largest; // Novo pai do nó
    }
}

static void make_heap(int *v, size_t size) { // Monta um max_heap novamente após o heap_sort acontecer
    int i;
    for (i = size / 2; i >= 0; i--) { // size/2 é o ultimo valor do vetor a ter filhos
        heapify(v, i, size);
    }
} // Ao final temos uma heap estruturada corretamente

void heap_sort(int *v, size_t size) {
    int i;
    make_heap(v, size); // Monta a heap
    for (i = size - 1; i > 0; i--) {
        // Faz a troca do primeiro com o ultimo, na próxima iteração irá desconsiderar o ultimo (i--) pois já está ordenado.
        int swp = v[i];
        v[i] = v[0];
        v[0] = swp;
        heapify(v, 0, i);
    }
}

void gerar_vetor_aleatorio(int *v, size_t size){
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        v[i] = rand() % 100;  // números entre 0 e 99
    }
}

int main(){
    int size = 1000;
    int v[size];
    gerar_vetor_aleatorio(v, size);

    heap_sort(v, size);

    for(int i = 0; i < size; i++){
        printf("[%d] ", v[i]);
    }

    return 0;
}