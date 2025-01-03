/*
MIT License

Copyright (c) 2024 fbrega10

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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

int isLeaf(Albero al) { return (al->destro == NULL && al->sinistro == NULL); }

int countLeaves(Albero al) {
  // counting the leaves of a tree recursively
  if (al == NULL)
    return 0;
  if (isLeaf(al))
    return 1;
  return countLeaves(al->sinistro) + countLeaves(al->destro);
}

int countNodes(Albero al) {
  if (al == NULL)
    return 0;
  else {
    return 1 + countNodes(al->sinistro) + countNodes(al->destro);
  }
}

int nodesSum(Albero al) {
  if (al == NULL)
    return 0;
  else {
    return (al->inf) + nodesSum(al->sinistro) + nodesSum(al->destro);
  }
}
int max(int c, int d) {
  if (c >= d)
    return c;
  return d;
}

int treeHeight(Albero al) {
  if (al == NULL)
    return -1;
  return 1 + max(treeHeight(al->sinistro), treeHeight(al->destro));
}

int findNode(int value, Albero al) {
  if (al == NULL)
    return al == NULL;
  if (al->inf == value)
    return al->inf == value;
  if (findNode(value, al->sinistro))
    return 1;
  if (findNode(value, al->destro))
    return 1;
  return 0;
}

int sumOddNodes(Albero al) {
  if (al == NULL)
    return 0;
  if (al->inf % 2 == 1)
    return (al->inf) + sumOddNodes(al->sinistro) + sumOddNodes(al->destro);
  else
    return sumOddNodes(al->sinistro) + sumOddNodes(al->destro);
}
