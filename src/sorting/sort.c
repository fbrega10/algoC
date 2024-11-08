#include "sort.h"
#include <stdio.h>
#include <stdlib.h>

void selection_sort(element *array, size_t size) {
  int min;
  for (int i = 0; i < size - 1; i++) {
    min = i;
    for (int j = min + 1; j < size; j++) {
      if (*(array + j) < *(array + min))
        min = j;
    }
    swap(array + i, array + min);
  }
}

void swap(void *pt1, void *pt2) {
  if (*((element *)pt1) == *((element *)pt2))
    return;
  element tmp = *((element *)pt1);
  *((element *)pt1) = *((element *)pt2);
  *((element *)pt2) = tmp;
}

void print_array(element *array, size_t size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", *(array + i));
  }
  printf("\n");
}
