#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

typedef int element;

Tree *buildTree(int initialValue) {
  Tree *this = (Tree *)malloc(sizeof(treeNode));
  if (this != NULL) {
    this->value = initialValue;
  }
  return this;
}

treeNode *newNode(int value) {
  treeNode *node = (treeNode *)malloc(sizeof(treeNode));
  if (node != NULL) {
    node->value = value;
  }
  return node;
}

Tree *allocWithBothNodes(int nodeValue, int leftValue, int rightValue) {
  Tree *this = buildTree(nodeValue);
  if (this != NULL) {
    this->left = newNode(leftValue);
    this->right = newNode(rightValue);
  }
  return this;
}

