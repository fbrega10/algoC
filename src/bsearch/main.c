#include <stdio.h>
#include <stdlib.h>
#include "bsearch.h"
#include "assert.h"


int main() {
  int array[] = {1, 23, 25, 43, 199};
  int element = 43;
  size_t size = sizeof(array) / sizeof(array[0]);
  void * result = binary_search((void*) &element, (void*) &array[0], size, sizeof(array[0]), elem_comp);
  assert(result != NULL);
  printf("found element : %d\n",*((int *)result));
  int not_found = 2;
  result = binary_search((void*) &not_found, (void*) &array[0], size, sizeof(array[0]), elem_comp); 
  assert(result == NULL);
  return EXIT_SUCCESS;
}

