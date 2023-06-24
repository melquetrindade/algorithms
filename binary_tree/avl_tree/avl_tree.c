#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "avl_tree.h"

Node* createNo(int value){
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->value = value;
    new_node->h = 0;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->parent = NULL;

    return new_node;
}

Node* achaRoot(Node *no){

    if(no->parent != NULL){

        return achaRoot(no->parent);
    }
    return no;
}

int caso(Node *no){
    int fBalance = fatorBalance(no);
    if((fBalance > 1) && (fatorBalance(no->left) > 0)){
        return 1;
    } 
    else if((fBalance < -1) && (fatorBalance(no->right) < 0)){
        return 2;
    }
    else if((fBalance > 1) && (fatorBalance(no->left) < 0)){
        return 3;
    }
    return 4;
}

void balance(Node *no){
    printf("\nentrou no balance para o %d\n", no->value);

    no = no->parent;
    int fBalance = 0;
    int c = 0;
    
    while(no != NULL){
        if(no->left != NULL && no->right != NULL){
            printf("\nno valor: %d, L: %d, R: %d\n", no->value, no->left->value, no->right->value);
        }
        
        printf("\nno valor: %d, hL: %d, hR: %d\n", no->value, heigthNo(no->left), heigthNo(no->right));
        no->h = big(heigthNo(no->left), heigthNo(no->right)) + 1;
        printf("\nentrou no while para o %d com h: %d\n", no->value, no->h);
        fBalance = fatorBalance(no);
        if(fBalance < -1 || fBalance > 1){
            printf("\nentrou no fator para o %d\n", no->value);
            c = caso(no);
            if(c == 1){
                rotRigth(no);
                //print_tree(achaRoot(no));
            }
            else if(c == 2){
                rotLeft(no);
                printf("\n%d\n", achaRoot(no)->value);
                //print_tree(achaRoot(no));
            }
            else if(c == 3){
                rotLeft2(no->left);
                rotRigth(no);
                printf("\nno atual: %d\n", no->value);
                //print_tree(achaRoot(no));
                printf("\nvalor: %d, pai: %p\n", no->parent->value, no->parent->parent);
                printf("\nvalor: %d, pai: %p\n", no->parent->left->value, no->parent->left->parent);
                printf("\nvalor: %d, pai: %p\n", no->parent->right->value, no->parent->right->parent);
            }
            else{
                printf("ainda vou fazer");
            }
        }
        no = no->parent;
    }
    printf("\nsaiu do while\n");
}

void rotLeft2(Node *no){
    printf("=========================");

    printf("\nentrou no rotLeft2 para o %d\n", no->value);
    printf("\nno c == 2:\n");

    Node *rChild, *lChild;

    rChild = no->right; // salva o f a rigth 3: 4
    printf("\n%d\n", rChild->value);
    lChild = rChild->left; // salva o f a left do 4: nil

    rChild->left = no; // coloca o 3 como f a left de 4
    printf("\n%d\n", rChild->left->value);
    //printf("\n%d\n", rChild->right->value);
    no->right = lChild; // coloca o f a left de 4 para a rigth of three

    if(lChild != NULL){
        lChild->parent = no; // 3 passa a ser pai do filho a left do 4
    }

    rChild->parent = no->parent; // 4 passa a ser filho do 5
    if(no->parent != NULL){
        printf("\n%d\n", rChild->parent->value);
        //atualizar o filho do 6
        no->parent->left = rChild; // 5 passa a ser pai do 4
    }
    
    no->parent = rChild; // 3 passa a ser filho do 4

    no->h = big(heigthNo(no->left), heigthNo(no->right)) + 1;
    printf("\n%d\n", no->h);
    rChild->h = big(heigthNo(rChild->left), heigthNo(rChild->right)) + 1;
    printf("\n%d\n", rChild->h);

    printf("==================\n");
}

void rotLeft(Node *no){

    printf("=========================");

    printf("\nentrou no rotLeft para o %d\n", no->value);
    printf("\nno c == 2:\n");

    Node *rChild, *lChild;

    rChild = no->right;
    printf("\n%d\n", rChild->value);
    lChild = rChild->left;

    rChild->left = no;
    printf("\n%d\n", rChild->left->value);
    printf("\n%d\n", rChild->right->value);
    no->right = lChild;

    if(lChild != NULL){
        lChild->parent = no;
    }

    rChild->parent = no->parent;
    if(no->parent != NULL){
        printf("\n%d\n", rChild->parent->value);
        //atualizar o filho do 6
        no->parent->right = rChild;
    }
    
    no->parent = rChild;

    no->h = big(heigthNo(no->left), heigthNo(no->right)) + 1;
    printf("\n%d\n", no->h);
    rChild->h = big(heigthNo(rChild->left), heigthNo(rChild->right)) + 1;
    printf("\n%d\n", rChild->h);

    printf("==================\n");
}

void rotRigth(Node *no){

    printf("\nentrou no rotRigth para o %d\n", no->value);

    Node *rChild, *lChild;

    lChild = no->left;
    rChild = lChild->right;

    lChild->right = no;
    no->left = rChild;

    if(rChild != NULL){
        rChild->parent = no;
    }

    lChild->parent = no->parent;
    if(no->parent != NULL){
        no->parent->left = lChild;
    }
    no->parent = lChild;

    no->h = big(heigthNo(no->left), heigthNo(no->right)) + 1;
    lChild->h = big(heigthNo(lChild->left), heigthNo(lChild->right)) + 1;


}

int big(int lChild, int rChild){
    if(lChild > rChild){
        return lChild;
    }
    return rChild;
}

