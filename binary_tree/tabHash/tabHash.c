#include <stdlib.h>
#include <stdio.h>

typedef struct hash{
    struct node** t;
    unsigned int m;
    unsigned int n;
}Hash;

typedef struct node{
    int value;
    struct node* next;
}Node;

Hash* newTable(int tam){
    Hash* hash = (Hash*)malloc(sizeof(Hash));
    if(hash != NULL){
        //printf("\nentrou aqui\n");
        hash->m = tam;
        hash->t = (Node**)malloc(tam*sizeof(Node*));
        if(hash->t == NULL){
            //printf("\nentrou aqui 2\n");
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

void deleteTable(Hash* hash){
    if(hash != NULL){
        for(int i = 0; i < hash->m; i++){
            if(hash->t[i] != NULL){
                Node* noAtual = hash->t[i];
                Node* noProx = hash->t[i]->next;
                while(noAtual != NULL){
                    free(noAtual);
                    noAtual = noProx;
                }
                free(noAtual);
                free(noProx);   
            }
        }
        free(hash->t);
        free(hash);
    }
}

int hashing(int value, int m){
    return value % m;
}

double fatorCarga(unsigned int n, unsigned int m){
    return n/m;
}


int insertTable(Hash* hash, int value){
    if(hash != NULL){
        int pos = hashing(value, hash->m);

        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->value = value;
        newNode->next = NULL;

        hash->t[pos] = newNode;
        hash->n += 1;
        return 1;

    }
    return 0;
}

void insere(Node *node, Node* newNode){
    if(node != NULL){
        newNode = node;
        insere(node->next, newNode->next);
    }
}

void rehashing(Hash *hash, int qtd){
    if(hash != NULL){
        Hash* newHash;
        newHash = newTable(qtd);
        printf("\nqtd: %d\n", newHash->m);
        for(int i = 0; i < hash->m; i++){
            if(hash->t[i] != NULL){
                //insere(hash->t[i], newHash->t[i]);
                newHash->t[i] = hash->t[i]; 
            }
        }
        printf("\nno new hash: %d\n", newHash->t[0]->value);
        /*
        for(int j = 0; j < newHash->m; j++){
            printf("\nt[%d]: %p\n", j, newHash->t[j]);
        }*/
        //deleteTable(hash);
        hash->m = newHash->m;
        hash->n = newHash->n;
        hash->t = newHash->t;
        free(newHash);
        //return hash;
        /*
        hash = newHash;
        for(int k = 0; k < hash->m; k++){
            printf("\nt[%d]: %p\n", k, hash->t[k]);
        }*/
        //free(newHash);
    }
    //return hash;
}

int main(){

    Hash* hash = newTable(1);
    //printf("\npassou da criação\n");

    //printf("\ntam da tab: %d - ele: \n", hash->m);

    //deleteTable(hash);

    int insertOk = insertTable(hash, 4);

    //printf("\npassou da inserção\n");
    
    if(insertOk == 1){
        double fator = fatorCarga(hash->n, hash->m);
        if(fator >= 1){
            //printf("\nfator: %0.1f\n", fator);
            rehashing(hash, 2*hash->m);
            for(int k = 0; k < hash->m; k++){
                printf("\nt[%d]: %p\n", k, hash->t[k]);
            }
        }
    }

    printf("\n%d\n", hash->t[0]->value);
    printf("\nqtd: %d\n", hash->m);
    

    return 0;
}