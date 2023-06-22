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

void balance(Node *no){
    no = no->parent;
    while(no != NULL){
        if((fatorBalance(no) > 1) || (fatorBalance(no < -1))){

        }
        no = no->parent;
    }
}

Node* rotLeft(Node *no){
    Node *rChild, *lChild;

    rChild = no->right;
    lChild = no->right;

    rChild->left = no;
    no->right = lChild;

    no->h = big(heigthNo(no->left), heigthNo(no->right)) + 1;
    rChild->h = big(heigthNo(rChild->left), heigthNo(rChild->right)) + 1;

    return rChild;
}

Node* rotLeft(Node *no){
    Node *rChild, *lChild;

    rChild = no->right;
    lChild = no->right;

    rChild->left = no;
    no->right = lChild;

    no->h = big(heigthNo(no->left), heigthNo(no->right)) + 1;
    rChild->h = big(heigthNo(rChild->left), heigthNo(rChild->right)) + 1;

    return rChild;
}

void insertLeft(Node *lNode, int value){
    if(lNode->left == NULL){
        lNode->left = createNo(value);
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
        rNode->right = createNo(value);
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
        tree->root = createNo(value);
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
}