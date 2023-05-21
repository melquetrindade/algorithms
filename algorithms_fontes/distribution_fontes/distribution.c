#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int min(int *v, int n){
    int menor = v[0];
    for(int i = 1; i < n; i++){
        if(v[i] < menor){
            menor = v[i];
        }
    }
    return menor;
}

int max(int *v, int n){
    int maior = v[0];
    for(int i = 1; i < n; i++){
        if(v[i] > maior){
            maior = v[i];
        }
    }
    return maior;
}

void distribution_sort(int *v,int n)
{
    int s, b, c[n];
    s = min(v, n);
    b = max(v, n);

    int d;
    int w[b+1];
    for(int i = 0; i < (b+1); i++){
        w[i] = 0;
    }
    for(int i = 0; i < n; i++){
        w[v[i]] = w[v[i]]+1;
    }
    for(int i = 1; i < (b+1); i++){
        w[i] = w[i] + w[i-1];
    }
    
    for(int i = 0; i < n; i++){
        d = v[i];
        c[--w[d]] = v[i];
    }

    for(int i = 0; i < n; i++){
        v[i] = c[i];
    }
}

int main(int argc, char **argv){

    struct timespec a, b;
    unsigned int t, n;
    int i, *v;

    n = atoi(argv[1]);
    v = (int *) malloc(n * sizeof(int));
    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++){
        v[i] = rand() % 1000;
    }

    clock_gettime(CLOCK_MONOTONIC, &b);
    distribution_sort(v,n);
    clock_gettime(CLOCK_MONOTONIC, &a);

    t = (a.tv_sec * 1e9 + a.tv_nsec) - (b.tv_sec * 1e9 + b.tv_nsec);

    printf("%u\n", t);

    free(v);

    return 0;
}