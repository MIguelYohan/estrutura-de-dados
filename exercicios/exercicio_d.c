#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct{
    char name[30]; // Máximo de 30 caracteres
    char first_time[7]; // Tempo: ss.mmm
    char second_time[7];
    char third_time[7];
}Classificatory;

typedef struct{
    int time; // Tempo em milésimos
    char name[30];
}DefaultTime;

void merge(DefaultTime *v, DefaultTime *v1, DefaultTime *v2, size_t size){
    size_t size_v1 = size / 2;
    size_t size_v2 = size - size_v1;
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;

    
    for (i = 0; j < size_v1 && k < size_v2; i ++){
        if (v1[j].time <= v2[k].time){
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
// Ordenar os valores já somados pela funcao sum_classificatories
void merge_sort(DefaultTime *v, size_t size){
    size_t mid;

    if (size > 1){
        mid = size / 2;

        DefaultTime *v1 = malloc(sizeof(DefaultTime) * mid);
        DefaultTime *v2 = malloc(sizeof(DefaultTime) * (size - mid));
        
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

void sum_classificatories(Classificatory *v, DefaultTime *times, size_t size){
    // Somar os classificatorias e devolver um vetor com os tempos somados em milésimos junto com o nome do piloto
}

int main(){
    int n;
    int i;
    scanf("%d", &n);
    
    Classificatory v[n];
    for(i = 0; i < n; i++){
        scanf("%s", v[i].name);
        scanf("%s %s %s", v[i].first_time, v[i].second_time, v[i].third_time);
    }

    DefaultTime times[n];
    sum_classificatories(v, times, n); // Copia valores de um vetor e padroniza-os em outro
    merge_sort(times, n); // Ordenamos o vetor com os tempos padronizados

    // Saída dos dados
    for(i = 0; i < n; i++){
        // Conversão dos valores
        int total_thousandths = times[i].time;
        int total_seconds = total_thousandths / 1000;
        int minutes = total_seconds / 60;
        int seconds = total_seconds % 60;
        int thousandths = total_thousandths % 1000;

        char minute_time[9];
        sprintf(minute_time, "%d:%02d.%03d", minutes, seconds, thousandths);

        printf("%d. %s - %s\n", i+1, times[i].name, minute_time);
    }

    return 0;
}