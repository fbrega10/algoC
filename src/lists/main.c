#include "list.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {

  Pila p = makePila();
  push(6, &p);
  push(7, &p);
  push(8, &p);
  push(9, &p);
  printList(p);
  return EXIT_SUCCESS;
}
