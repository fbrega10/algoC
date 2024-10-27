
typedef int Element;

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
