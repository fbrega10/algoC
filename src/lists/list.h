
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

void removeNext(Lista l);

void printList(const Lista l);

void freeList(Lista l);
