#include <stdbool.h>
#include <stdlib.h>

typedef int element;

typedef int (*func) (void *, void *);
extern func fun;

int elem_comp(void *first, void *second);
void *binary_search(void *key, void *base, size_t num_elem, size_t elem_size,
        func);
