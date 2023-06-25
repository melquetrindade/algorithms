#include <stdlib.h>
#include <stdio.h>

typedef struct lista{
    int m;
    int n;
}Lista;

typedef struct node{
    int value;
    struct node* next;
}Node;

int main(){

    int *tabela;

    tabela = (Node*)malloc(sizeof(Node));

    for(int i = 0; i<20; i++){
        *(tabela + i) = i+1;
    }
    //int n = (sizeof(tabela)/sizeof(int))/2;
    //printf("%d\n", n);
    for(int i = 0; i<20; i++){
        printf("%d", *(tabela + i));
    }

    return 0;
}