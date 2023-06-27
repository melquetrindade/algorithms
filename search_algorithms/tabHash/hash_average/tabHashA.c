#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "tabHash.h"

Hash* newTable(int tam){
    Hash* hash = (Hash*)malloc(sizeof(Hash));
    if(hash != NULL){
        hash->m = tam;
        hash->t = (Node**)malloc(tam*sizeof(Node*));
        if(hash->t == NULL){
            free(hash);
            return NULL;
        }
        hash->n = 0;
        for(int i = 0; i < hash->m; i++){
            hash->t[i] = NULL;
        }
        return hash;
    }
    return NULL;
}

void deleteNo(Node *node){
    if(node->next != NULL){
        deleteNo(node->next);
    }
    free(node);
}

void deleteTable(Hash* hash){
    if(hash != NULL){
        for(int i = 0; i < hash->m; i++){
            if(hash->t[i] != NULL){
                /*
                Node* noAtual = hash->t[i];
                Node* noProx = hash->t[i]->next;
                while(noAtual != NULL){
                    free(noAtual);
                    noAtual = noProx;
                }
                free(noAtual);
                free(noProx);
                free(hash->t[i]);*/
                deleteNo(hash->t[i]);   
            }
        }
        free(hash->t);
        free(hash);
    }
}

int hashing(int value, int m){
    return value % m;
}

double fatorCarga(int n, int m){
    return n/m;
}

void insertNo(Node *no, Node *newNode){
    if(no->next != NULL){
        insertNo(no->next, newNode);
    }
    else{
        no->next = newNode;
    }
}

void insertTable(Hash* hash, int value){
    int ok = 0;
    if(hash != NULL){
        int existe = searchTable(hash, value);
        if(existe == 0){
            int pos = hashing(value, hash->m);
            Node* newNode = (Node*)malloc(sizeof(Node));
            newNode->value = value;
            newNode->next = NULL;

            if(hash->t[pos] != NULL){
                insertNo(hash->t[pos], newNode);
                hash->n += 1;
                ok = 1;
            }
            else{
                hash->t[pos] = newNode;
                hash->n += 1;
                ok = 1;
            }
        }
        else{
            printf("\nEste valor já foi inserido\n");
        }
    }
    if(ok == 1){
        double fator = fatorCarga(hash->n, hash->m);
        if(fator >= 1){
            rehashing(hash, 2*hash->m);
        }
    }
}

void rehashInsert(Hash *hash, Node* no){
    if(no != NULL){
        int pos = hashing(no->value, hash->m);

        if(hash->t[pos] != NULL){
            Node* aux = no->next;
            no->next = NULL;
            insertNo(hash->t[pos], no);
            rehashInsert(hash, aux);
        }
        else{
            Node* aux = no->next;
            no->next = NULL;
            hash->t[pos] = no;
            rehashInsert(hash, aux);
        }
    }
}

void rehashing(Hash *hash, int qtd){
    if(hash != NULL){
        Hash* newHash;
        newHash = newTable(qtd);
        newHash->n = hash->n;
        for(int i = 0; i < hash->m; i++){
            if(hash->t[i] != NULL){
                rehashInsert(newHash, hash->t[i]); 
            }
        }
        //printf("\nno new hash: %d\n", newHash->t[0]->value);
        //deleteTable(hash);
        hash->m = newHash->m;
        hash->n = newHash->n;
        hash->t = newHash->t;
        //deleteTable(newHash);
    }
}

int searchList(Node *no, int value){
    if(no->next != NULL){
        if(no->next->value == value){
            return 1;
        }
        else{
            searchList(no->next, value);
        }
    }
    else{
        return 0;
    }
}

int searchTable(Hash *hash, int value){
    if(hash != NULL){
        int exist;
        int pos = hashing(value, hash->m);
        if(hash->t[pos] != NULL){
            if(hash->t[pos]->value == value){
                exist = 1;
            }
            else{
                
                exist = searchList(hash->t[pos], value);
            }
            if(exist == 1){
                return 1;
            }
        }
        return 0;
    }
}
//====================
void printLista(Node *no){
    if(no->next != NULL){
        printLista(no->next);
    }
    printf("%d -> ", no->value);
}

void printTable(Hash *hash){
    if(hash != NULL){
        for(int i = 0; i < hash->m; i++){
            printf("\nt[%d]: ", i);
            if(hash->t[i] != NULL){
                printLista(hash->t[i]);
            }
        }
    }
}

int main(int argc, char **argv){

    struct timespec a, b;
    unsigned int t, n;
    int i, ret;

    Hash* hash = newTable(1);

    n = atoi(argv[1]);  
    srand(time(NULL));
    for (i = 0; i < n; i++){
        insertTable(hash, rand());
    }

    clock_gettime(CLOCK_MONOTONIC, &b);
    ret = searchTable(hash, n);
    clock_gettime(CLOCK_MONOTONIC, &a);

    t = (a.tv_sec * 1e9 + a.tv_nsec) - (b.tv_sec * 1e9 + b.tv_nsec);
    /*
    if(ret == 1){
        printf("\nValor: %d foi encontrado!\n", n);
        getchar();
    }
    else{
        printf("\nValor: %d não encontrado!\n", n);
        getchar();
    }*/

    //printTable(hash);

    printf("\n%u\n", t);

    return 0;
}