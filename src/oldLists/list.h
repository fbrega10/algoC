#ifndef __LIST_H
#define __LIST_H

typedef int data;

typedef struct node {
  data data;
  struct node *next;
} node;

// list definition/functions
node *newNode();
node *newNodeValue(data);
void add(int, node *);
void printListRecursively(node *head);
void printList(node *head);
int getRandomNumber();
void flushListRec(node *head);
void removeNode(node *);
void flushList(node *head);
node *buildRandomList(int size);
int countNodes(node *head);
node *removeHead(node *head);
void removeTail(node *head);
node *merge(node *list1, node *list2);

// stack definition/functions
typedef node stack;
stack *newStack();
int emptyS(stack *);
void push(int, stack *);
void pop(stack *);
int topOfStack(stack *);
void printStack(stack *head);

// queue definition/implementation
typedef node queue;
queue *newQueue();
void enqueue(queue *, int);
int dequeue(queue *);
void printQueue(queue *);

#endif
