

/****************Currently Broken********************/
// test contains.
// test remove.
// test get/remove min/max.
// test freeTree.
// fix init and insert so you don't have to 'tree = insertNode()' every time. Maybe pass the tree by reference?
// adapt data variable to accept void * data. -user defined compare, print, and destroy functions.

#include <stdio.h>
#include "avlTree.h"

int main()
{
    AvlNode *tree = _newNode(3);
    tree = insertNode(tree, 2);
    tree = insertNode(tree, 1);
    tree = insertNode(tree, 5);
    tree = insertNode(tree, 4);
    tree = insertNode(tree, 0);
    tree = insertNode(tree, 99);
    tree = insertNode(tree, -1);
    tree = insertNode(tree, 4004);
    tree = insertNode(tree, 15);
    tree = insertNode(tree, -3);
    tree = insertNode(tree, -2);
    tree = insertNode(tree, -200);
    tree = insertNode(tree, 8);
    tree = insertNode(tree, 7);













    inOrderPrint(tree);
    printf("\n\n");
    preOrderPrint(tree);
    printf("\n\n");
    postOrderPrint(tree);
    printf("\n\n");


    print2D(tree);

    return 0;
}