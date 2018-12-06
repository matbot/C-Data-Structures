/*************************************
 * **Author: Mathew McDade
 * **Date: Sun Oct 15 15:06:12 PDT 2017
 * **CS 261 Assignment 3
 * **Desription: Implementation of a deque data structure using a circular doubly linked list.
 * Developed using the provided skeleton code.
 * *************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 */
static void init(struct CircularList* list)
{
	// FIXED: you must write this
	assert(list!=0);
	list->sentinel = (struct Link*)malloc(sizeof(struct Link));
	assert(list->sentinel!=0);

	list->sentinel->next = list->sentinel;
	list->sentinel->prev = list->sentinel;

	list->size = 0;
}

/**
 * Creates a link with the given value and NULL next and prev pointers.
 */
static struct Link* createLink(TYPE value)
{
	// FIXED: you must write this
	struct Link* newLink = (struct Link*)malloc(sizeof(struct Link));
	assert(newLink!=0);
	newLink->next = NULL;
	newLink->prev = NULL;
	newLink->value = value;

	return newLink;
}

/**
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 */
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
	// FIXED: you must write this
	assert(list!=0);
	assert(link!=0);
	struct Link* newLink = createLink(value);
	newLink->next = link->next;
	newLink->next->prev = newLink;
	newLink->prev = link;
	link->next = newLink;

	list->size++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct CircularList* list, struct Link* link)
{
	// FIXED: you must write this
	assert(list!=0);
	assert(link!=0);
	link->prev->next = link->next;
	link->next->prev = link->prev;
	free(link);
	list->size--;
}

/**
 * Allocates and initializes a list.
 */
struct CircularList* circularListCreate()
{
	struct CircularList* list = malloc(sizeof(struct CircularList));
	init(list);
	return list;
}

/**
 * Deallocates every link in the list and frees the list pointer.
 */
void circularListDestroy(struct CircularList* list)
{
	// FIXED: you must write this
	assert(list!=0);
	while(list->sentinel->next!=list->sentinel) {
		removeLink(list,list->sentinel->next);
	}
	removeLink(list,list->sentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void circularListAddFront(struct CircularList* list, TYPE value)
{
	// FIXED: you must write this
	assert(list!=0);
	addLinkAfter(list,list->sentinel,value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void circularListAddBack(struct CircularList* list, TYPE value)
{
	// FIXED: you must write this
	assert(list!=0);
	addLinkAfter(list,list->sentinel->prev,value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE circularListFront(struct CircularList* list)
{
	// FIXED: you must write this
	assert(list!=0);
	assert(!circularListIsEmpty(list));
	return list->sentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE circularListBack(struct CircularList* list)
{
	// FIXED: you must write this
	assert(list!=0);
	assert(!circularListIsEmpty(list));
	return list->sentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void circularListRemoveFront(struct CircularList* list)
{
	// FIXED: you must write this
	assert(list!=0);
	assert(!circularListIsEmpty(list));
	removeLink(list,list->sentinel->next);	
}

/**
 * Removes the link at the back of the deque.
 */
void circularListRemoveBack(struct CircularList* list)
{
	// FIXED: you must write this
	assert(list!=0);
	assert(!circularListIsEmpty(list));
	removeLink(list,list->sentinel->prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int circularListIsEmpty(struct CircularList* list)
{
	// FIXED: you must write this
	return (list->size==0);
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void circularListPrint(struct CircularList* list)
{
	// FIXED: you must write this
	assert(list!=0);
	struct Link* printLink = list->sentinel->next;
	while(printLink!=list->sentinel) {
		printf("%g\n",printLink->value);
		printLink = printLink->next;
	}
}

/**
 * Reverses the deque.
 */
void circularListReverse(struct CircularList* list)
{
	// FIXED: you must write this
	assert(list!=0);
	struct Link* tempLink = createLink(0);
	struct Link* currentLink = list->sentinel;
	do {
		tempLink->next = currentLink->next;
		tempLink->prev = currentLink->prev;
		currentLink->next = tempLink->prev;
		currentLink->prev = tempLink->next;
		currentLink = currentLink->next;
	} while(currentLink!=list->sentinel);
	free(tempLink);
}
