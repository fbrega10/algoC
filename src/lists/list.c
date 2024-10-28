#include "list.h"
#include <stdio.h>
#include <stdlib.h>

Lista makeLista() { return NULL; }

Lista newNode() { return (Lista)malloc(sizeof(NodeLista)); }

int isEmpty(Lista l) { return l == NULL; }

void addNode(Element e, Lista *l) {
  // allocate list if null and set value
  Lista l1 = newNode();

  if (l1 != NULL) {
    l1->valore = e;
    l1->next = (*l);
    (*l) = l1;
  }
}

Element primo(Lista l) {
  if (l != NULL)
    return l->valore;
  return NULL;
}

Element rimuovi(Lista *lptr) {
  if ((*lptr) != NULL) {
    Element e = primo(*lptr);
    Lista l = (*lptr);
    (*lptr) = (*lptr)->next;
    free(l);
    return e;
  }
  return NULL;
}

void printList(const Lista l) {
  if (isEmpty(l)) {
    printf("NULL \n");
  } else {
    printf(" %p --> ", l->valore);
    printList(l->next);
  }
}

void freeList(Lista l) {
  if (l == NULL)
    return;
  else {
    Lista tmp = l->next;
    free(l);
    freeList(tmp);
  }
}

/*
 * Stack implementation
 */

int isEMptyP(Pila p) { return isEmpty(p); }

void push(Element e, Pila *p) { addNode(e, p); }

Element pop(Pila *p) { return rimuovi(p); }

// Element top(Pila *p) { return primo(*p); }

Element top(Pila *p) {
  if (isEMptyP(*p))
    return NULL;
  while ((*p)->next != NULL) {
    (*p) = (*p)->next;
  }
  return (*p)->valore;
}

Pila makePila() { return makeLista(); }

/*
 * Queue implementation
 */

int isEmptyC(Coda c) { return isEmpty(c.primo); }

void enqueue(Element e, Coda *c) {
  Lista l = NULL;
  addNode(e, &l);
  if (isEmptyC(*c)) {
    (*c).primo = l;
    (*c).ultimo = l;
  } else {
    // update last pointer to l
    (*c).ultimo->next = l;
    (*c).ultimo = l;
  }
}

Element dequeue(Coda *c) { return rimuovi(&((*c).primo)); }

Element first(Coda c) { return primo(c.primo); }

Coda makeCoda() {
  Coda c;
  c.primo = c.ultimo = NULL;
  return c;
}

Albero creaNodo(Elemento e) {
  Albero al;
  al = (Albero)malloc(sizeof(Nodo));
  al->destro = al->sinistro = NULL;
  al->inf = e;
  return al;
}

void visitDFS(Albero *al) {
  Pila p = makePila();
  push((*al), &p);
  while (!isEMptyP(p)) {
    Element e = pop(&p);
    printf("%d\n", e->inf);
    if ((e->sinistro) != NULL)
      push(e->sinistro, &p);
    if ((e->destro) != NULL)
      push(e->destro, &p);
  }
  printf("\n");
}

void visitBFS(Albero *al) {
  Coda p = makeCoda();
  enqueue((*al), &p);
  while (!isEmptyC(p)) {
    Element e = dequeue(&p);
    printf("%d\n", e->inf);
    if ((e->sinistro) != NULL)
      enqueue(e->sinistro, &p);
    if ((e->destro) != NULL)
      enqueue(e->destro, &p);
  }
  printf("\n");
}

void visitSymRecDFS(Albero *al) {
  // asymmetric recursive tree visit
  if ((*al) == NULL)
    return;
  else {
    visitSymRecDFS(&(*al)->sinistro);
    printf("%d\n", (*al)->inf);
    visitSymRecDFS(&(*al)->destro);
  }
}

void visitPreRecDFS(Albero *al) {
  // preorder recursive tree visit
  if ((*al) == NULL)
    return;
  else {
    printf("%d\n", (*al)->inf);
    visitPreRecDFS(&(*al)->sinistro);
    visitPreRecDFS(&(*al)->destro);
  }
}

void visitPostRecDFS(Albero *al) {
  // postorder recursive tree visit
  if ((*al) == NULL)
    return;
  else {
    visitPostRecDFS(&(*al)->sinistro);
    visitPostRecDFS(&(*al)->destro);
    printf("%d\n", (*al)->inf);
  }
}

void freeTree(Albero *al) {
  // freeing a tree recursively
  if ((*al) == NULL)
    return;
  else {
    freeTree(&(*al)->sinistro);
    freeTree(&(*al)->destro);
    free(*al);
  }
}
