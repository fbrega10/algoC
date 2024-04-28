#include <stdbool.h>
#include <stdio.h>

bool binary_search(int array[], int element) {
  int a = 0;
  int b = (sizeof(array) / sizeof(int)) - 1;
  int middle = 0;

  while (a < b) {
    middle = (b + a) / 2;
    if (array[middle] == element)
      printf("element found : %d, which is the middle : %d \n", array[middle],
             element);
    return true;
    if (array[middle] > element) {
      a = middle + 1;
    } else {
      b = middle - 1;
    }
  }
  return false;
}
