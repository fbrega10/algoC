#include "sort.h"
#include <stdlib.h>

void selection_sort(element *array, size_t size) {
  int min;
  element *start = array;
  element *secondIndex = array + 1;
  element *end = array + size;
}

void swap(void *pt1, void *pt2, size_t size) {
  if (*((element *)pt1) == *((element *)pt2))
    return;
  element tmp = *((element *)pt1);
  *((element *)pt1) = *((element *)pt2);
  *((element *)pt2) = tmp;
}
