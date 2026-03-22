#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int busca_binaria(int *v, size_t n, int key) {
    // Espaço de busca: 
    int l = 0; // Primeiro elemento
    int r = n - 1; // Ultimo elemento

    while (l <= r) { // O loop continua enquanto o lado esquerdo não ultrapassar o direito
        int mid = l + (r - l) / 2; // Calculo do valor central 

        if (key == v[mid]) {
            return mid; /**Retorna a posição da chave**/
        }
        else if (key < v[mid]) {
            r = mid - 1;
        }
        else {
            l = mid + 1;
        }

    }
    return -1; /**Chave não encontrada**/
 }