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

void removeNext(Lista l) {
  // if ((*l) != NULL){}
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
