/*************************************
 * **Author: Mathew McDade
 * **Date: Sun Oct 15 14:54:22 PDT 2017
 * **CS 261 Assignment 3
 * **Desription: Implementation of deque and bag data structures using a doubly linked
 * list. Developed using provided skeleton code.
 * *************************************/

#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Double link
struct Link
{
	TYPE value;
	struct Link* next;
	struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	int size;
	struct Link* frontSentinel;
	struct Link* backSentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinels' next and prev should point to each other or NULL
 * as appropriate.
 */
static void init(struct LinkedList* list) {
	// FIXED: you must write this
	list->frontSentinel = (struct Link *)malloc(sizeof(struct Link));
    assert(list->frontSentinel!=0);
    list->backSentinel = (struct Link *)malloc(sizeof(struct Link));
    assert(list->backSentinel!=0);

    list->frontSentinel->next = list->backSentinel;
    list->backSentinel->prev = list->frontSentinel;

    list->size = 0;
}

/**
 * Adds a new link with the given value before the given link and
 * increments the list's size.
 */
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
	// FIXED: you must write this
    assert(list!=0);
    assert(link!=0);

    struct Link* newLink = (struct Link *)malloc(sizeof(struct Link));
    assert(newLink!=0);
    newLink->next = link;
    newLink->prev = link->prev;
    link->prev->next = newLink;
    link->prev = newLink;

    newLink->value = value;
    list->size++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct LinkedList* list, struct Link* link)
{
	// FIXED: you must write this
    assert(list!=0);
    assert(link!=0);
    assert(!linkedListIsEmpty(list));

    link->next->prev = link->prev;
    link->prev->next = link->next;
    free(link);

    list->size--;
}

/**
 * Allocates and initializes a list.
 */
struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}

/**
 * Deallocates every link in the list including the sentinels,
 * and frees the list itself.
 */
void linkedListDestroy(struct LinkedList* list)
{
	while (!linkedListIsEmpty(list))
	{
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void linkedListAddFront(struct LinkedList* list, TYPE value)
{
	// FIXED: you must write this
    assert(list!=0);
    addLinkBefore(list, list->frontSentinel->next, value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
	// FIXED: you must write this
    assert(list!=0);
    addLinkBefore(list, list->backSentinel, value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE linkedListFront(struct LinkedList* list)
{
	// FIXED: you must write this
    assert(list!=0);
    assert(!linkedListIsEmpty(list));

    return list->frontSentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE linkedListBack(struct LinkedList* list)
{
	// FIXED: you must write this
    assert(list!=0);
    assert(!linkedListIsEmpty(list));

    return list->backSentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void linkedListRemoveFront(struct LinkedList* list)
{
	// FIXED: you must write this
    assert(list!=0);
    assert(!linkedListIsEmpty(list));

    removeLink(list, list->frontSentinel->next);
}

/**
 * Removes the link at the back of the deque.
 */
void linkedListRemoveBack(struct LinkedList* list)
{
	// FIXED: you must write this
    assert(list!=0);
    assert(!linkedListIsEmpty(list));

    removeLink(list, list->backSentinel->prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int linkedListIsEmpty(struct LinkedList* list)
{
	// FIXED: you must write this
    return (list->size==0);
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void linkedListPrint(struct LinkedList* list)
{
	// FIXED: you must write this
    assert(list!=0);
    assert(!linkedListIsEmpty(list));

    //struct Link* printLink = list->frontSentinel;
    /* Implemented this combined for loop structure because it adds compactness while maintaining or even improving readability */
    for(struct Link *printLink = list->frontSentinel->next;printLink!=list->backSentinel;printLink = printLink->next) {
        printf("%d\n", printLink->value);
    }
}

/**
 * Adds a link with the given value to the bag.
 */
void linkedListAdd(struct LinkedList* list, TYPE value)
{
	// FIXED: you must write this
    assert(list!=0);
    addLinkBefore(list,list->frontSentinel->next,value);
}

/**
 * Returns 1 if a link with the value is in the bag and 0 otherwise.
 */
int linkedListContains(struct LinkedList* list, TYPE value)
{
	// FIXED: you must write this
    assert(list!=0);

    for(struct Link *checkValLink = list->frontSentinel->next;checkValLink!=list->backSentinel;checkValLink = checkValLink->next) {
        if(checkValLink->value==value) {
            return 1;
        }
    }
    return 0;
}

/**
 * Removes the first occurrence of a link with the given value.
 */
void linkedListRemove(struct LinkedList* list, TYPE value)
{
	// FIXED: you must write this
    assert(list!=0);

    for(struct Link *checkValLink = list->frontSentinel->next;checkValLink!=list->backSentinel;checkValLink = checkValLink->next) {
        if(checkValLink->value==value) {
            removeLink(list,checkValLink);
            return;
        }
    }
}