int heigthNo(Node *no){
    if(no == NULL){
        return 0;
    }
    return no->h;
}

void calcHeigth(Node *no){
    no = no;
    while(no != NULL){
        no->h = big(heigthNo(no->left), heigthNo(no->right)) + 1;
        no = no->parent;
    }
}

int fatorBalance(Node *no){
    if(no != NULL){
        return heigthNo(no->left) - heigthNo(no->right);
    }
    return 0;
}

void insertLeft(Node *lNode, int value){
    if(lNode->left == NULL){

        Node *new_node = (Node*)malloc(sizeof(Node));
        new_node->value = value;
        new_node->h = 0;
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->parent = lNode;

        lNode->left = new_node;

        printf("\nvalor: %d\n", lNode->left->value);

        lNode->left->h = big(heigthNo(lNode->left->left), heigthNo(lNode->left->right)) + 1;
        calcHeigth(lNode->left);
        balance(lNode->left);

        //printf("\nvalor: %d\n", lNode->left->value);
        //print_tree(achaRoot(lNode->left));
    }
    else{
        if(value < lNode->left->value){
            insertLeft(lNode->left, value);
        }
        else if(value > lNode->left->value){
            insertRight(lNode->left, value);
        }
        else{
            printf("não pode");
        }
    }
}

void insertRight(Node *rNode, int value){
    if(rNode->right == NULL){

        Node *new_node = (Node*)malloc(sizeof(Node));
        new_node->value = value;
        new_node->h = 0;
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->parent = rNode;

        rNode->right = new_node;

        printf("\nvalor: %d\n", rNode->right->value);

        rNode->right->h = big(heigthNo(rNode->right->left), heigthNo(rNode->right->right)) + 1;
        calcHeigth(rNode->right);
        balance(rNode->right);

        //printf("\nvalor: %d, pai: %p\n", rNode->right->value, rNode->right->parent);

        printf("\nvalor: %p\n", rNode->right);

        //print_tree(achaRoot(rNode->right));
    }
    else{
        if(value < rNode->right->value){
            insertLeft(rNode->right, value);
        }
        else if(value > rNode->right->value){
            insertRight(rNode->right, value);
        }else{
            printf("não pode");
        }
    }
}

void tree_insert(Tree *tree, int value){
    if(tree->root == NULL){
        tree->root = createNo(value);

        tree->root->h = big(heigthNo(tree->root->left), heigthNo(tree->root->right)) + 1;
        //balance(tree->root);
    }
    else{
        if(value < tree->root->value){
            insertLeft(tree->root, value);
        }
        else if(value > tree->root->value){
            printf("entrou no insRi");
            insertRight(tree->root, value);
        }
        else{
            printf("não pode");
        }
        printf("\nraiz: %p\n", tree->root);
        printf("\nvalor da raiz: %d\n", tree->root->value);
        tree->root = achaRoot(tree->root);
        printf("\nvalor da raiz: %d\n", tree->root->value);
        printf("\nraiz: %p\n", tree->root);
    }

};

Node* search(Node *root, int v){
    if(root != NULL){
        if(root->value == v){
            return root;
        }
        else{
            if(v < root->value){
                return search(root->left, v);
            }
            return search(root->right, v);
        }
    }
    return NULL;
}

void print_tree(Node *root){
    
    //printf("entrou antes do if no print\n");
    if(root != NULL){
        //printf("\nroot: %d\n", root->value);
        //printf("entrou depois do if no print\n");
        print_tree(root->left);
        printf("\nvalor: %d, pai: %p\n", root->value, root->parent);
        print_tree(root->right);
    }
}

int main(){

    int op, valor;
    Tree tree;
    tree.root = NULL;

    Node *no = (Node*)malloc(sizeof(Node));
    no->value = 0;
    no->h = 0;
    no->left = NULL;
    no->right = NULL;
    no->parent = NULL;

    do{

        system("clear||cls");

        printf("\n=============================\n");
        printf("| 0- Encerrar o Programa    |\n");
        printf("| 1- Inserir Elemento       |\n");
        printf("| 2- Imprimir Árvore        |\n");
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
            tree_insert(&tree, valor);
            printf("\nValor %d inserido com sucesso!", valor);
            getchar();
        }
        else if(op == 2){
            //printf("nó no op == 2: %p\n", tree.root);
            printf("\nImpressão da Árvore:\n\n");
            print_tree(tree.root);
            getchar();
        }
        else if(op == 3){
            printf("\nInforme o Valor a ser buscado: ");
            scanf("%d", &valor);
            no = search(tree.root, valor);
            if(no == NULL){
                printf("\nvalor do elemento informado não foi encontrado!\n");
                getchar();
            }
            else{
                printf("\nO endereço do nó encontrado é %p\n o valor do nó é: %d\n l: %p\nr: %p\npai: %p", no, no->value, no->left, no->right, no->parent);
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
};

/*
int main(int argc, char **argv)
{
    struct timespec a, b;
    unsigned int t, n;
    int i;

    Tree tree;
    tree.root = NULL;

    n = atoi(argv[1]);  
    srand(time(NULL));
    for (i = 0; i < n; i++){
        //v[i] = rand();
        tree_insert(&tree, i);
    }

    clock_gettime(CLOCK_MONOTONIC, &b);
    search(tree.root, n);
    clock_gettime(CLOCK_MONOTONIC, &a);

    t = (a.tv_sec * 1e9 + a.tv_nsec) - (b.tv_sec * 1e9 + b.tv_nsec);

    printf("%u\n", t);

    return 0;
}*/