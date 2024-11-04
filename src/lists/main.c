#include "list.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  Albero sx = creaNodo(2);
  sx->sinistro = creaNodo(7);
  sx->destro = creaNodo(4);

  Albero dx = creaNodo(9);
  dx->sinistro = creaNodo(3);
  dx->destro = creaNodo(2);

  Albero al = creaNodo(5);
  al->destro = dx;
  al->sinistro = sx;

  visitDFS(&al);
  visitSymRecDFS(&al);
  printf("\n number of leaves: %d\n", countLeaves(al));
  printf("nodes sum is : %d\n", nodesSum(al));
  printf("tree height is : %d\n", treeHeight(al));

  printf("sum of all the odd nodes is : %d\n", sumOddNodes(al));
  int retvalue = findNode(5, al);
  if (retvalue == 1)
    printf("found value! 5\n");
  else
    printf("value 5 not found...\n");
  freeTree(&al);

  return EXIT_SUCCESS;
}
