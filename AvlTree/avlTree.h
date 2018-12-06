//
// Created by MatBot on 10/29/2017.
//

/****************Currently Broken********************/

#ifndef AVL_TREE_C_AVLTREE_H
#define AVL_TREE_C_AVLTREE_H

#include <stdlib.h>

typedef struct AvlNode AvlNode;

AvlNode* _newNode(int data);
int _height(AvlNode *node);
int _balanceFactor(AvlNode *node);
void _adjustHeight(AvlNode *node);
AvlNode* _rotateRight(AvlNode *node);
AvlNode* _rotateLeft(AvlNode *node);
AvlNode* _balance(AvlNode *node);

AvlNode* _getMin(AvlNode *node);
AvlNode* _getMax(AvlNode *node);

AvlNode* _removeMin(AvlNode *node);
AvlNode* _removeMax(AvlNode *node);

AvlNode* insertNode(AvlNode *node, int data);
AvlNode* containsNode(AvlNode *node, int data);
AvlNode* removeNode(AvlNode *node, int data);
void freeTree(AvlNode *node);

void inOrderPrint(AvlNode *node);
void preOrderPrint(AvlNode *node);
void postOrderPrint(AvlNode *node);

//void displayTree(AvlNode *root);

/***********************************************************/
void print2DUtil(AvlNode *root,int space);
void print2D(AvlNode *root);
#endif //AVL_TREE_C_AVLTREE_H
