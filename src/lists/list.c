#include "list.h"
#include <stdio.h>
#include <stdlib.h>



node * newNode(){
	return (node *) malloc(sizeof(node));
}

int getRandomNumber(){
	return rand() % 1000;
}

void printListRecursively(node * head){
	//recursive approach
	if (head == NULL) {
		printf("NULL\n");
	}else{
		printf("%d -> ", head -> data);
		printListRecursively(head -> next);
	}
}

void printList(node * head){
	//iterative approach
	while (head != NULL){
		printf("%d -> ", head -> data);
		head = head -> next;
	}
	printf("NULL\n");
}

void flushListRec(node * head){
	//freeing the allocated heap memory recursively
	if (head != NULL){
		node * p = head;
		head = head -> next;
		free(p);
		flushListRec(head);
	}
}

void flushList(node * head){
	while (head != NULL){
		node * p = head;
		head = head -> next;
		free(p);
	}
}

node * buildRandomList(int size){
	//builds a random list of n elements
	//use srand function in main to generate effectively random sequences
	node * head = newNode();
	head -> data = rand() % getRandomNumber();
	node * tail = head;
	for (int i = 0; i < size - 1; i++){
		node * p = newNode();
		p -> data = getRandomNumber();
		tail -> next = p;
		tail = tail -> next;
	}
	return head;
}


int countNodes(node * head){
	//counting n° of nodes
	if (head == NULL) return 0;
	else{
		return 1 + countNodes(head -> next);
	}
}

node * removeHead(node * head){
	if (head == NULL){
		printf("could not remove the head, empty list\n");
	}else{
		node * p = head;
		head = head -> next;
		free(p);
	}
	return head;
}

void removeTail(node * head){
	while (head -> next -> next != NULL){
		head = head -> next;
	}
	node * p = head -> next;
	head -> next = NULL;
	free(p);
}
