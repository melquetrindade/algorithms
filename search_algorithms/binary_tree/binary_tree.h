typedef struct node{
    int value;
    struct node *left;
    struct node *right;
}Node;

typedef struct{
    Node *root;
}Tree;

void insertLeft(Node *, int);
void insertRight(Node *, int);
void tree_insert(Tree *, int);
Node* search(Node *, int);
void print_tree(Node *);
int min(Node *);
int max(Node *);
