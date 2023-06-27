typedef struct hash{
    struct node** t;
    int m;
    int n;
}Hash;

typedef struct node{
    int value;
    struct node* next;
}Node;

Hash* newTable(int );
void deleteNo(Node *);
void deleteTable(Hash*);
int hashing(int, int);
double fatorCarga(int, int);
void insertNo(Node *, Node *);
void insertTable(Hash*, int);
void rehashing(Hash *, int);
void printTable(Hash *);
void printLista(Node *);
int searchTable(Hash *, int);
int searchList(Node *, int);
void rehashInsert(Hash *, Node*);