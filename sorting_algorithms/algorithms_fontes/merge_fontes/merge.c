#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge(int *vet, int s,int m, int e)
{
    int p, q;
    p = s;
    q = m + 1;
    int w[e-s];

    for(int i = 1; i <= (e-s+1); i++){
        if((q > e) || ((p<= m) && vet[p] < vet[q])){
            w[i] = vet[p];
            p = p+1;
        }
        else{
            w[i] = vet[q];
            q = q+1;
        }
    }
    for(int j = 1; j <= (e-s+1); j++){
        vet[s+j-1] = w[j];
    }

}

void merge_sort(int *v,int s, int e)
{
    int m;
    if (s < e) {
        m = (s + e)/2;
        merge_sort(v, s, m);
        merge_sort(v, m+1, e);
        merge(v, s, m, e);
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
    merge_sort(v, 0, n-1);
    clock_gettime(CLOCK_MONOTONIC, &a);


    t = (a.tv_sec * 1e9 + a.tv_nsec) - (b.tv_sec * 1e9 + b.tv_nsec);

    printf("%u\n", t);

    free(v);

    return 0;
}