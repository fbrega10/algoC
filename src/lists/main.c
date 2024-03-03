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
  return EXIT_SUCCESS;
}
