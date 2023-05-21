#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int *vet, int s, int e)
{
    int d;
    d = s-1;
    for(int i = s; i <= (e-1); i++){
        if(vet[i] <= vet[e]){
            d = d+1;
            swap(&vet[d], &vet[i]);
        }
    }

    swap(&vet[d + 1], &vet[e]);
    return d+1;
}

void quick_sort(int *v,int s, int e)
{
    int p;
    if (s < e) {
        p = partition(v, s, e);
        quick_sort(v, s, p-1);
        quick_sort(v, p+1, e);
    }
}

int main(int argc, char **argv)
{
    struct timespec a, b;
    unsigned int t, n;
    int i, *v;

    n = atoi(argv[1]);
    v = (int *) malloc(n * sizeof(int));
    srand(time(NULL));
    for (i = 0; i < n; i++){
        v[i] = rand();
    }

    clock_gettime(CLOCK_MONOTONIC, &b);
    quick_sort(v, 0, n-1);
    clock_gettime(CLOCK_MONOTONIC, &a);

    t = (a.tv_sec * 1e9 + a.tv_nsec) - (b.tv_sec * 1e9 + b.tv_nsec);

    printf("%u\n", t);

    free(v);

    return 0;
}