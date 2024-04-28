#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "bsearch.h"


int main() {
  int array[] = {1, 23, 25, 45, 199};
  int element = 43;
  if (binary_search(array, element) == true)
    printf("it is in the array\n");
  else
    printf("no it isn't in the array\n");

  return EXIT_FAILURE;
}

