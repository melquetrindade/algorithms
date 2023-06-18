#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int value;
    struct node *left;
    struct node *right;
}Node;

typedef struct{
    Node *root;
}Tree;

void insertLeft(Node *lNode, int value){
    if(lNode->left == NULL){
        Node *new_node = (Node*)malloc(sizeof(Node));
        new_node->value = value;
        new_node->left = NULL;
        new_node->right = NULL;

        lNode->left = new_node;
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
        new_node->left = NULL;
        new_node->right = NULL;

        rNode->right = new_node;
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

void tree_insert(Tree *tree, int value){
    if(tree->root == NULL){
        Node *new_node = (Node*)malloc(sizeof(Node));
        new_node->value = value;
        new_node->left = NULL;
        new_node->right = NULL;

        tree->root = new_node;
    }
    else{
        if(value < tree->root->value){
            insertLeft(tree->root, value);
        }
        if(value > tree->root->value){
            insertRight(tree->root, value);
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

int min(Node *root){
    if(root->left == NULL){
        return root->value;
    }
    return min(root->left);
}

int max(Node *root){
    if(root->right == NULL){
        return root->value;
    }
    return max(root->right);
}

int main(){

    int op, valor;
    Tree tree;
    tree.root = NULL;

    Node *no = (Node*)malloc(sizeof(Node));
    no->value = 0;
    no->left = NULL;
    no->right = NULL;

    do{

        system("clear||cls");

        printf("\n=============================\n");
        printf("| 0- Encerrar o Programa    |\n");
        printf("| 1- Inserir Elemento       |\n");
        printf("| 2- Imprimir Árvore        |\n");
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
            tree_insert(&tree, valor);
            printf("\nValor %d inserido com sucesso!", valor);
            getchar();
        }
        else if(op == 2){
            printf("\nImpressão da Árvore:\n\n");
            print_tree(tree.root);
            getchar();
        }
        else if(op == 3){
            printf("\n o menor valor da árvore é: %d", min(tree.root));
            getchar();
        }
        else if(op == 4){
            printf("\n o maior valor da árvore é: %d", max(tree.root));
            getchar();
        }
        else if(op == 5){
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