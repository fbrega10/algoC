#ifndef __TREE_H
#define __TREE_H

typedef int element;

typedef struct treeNode {
  struct treeNode *right;
  struct treeNode *left;
  element value;
} treeNode;

typedef treeNode Tree;
Tree *buildTree(int initialValue);
treeNode *newNode(int value);
Tree *allocWithBothNodes(int nodeValue, int leftValue, int rightValue);

#endif
