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

node * merge(node * list1, node * list2){
	//merging the nodes of both lists
	node * p, *head = NULL, * tail = NULL;
	while (list1 != NULL && list2 != NULL){

		if (list1 -> data <= list2 -> data){
			p = list1;
			list1 = list1 -> next;
		}
		else {
			p = list2;
			list2 = list2 -> next;
		}
		if (head == NULL){
			head = p;
			tail = head;
		}
		else {
			tail -> next = p;
			tail = tail -> next;
		}

	}

	if (list1 != NULL){
		tail -> next = list1;
	}
	if (list2 != NULL){
		tail -> next = list2;
	}

	return head;
}
