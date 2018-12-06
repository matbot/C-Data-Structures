#include <stdlib.h>
#include <assert.h>
#include <stddef.h> /* for offsetof */

#include "deque.h"

#define NUM_DIRECTIONS (2)

struct deque {
	struct deque *next[NUM_DIRECTIONS];
	int value;
};

Deque *dequeCreate(void)
{
	Deque *d;

	/* malloc w offsetof to reduce the size of the head pointer */
	d = malloc(offsetof(struct deque, value));
	/* test for malloc failure */
	if(d) {
		d->next[DEQUE_FRONT] = d->next[DEQUE_BACK] = d;
	}
	return d;
}

void dequePush(Deque *d, int direction, int value)
{
	struct deque *e; /* new element */
	/* input check direction value */
	assert(direction == DEQUE_FRONT || direction == DEQUE_BACK);

	e = malloc(sizeof(struct deque));
	assert(e);

	e->next[direction] = d->next[direction];
	e->next[!direction] = d;
	e->value = value;

	d->next[direction] = e;
	e->next[direction]->next[!direction] = e; /* points next back to this */
}

int dequePop(Deque *d, int direction)
{
	struct deque *e;
	int retVal;

	assert(direction == DEQUE_FRONT || direction == DEQUE_BACK);

	e = d->next[direction];

	/* check if empty */
	if(e == d) {
		return DEQUE_EMPTY;
	}
	else {
		d->next[direction] = e->next[direction];
		e->next[direction]->next[!direction] = d;

		retVal = e->value;

		free(e);

		return retVal;
	}
}

int dequeIsEmpty(const Deque *d)
{
	return d->next[DEQUE_FRONT] == d;
}

void dequeDestroy(Deque *d)
{
	while(!dequeIsEmpty(d)) {
		dequePop(d, DEQUE_FRONT);
	}
	free(d);
}






















