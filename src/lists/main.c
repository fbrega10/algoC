#include "list.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {

  Albero al = creaNodo(5);
  al->destro = creaNodo(5);
  al->sinistro = creaNodo(6);
  visitDFS(&al);
  visitSymRecDFS(&al);
  freeTree(&al);
  return EXIT_SUCCESS;
}
