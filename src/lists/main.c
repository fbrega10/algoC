#include "list.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {

  Lista l = makeLista();
  addNode(5, &l);
  addNode(7, &l);
  printList(l);
  freeList(l);
  return EXIT_SUCCESS;
}
