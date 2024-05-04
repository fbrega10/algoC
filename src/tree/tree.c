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

void printTree(Tree *tree) {
  printf("1)          %d\n", tree->value);
  printf("2)    %d            %d\n", tree->left->value, tree->right->value);
}

void freeTree(Tree *tree) {
  free(tree->left);
  free(tree->right);
  free(tree);
}
