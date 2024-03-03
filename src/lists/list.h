#ifndef __LIST_H
#define __LIST_H

typedef struct node{
	int data;
	struct node * next;
}node;


node * newNode();
void printListRecursively(node * head);
void printList(node * head);
int getRandomNumber();
void flushListRec(node * head);
void flushList(node * head);
node * buildRandomList(int size);
int countNodes(node * head);
node * removeHead(node * head);
void removeTail(node * head);


#endif
