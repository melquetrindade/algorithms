typedef struct node{
    int value, h;
    struct node *left;
    struct node *right;
    struct node *parent;
}Node;

typedef struct{
    Node *root;
}Tree;

Node* createNo(int);
Node* achaRoot(Node *);
int caso(Node *);
void balance(Node *);
void rotLeft(Node *);
void rotRigth(Node *);
int big(int, int);
int heigthNo(Node *);
void calcHeigth(Node *);
int fatorBalance(Node *);
void insertLeft(Node *, int);
void insertRight(Node *, int);
void tree_insert(Tree *, int);
Node* search(Node *, int);
void print_tree(Node *);
void rotLeft2(Node *);
void rotRigth2(Node *);