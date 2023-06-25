#include <stdlib.h>
#include <stdio.h>
#include "tabHash.h"

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
                printf("\nno delete: %d\n", hash->t[i]->value);   
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

void insertNo(Node *no, Node *newNode){
    if(no->next != NULL){
        insertNo(no->next, newNode);
    }
    no->next = newNode;
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
                printf("\nValor %d inserido com sucesso!", value);
            }
            else{
                hash->t[pos] = newNode;
                hash->n += 1;
                ok = 1;
                printf("\nValor %d inserido com sucesso!", value);
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

void rehashing(Hash *hash, int qtd){
    if(hash != NULL){
        Hash* newHash;
        newHash = newTable(qtd);
        newHash->n = hash->n;
        printf("\ntam: %d\n", newHash->m);
        for(int i = 0; i < hash->m; i++){
            if(hash->t[i] != NULL){
                newHash->t[i] = hash->t[i]; 
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
    if(no != NULL){
        if(no->value == value){
            return 1;
        }
        searchList(no->next, value);
    }
    return 0;
}

int searchTable(Hash *hash, int value){
    if(hash != NULL){
        int existe = 0;
        for(int i = 0; i < hash->m; i++){
            if(hash->t[i] != NULL){
                existe = searchList(hash->t[i], value);
                if(existe == 1){
                    return 1;
                }
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

int main(){

    int op, valor, ret;
    Hash* hash = newTable(1);
    
    do{

        system("clear||cls");

        printf("\n=============================\n");
        printf("| 0- Encerrar o Programa    |\n");
        printf("| 1- Inserir Elemento       |\n");
        printf("| 2- Imprimir Tabela        |\n");
        printf("| 3- Buscar elemento        |\n");
        printf("=============================\n");
        printf("Selecione uma Opção: ");

        scanf("%d", &op);

        if(op == 0){
            printf("\nSaindo...\n");
        }
        else if(op == 1){
            printf("\nInforme o Valor: ");
            scanf("%d", &valor);
            insertTable(hash, valor);
            printf("\n\nqtd: %d - tam: %d\n", hash->n, hash->m);
            getchar();
        } // falta refazer a função de busca
        else if(op == 2){
            printf("\nImpressão da Tabela:\n\n");
            printTable(hash);
            getchar();
        }
        else if(op == 3){
            printf("\nInforme o Valor a ser buscado: ");
            scanf("%d", &valor);
            ret = searchTable(hash, valor);
            if(ret == 1){
                printf("\nValor: %d foi encontrado!\n", valor);
                getchar();
            }
            else{
                printf("\nValor: %d não encontrado!\n", valor);
                getchar();
            }
        }
        else{
            printf("\nOpção inválida!\n");
        }
        printf("\n\nPresione <ENTER> para continuar\n");
        getchar();

    }while(op != 0);

    return 0;
}