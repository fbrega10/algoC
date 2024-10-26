#include "list.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Nodes - linked lists api
 */

node *newNode() { return (node *)malloc(sizeof(node)); }

node *newNodeValue(int data) {
  node *this = (node *)malloc(sizeof(node));
  if (this == NULL) {
    printf("Error allcocating memory\n");
    return NULL;
  }
  this->data = data;
  return this;
}

int getRandomNumber() { return rand() % 1000; }

void add(int data, node *node) { node->next = newNodeValue(data); }

void removeNode(node *node) {
  if (node == NULL || node->next == NULL) {
    printf("nothing to be removed here");
    return;
  }
  free(node->next);
  node->next = NULL;
}

void printListRecursively(node *head) {
  // recursive approach
  if (head == NULL) {
    printf("NULL\n");
  } else {
    printf("%d -> ", head->data);
    printListRecursively(head->next);
  }
}

void printList(node *head) {
  // iterative approach
  while (head != NULL) {
    printf("%d -> ", head->data);
    head = head->next;
  }
  printf("NULL\n");
}

void flushListRec(node *head) {
  // freeing the allocated heap memory recursively
  if (head != NULL) {
    node *p = head;
    head = head->next;
    free(p);
    flushListRec(head);
  }
}

void flushList(node *head) {
  while (head != NULL) {
    node *p = head;
    head = head->next;
    free(p);
  }
}

node *buildRandomList(int size) {
  // builds a random list of n elements
  // use srand function in main to generate effectively random sequences
  node *head = newNode();
  head->data = rand() % getRandomNumber();
  node *tail = head;
  for (int i = 0; i < size - 1; i++) {
    node *p = newNode();
    p->data = getRandomNumber();
    tail->next = p;
    tail = tail->next;
  }
  return head;
}

int countNodes(node *head) {
  // counting n° of nodes
  if (head == NULL)
    return 0;
  else {
    return 1 + countNodes(head->next);
  }
}

node *removeHead(node *head) {
  if (head == NULL) {
    printf("could not remove the head, empty list\n");
  } else {
    node *p = head;
    head = head->next;
    free(p);
  }
  return head;
}

void removeTail(node *head) {
  while (head->next->next != NULL) {
    head = head->next;
  }
  node *p = head->next;
  head->next = NULL;
  free(p);
}

node *merge(node *list1, node *list2) {
  // merging the nodes of both lists
  node *p, *head = NULL, *tail = NULL;
  while (list1 != NULL && list2 != NULL) {

    if (list1->data <= list2->data) {
      p = list1;
      list1 = list1->next;
    } else {
      p = list2;
      list2 = list2->next;
    }
    if (head == NULL) {
      head = p;
      tail = head;
    } else {
      tail->next = p;
      tail = tail->next;
    }
  }

  if (list1 != NULL) {
    tail->next = list1;
  }
  if (list2 != NULL) {
    tail->next = list2;
  }

  return head;
}

/*
 * Stack api's
 *
 */

stack *newStack() { return (stack *)malloc(sizeof(stack)); }

int emptyS(stack *s) { return (s != NULL); }

void push(int data, stack *stack) {
  // pushing an element on the TOS (top of stack)
  add(data, stack);
}

void pop(stack *stack) {
  // from the current stack we pop off and remove the last element
  // LIFO policy
  if (stack == NULL) {
    printf("nothing to free, already empty\n");
  }
  if (stack->next == NULL) {
    stack = NULL;
    return;
  }
  while (stack->next->next != NULL) {
  }
  free(stack->next);
  stack->next = NULL;
}

int topOfStack(stack *stack) {
  if (emptyS(stack)) {
    printf("empty stack\n");
    return 0;
  }
  node *head = stack;
  while (head->next != NULL) {
    head = head->next;
  }
  return head->data;
}

void printStack(stack *head) { printListRecursively(head); }

/*
 * Queue api
 *
 */

queue *newQueue() { return newNode(); }

void enqueue(queue *head, int data) { add(data, head); }

int dequeue(queue *head) {
  if (head == NULL) {
    printf("empty queue\n");
    return -1;
  }
  int currentData = head->data;
  node *tofree = head;
  head = head->next;
  free(tofree);
  return currentData;
}

void printQueue(queue *head) { printListRecursively(head); }
