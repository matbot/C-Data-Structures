//
// Created by MatBot on 10/30/2017.
//

/****************Currently Broken********************/

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "avlTree.h"

struct AvlNode
{
    int data;
    int height;

    AvlNode *leftChild;
    AvlNode *rightChild;
};

AvlNode* _newNode(int data)
{
    AvlNode *newNode = (AvlNode *)malloc(sizeof(AvlNode));
    assert(newNode);
    newNode->data = data;
    newNode->height = 0;
    newNode->leftChild = newNode->rightChild = NULL;
}

int _height(AvlNode *node)
{
    if(node==NULL)
        return -1;
    return node->height;
}

int _balanceFactor(AvlNode *node)
{
    return _height(node->rightChild) - _height(node->leftChild);
}

void _adjustHeight(AvlNode *node)
{
    int leftHeight = _height(node->leftChild);
    int rightHeight = _height(node->rightChild);

    node->height = (leftHeight>rightHeight?leftHeight:rightHeight)+1;
}

AvlNode* _rotateRight(AvlNode *node)
{
    AvlNode *pivotNode = node->leftChild;
    node->leftChild =  pivotNode->rightChild;
    pivotNode->rightChild = node;

    _adjustHeight(node);
    _adjustHeight(pivotNode);

    return pivotNode;
}

AvlNode* _rotateLeft(AvlNode *node)
{
    AvlNode *pivotNode = node->rightChild;
    node->rightChild =  pivotNode->leftChild;
    pivotNode->leftChild = node;

    _adjustHeight(node);
    _adjustHeight(pivotNode);

    return pivotNode;
}

AvlNode* _balance(AvlNode *node)
{
    _adjustHeight(node);

    if(_balanceFactor(node)>1) {
        if(_balanceFactor(node->rightChild)<0) { /* Call double left rotation */
            printf("double left rotate\n");
            node->rightChild = _rotateRight(node->rightChild);
        }
        return _rotateLeft(node);
    }
    if(_balanceFactor(node)<-1) {
        if(_balanceFactor(node->leftChild)>0) {  /* Call double right rotation */
            printf("double right rotate\n");
            node->leftChild = _rotateLeft(node->leftChild);
        }
       return _rotateRight(node);
    }
    _adjustHeight(node);

    return node;
}

AvlNode* _getMin(AvlNode *node)
{
    if(node->leftChild==NULL) {
        return node;
    }
    else {
        return _getMin(node->leftChild);
    }
}

AvlNode* _getMax(AvlNode *node)
{
    if(node->rightChild==NULL) {
        return node;
    }
    else {
        return _getMax(node->rightChild);
    }
}

AvlNode* _removeMin(AvlNode *node)
{
    if(node->leftChild==NULL) {
        AvlNode *tempNode = node->rightChild;
        free(node);
        return tempNode;
    }
    node->leftChild = _removeMin(node->leftChild);
    return _balance(node);
}

AvlNode* _removeMax(AvlNode *node)
{
    if(node->rightChild==NULL) {
        AvlNode *tempNode = node->leftChild;
        free(node);
        return tempNode;
    }
    node->rightChild = _removeMin(node->rightChild);
    return _balance(node);
}



AvlNode* insertNode(AvlNode *node, int newData)
{

    if(node==NULL) {
        return _newNode(newData);
    }
    if(newData<node->data) {
        node->leftChild = insertNode(node->leftChild,newData);
    }
    else if(newData>node->data) {
        node->rightChild = insertNode(node->rightChild,newData);
    }
    /*AvlNode *retNode = _balance(node);
    printf("RetVal2:%d%d%d\n",retNode->data,retNode->rightChild->data,retNode->leftChild->data);
    return retNode;*/
    return _balance(node);
}

/*****************returns NULL if value not found, returns pointer to node if found***********/
AvlNode* containsNode(AvlNode *node, int searchData)
{
    AvlNode *searchNode = node;

    while(searchNode!=NULL) {
        if(searchData==searchNode->data) {
            return searchNode;
        }
        else if(searchData<searchNode->data) {
            searchNode = searchNode->leftChild;
        }
        else {
            searchNode = searchNode->rightChild;
        }
    }
    return NULL;
}

AvlNode* removeNode(AvlNode *node, int searchData)
{
    AvlNode *removalNode = containsNode(node, searchData);
    if(removalNode==NULL) {
        return NULL;
    }
    AvlNode *leftNode = removalNode->leftChild;
    AvlNode *rightNode = removalNode->rightChild;
    free(removalNode);

    if(rightNode==NULL) {
        return leftNode;
    }
    AvlNode *rightMin = _getMin(rightNode);
    rightMin->rightChild = _removeMin(rightNode);
    rightMin->leftChild = leftNode;

    return _balance(rightMin);
}

void freeTree(AvlNode *node)
{
    while(_removeMin(node));
}


void inOrderPrint(AvlNode *node)
{
    if(node!=NULL) {
        inOrderPrint(node->leftChild);
//        printf("%d(h:%d)(l:%d)(r:%d)[bf:%d], ",node->data,node->height, _height(node->leftChild), _height(node->rightChild), _balanceFactor(node));
        printf("%d, ",node->data);
        inOrderPrint(node->rightChild);
    }
}

void preOrderPrint(AvlNode *node)
{
    if(node!=NULL) {
        printf("%d, ",node->data);
        preOrderPrint(node->leftChild);
        preOrderPrint(node->rightChild);
    }
}

void postOrderPrint(AvlNode *node)
{
    if(node!=NULL) {
        postOrderPrint(node->leftChild);
        postOrderPrint(node->rightChild);
        printf("%d, ",node->data);

    }
}

/*void displayTree(AvlNode *root)
{

}*/


/***********************************************************/

#define COUNT 10
void print2DUtil(AvlNode *root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->rightChild, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", root->data);

    // Process left child
    print2DUtil(root->leftChild, space);
}

// Wrapper over print2DUtil()
void print2D(AvlNode *root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}

