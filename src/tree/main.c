#include "tree.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {
  Tree *tree = allocWithBothNodes(5, 7, 8);
  printTree(tree);
  freeTree(tree);
  return EXIT_SUCCESS;
}
