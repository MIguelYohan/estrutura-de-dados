#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char text[11];
    size_t size;
}String;

void merge(String *v, String *v1, String *v2, size_t size){
    size_t size_v1 = size / 2;
    size_t size_v2 = size - size_v1;
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;

    for (i = 0; j < size_v1 && k < size_v2; i ++){
        if (strcmp(v1[j].text, v2[k].text) <= 0){
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
        String *v2 = malloc(sizeof(String) * (size - mid)); 
        
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

// Contar qual string aparece mais no vetor retorna a contagem
int max_count(String *v, size_t size){
    int cont = 1;
    int max = 1;
    for(int i = 0; i < size - 1; i++){
        if(strcmp(v[i].text, v[i+1].text) == 0){
            cont += 1;
            if(cont > max){
                max = cont;
            }
        }
        else{
            cont = 1;
        }
    }
    return max;
}

// Contar qual string aparece mais no vetor retorna a string
String max_string(String *v, size_t size){
    int cont = 1;
    int max = 1;
    String max_string;
    strcpy(max_string.text, v[0].text); // Inicializa a max_string

    for(int i = 0; i < size - 1; i++){
        if(strcmp(v[i].text, v[i+1].text) == 0){
            cont += 1;
            if(cont > max){
                max = cont;
                strcpy(max_string.text, v[i].text);
            }
        }
        else{
            cont = 1;
        }
    }
    return max_string;
}

    
int main(){
    int n, i;
    scanf("%d", &n);
    String v[n];

    for(i = 0; i < n; i++){
        scanf("%s", v[i].text);
    }

    merge_sort(v, n);
    int max_c = max_count(v, n);
    String max_name = max_string(v, n);

    printf("%s %d", max_name.text, max_c);

    return 0;
}  