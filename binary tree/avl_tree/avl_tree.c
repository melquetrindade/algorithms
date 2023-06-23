#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node{
    int value, h;
    struct node *left;
    struct node *right;
    struct node *parent;
}Node;

typedef struct{
    Node *root;
}Tree;

Node* createNo(int value){
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->value = value;
    new_node->h = 0;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->parent = NULL;

    return new_node;
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
    no = no;
    int fBalance = 0;
    int c = 0;
    while(no != NULL){
        fBalance = fatorBalance(no);
        if(fBalance < -1 || fBalance > 1){
            c = caso(no);
            if(c == 1){
                rotRigth(no);
            }
            else if(c == 2){
                rotLeft(no);
            }
            else if(c == 3){
                printf("ainda vou fazer");
            }
            else{
                printf("ainda vou fazer");
            }
        }
        no = no->parent;
    }
}

void rotLeft(Node *no){
    Node *rChild, *lChild;

    rChild = no->right;
    lChild = rChild->left;

    rChild->left = no;
    no->right = lChild;

    rChild->parent = no->parent;
    no->parent = rChild;

    no->h = big(heigthNo(no->left), heigthNo(no->right)) + 1;
    rChild->h = big(heigthNo(rChild->left), heigthNo(rChild->right)) + 1;
}

void rotRigth(Node *no){
    Node *rChild, *lChild;

    lChild = no->left;
    rChild = lChild->right;

    lChild->right = no;
    no->left = rChild;

    lChild->parent = no->parent;
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

        lNode->left->h = big(heigthNo(lNode->left->left), heigthNo(lNode->left->right)) + 1;
        balance(lNode->left);

    }
    else{
        if(value < lNode->left->value){
            insertLeft(lNode->left, value);
        }
        if(value > lNode->left->value){
            insertRight(lNode->left, value);
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

        rNode->right->h = big(heigthNo(rNode->right->left), heigthNo(rNode->right->right)) + 1;
        balance(rNode->right);
    }
    else{
        if(value < rNode->right->value){
            insertLeft(rNode->right, value);
        }
        if(value > rNode->right->value){
            insertRight(rNode->right, value);
        }
    }
}

void tree_insert(Node *root, int value){
    if(root == NULL){
        root = createNo(value);

        root->h = big(heigthNo(root->left), heigthNo(root->right)) + 1;
        balance(root);

    }
    else{
        if(value < root->value){
            insertLeft(root, value);
        }
        if(value > root->value){
            insertRight(root, value);
        }
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
    if(root != NULL){
        print_tree(root->left);
        printf("%d ", root->value);
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
            tree_insert(tree.root, valor);
            printf("\nValor %d inserido com sucesso!", valor);
            getchar();
        }
        else if(op == 2){
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
                printf("\nO endereço do nó encontrado é %p e o valor do nó é: %d", no, no->value);
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