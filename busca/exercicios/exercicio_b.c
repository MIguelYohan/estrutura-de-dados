#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct{
    int value1;
    int value2;
}TwoValues;

void merge(int *v, int *v1, int *v2, size_t size){
    size_t size_v1 = size / 2;
    size_t size_v2 = size - size_v1;
    int i = 0;
    int j = 0;
    int k = 0;

    for(i = 0; j < size_v1 && k < size_v2; i++){
        if(v1[j] <= v2[k]){
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

void merge_sort(int *v, size_t size){
    size_t mid;

    if(size > 1){
        mid = size / 2;

        int *v1 = malloc(sizeof(int) * mid);
        int *v2 = malloc(sizeof(int) * (size - mid));
        
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

int busca_binaria_first(int *v, size_t size, int key){
    int l = 0;
    int r = size - 1;
    int res = -1;

    while(l <= r){
        int m = l + (r - l) / 2;

        if(key == v[m]){
            res = m;
            r = m - 1;
        }

        else if(key < v[m]){
            r = m - 1;
        }

        else{
            l = m + 1;
        }
    }
    return res;
}

int busca_binaria_last(int *v, size_t size, int key){
    int l = 0;
    int r = size - 1;
    int res = -1;

    while(l <= r){
        int m = l + (r - l) / 2;

        if(key == v[m]){
            res = m;
            l = m + 1;
        }

        else if(key < v[m]){
            r = m - 1;
        }

        else{
            l = m + 1;
        }
    }
    return res;
}

// Achar indice que começa o valor x e oque termina exemplo:
// [1 1 2 2 2 2 3 4 7 8] -> x = 2 -> (3, 6)
TwoValues seach_quota(int *v, size_t size, int x){
    TwoValues r;
    int response1 = busca_binaria_first(v, size, x);
    int response2 = busca_binaria_last(v, size, x);

    if(response1 == -1){
        r.value1 = -1;
        r.value2 = -1;
        return r;
    }

    r.value1 = response1;
    r.value2 = response2;

    return r;
}

int main(){
    int n, q;
    int i;
    scanf("%d %d", &n, &q);
    int v[n];

    for(i = 0; i < n; i++){
        scanf("%d", &v[i]);
    }

    merge_sort(v, n);

    int x;
    for(i = 0; i < q; i++){
        scanf("%d", &x);
        TwoValues response = seach_quota(v, n, x);
        if(response.value1 != -1){
            printf("%d %d\n", response.value1 + 1, response.value2 + 1);
        }
        else{
            printf("%d\n", -1);
        }
    }

    return 0;
}