#include <stdlib.h>

typedef struct list {
  int value;
  struct list *next;
} list;

list *createList(int value);
void addNode(list **ptr, int value);
list *newNode();

int main(int argc, char *argv[]) { return EXIT_SUCCESS; }

list *createList(int value) {
  list *ptr = (list *)malloc(sizeof(list));
  if (ptr != NULL) {
    ptr->value = value;
    ptr->next = NULL;
  }
  return ptr;
}

list *newNode() { return (list *)malloc(sizeof(list)); }

void addNode(list **ptr, int value) {
  list *node = newNode();
  node->value = value;
  *ptr->next = node;
}
