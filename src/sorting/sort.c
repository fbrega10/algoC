/*
MIT License

Copyright (c) 2024 fbrega10

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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

void bubble_sort(element *array, size_t size) {
    for (int i = 0; i < size - 1 ;i++){
        for (int j = 1; j < size - i + 1; j++){
            if (array[j-1] > array[j]) swap(&array[j], &array[j-1]);
        }
    }
}

void insertion_sort(element *array, size_t size){
    for (int i = 0; i < size - 1; i++){
        element x = array[i + 1];
        int j = i;
        for (; j >= 0; j--) {
            if (j >= 0 && array[j] <= x) break;
        }
        if (j < i){
            for (int t = i; t >= j+1; j--){
                swap(&array[t+1], &array[t]);
            }
            swap(&array[j + 1], &array[j + 1]);
        }
    }
}
