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

#include "bsearch.h"

int elem_comp(void *first, void *second) {
  if (*((int *)first) > *((int *)second))
    return 1;
  else if (*((int *)first) < *((int *)second))
    return -1;
  else
    return 0;
}

void *binary_search(void *key, void *base, size_t num_elem, size_t elem_size, func) {
  size_t low = 0;
  size_t high = num_elem - 1;
  size_t mid;
  element *base_ptr = base;

  while (low <= high) {
    mid = (low + high) / 2;

    if (fun(key, (void *)(&base_ptr[elem_size * mid])) < 0)
      high = mid - 1;
    else if (fun(key, (void *)(&base_ptr[elem_size * mid])) > 0)
      low = mid + 1;
    else
      return (void *)(&base_ptr[elem_size * mid]);
  }
  return NULL;
}
