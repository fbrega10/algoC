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
  else
    return 0;
}

Element rimuovi(Lista *lptr) {
  if ((*lptr) != NULL) {
    Element e = primo(*lptr);
    Lista l = (*lptr);
    (*lptr) = (*lptr)->next;
    free(l);
    return e;
  }
  return 0;
}

void printList(const Lista l) {
  if (isEmpty(l)) {
    printf("NULL \n");
  } else {
    printf(" %d --> ", l->valore);
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
 * Stack methods and interfaces
 */

int isEMptyP(Pila p) { return isEmpty(p); }

void push(Element e, Pila *p) { addNode(e, p); }

Element pop(Pila *p) { return rimuovi(p); }

// Element top(Pila *p) { return primo(*p); }

Element top(Pila *p) {
  if (isEMptyP(*p))
    return 0;
  while ((*p)->next != NULL) {
    (*p) = (*p)->next;
  }
  return (*p)->valore;
}

Pila makePila() { return makeLista(); }

/*
 * Queue methods and interfaces
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
