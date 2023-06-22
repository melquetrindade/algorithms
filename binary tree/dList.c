#include <stdio.h>
#include <stdlib.h>

typedef struct dList{
    int value;
    struct dList *prev;
    struct dList *next; 
}Dlist;

typedef struct lista{
    Dlist *inicio;
}Lista;

void insert_next(Dlist *no, int valor){
    if(no->next == NULL){
        Dlist *new_no = (Dlist *)malloc(sizeof(Dlist));
        new_no->value = valor;
        new_no->prev = no;
        new_no->next = NULL;

        no->next = new_no;
    }
    else{
        insert_next(no->next, valor);
    }
}

void insert(Lista *lista, int valor){
    if(lista->inicio == NULL){
        Dlist *new_no = (Dlist *)malloc(sizeof(Dlist));
        new_no->value = valor;
        new_no->prev = NULL;
        new_no->next = NULL;

        lista->inicio = new_no;
    }
    else{
        insert_next(lista->inicio, valor);
    }
}

void imprimir(Dlist *inicio){
    if(inicio != NULL){
        printf("%d ", inicio->value);
        imprimir(inicio->next);
    }
}

int main(){

    int op, valor;
    Lista lista;
    lista.inicio = NULL;

    Dlist *no = (Dlist*)malloc(sizeof(Dlist));
    no->value = 0;
    no->prev = NULL;
    no->next = NULL;

    do{

        system("clear||cls");

        printf("\n=============================\n");
        printf("| 0- Encerrar o Programa    |\n");
        printf("| 1- Inserir Elemento       |\n");
        printf("| 2- Imprimir Lista         |\n");
        printf("| 3- Imprimir o menor valor |\n");
        printf("| 4- Imprimir o maior valor |\n");
        printf("| 5- Buscar elemento        |\n");
        printf("=============================\n");
        printf("Selecione uma Opção: ");

        scanf("%d", &op);

        if(op == 0){
            printf("\nSaindo...\n");
        }
        else if(op == 1){
            printf("\nInforme o Valor: ");
            scanf("%d", &valor);
            insert(&lista, valor);
            printf("\nValor %d inserido com sucesso!", valor);
            getchar();
        }
        else if(op == 2){
            printf("\nImpressão da Lista:\n\n");
            imprimir(lista.inicio);
            getchar();
        }
        else if(op == 3){
            //printf("\n o menor valor da árvore é: %d", min(tree.root));
            printf("\n a fazer");
            getchar();
        }
        else if(op == 4){
            //printf("\n o maior valor da árvore é: %d", max(tree.root));
            getchar();
        }
        else if(op == 5){
            /*
            printf("\nInforme o Valor a ser buscado: ");
            scanf("%d", &valor);
            no = search(tree.root, valor);
            if(no == NULL){
                printf("\nvalor do elemento informado não foi encontrado!\n");
                getchar();
            }
            else{
                printf("\nO endereço do nó encontrado é %p e o valor do nó é: %d", no, no->value);
                getchar();
            }*/
            printf("\n a fazer");
            getchar();
        }
        else{
            printf("\nOpção inválida!\n");
        }
        printf("\n\nPresione <ENTER> para continuar\n");
        getchar();

    }while(op != 0);

    return 0;
}