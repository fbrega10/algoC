#include "sort.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  int a = 4;
  int b = 5;
  swap(&a, &b, sizeof(int));
  printf("a = 4, b = 5 ==> swap : a = %d, b = %d\n", a, b);
  return EXIT_SUCCESS;
}
