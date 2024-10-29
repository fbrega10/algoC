
typedef int Elemento;

typedef struct Nodo {
  Elemento inf;
  struct Nodo *sinistro;
  struct Nodo *destro;
} Nodo;

typedef Nodo *Albero;
Albero creaNodo(Elemento);

typedef Nodo *Element;

void visitDFS(Albero *al);
void visitBFS(Albero *al);
void visitSymRecDFS(Albero *al);
void visitPreRecDFS(Albero *al);
void visitPostRecDFS(Albero *al);
void freeTree(Albero *al);
int isLeaf(Albero al);
int countLeaves(Albero al);
int countNodes(Albero al);
int nodesSum(Albero al);
int max(int, int);
int treeHeight(Albero al);

typedef struct NodeLista {
  struct NodeLista *next;
  Element valore;
} NodeLista;

typedef NodeLista *Lista;

Lista makeLista();

Lista newNode();

int isEmpty(Lista l);

Element primo(Lista l);

void addNode(Element e, Lista *l);

Element rimuovi(Lista *l);

void printList(const Lista l);

void freeList(Lista l);

/*
 * Stack implementation
 */

typedef Lista Pila;

int isEMptyP(Pila);
void push(Element, Pila *);
Element pop(Pila *);
Element top(Pila *);
Pila makePila();

/*
 * Queue implementation
 */

typedef struct coda {
  Lista primo;
  Lista ultimo;
} coda;

typedef struct coda Coda;

int isEmptyC(Coda);
void enqueue(Element, Coda *);
Element dequeue(Coda *);
Element first(Coda);
Coda makeCoda();
