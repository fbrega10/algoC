#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEFAULT 10

int main() {

  srand(time(NULL));
  node *head = buildRandomList(10);
  printList(head);
  printf("Number of nodes : %d\n", countNodes(head));
  head = removeHead(head);
  removeTail(head);
  printf("new list : \n");
  printList(head);
  flushList(head);

  node * list1 = buildRandomList(5);
  node * list2 = buildRandomList(5);
  printf("\nprinting list 1 : \n");
  printList(list1);
  printf("\nprinting list 2 : \n");
  printList(list2);

  node * list3 = merge(list1, list2);
  printf("\nprinting list 3 : \n");
  printList(list3);
  flushList(list3);
  return EXIT_SUCCESS;
}
