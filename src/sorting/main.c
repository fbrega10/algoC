#include "sort.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  int a = 4;
  int b = 5;
  swap(&a, &b);
  printf("a = 4, b = 5 ==> swap : a = %d, b = %d\n", a, b);
  int d[] = {5, 23, 1, 4, 2, 234, 2, 3, 4};
  print_array(&d[0], 9);
  selection_sort(&d[0], 9);
  print_array(&d[0], 9);
  return EXIT_SUCCESS;
}
