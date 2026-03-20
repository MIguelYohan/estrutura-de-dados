#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct{
    int num_ori; // Guarda o numero original
    int m_remainder; // Guarda o resto de num_ori por m
}Remainder;

void merge(Remainder *v, Remainder *v1, Remainder *v2, size_t size){
    size_t size_v1 = size / 2;
    size_t size_v2 = size - size_v1;
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;

    for (i = 0; j < size_v1 && k < size_v2; i ++){
        if (v1[j].m_remainder < v2[k].m_remainder){
            v[i] = v1[j++];
        }
        
        else if(v1[j].m_remainder > v2[k].m_remainder){
            v[i] = v2[k++];
        }

        else if(v1[j].m_remainder == v2[k].m_remainder){
            // Aqui possuem todas as condicionais separadas por OU, todas tem como resultado v2[k] primeiro por tanto unifiquei todas
            if(
                (v1[j].num_ori % 2 == 0 && v2[k].num_ori % 2 != 0) ||
                ((v1[j].num_ori % 2 == 0 && v2[k].num_ori % 2 == 0) && v2[k].num_ori < v1[j].num_ori) ||
                ((v1[j].num_ori % 2 != 0 && v2[k].num_ori % 2 != 0) && v1[j].num_ori < v2[k].num_ori)
            ){
                v[i] = v2[k++];
            }
            else{
                v[i] = v1[j++];
            }
        }
    }   
    
    while (j < size_v1) {
        v[i++] = v1[j++];
    }

    while (k < size_v2) {
        v[i++] = v2[k++];
    }
}


void merge_sort(Remainder *v, size_t size){
    size_t mid;

    if (size > 1){
        mid = size / 2;

        Remainder *v1 = malloc(sizeof(Remainder) * mid);
        Remainder *v2 = malloc(sizeof(Remainder) * (size - mid));
        
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

void calc_remainder(Remainder *v, size_t size, int m){
    for(int i = 0 ; i < size; i++){
        v[i].m_remainder = v[i].num_ori % m;
    }
}

int main(){
    int n, m;
    int i;
    scanf("%d %d", &n, &m);
    Remainder v[n];

    for(i = 0; i < n; i++){
        scanf("%d", &v[i].num_ori);
    }

    calc_remainder(v, n, m);
    merge_sort(v, n);

    for(i = 0; i < n; i++){
        printf("%d\n", v[i].num_ori);
    }
}