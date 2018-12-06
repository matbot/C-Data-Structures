#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct element {
	struct element *next;
	int value;
};

struct queue {
	struct element *head;
	struct element *tail;
};

/*struct queue *q;*/

struct queue* queueCreate(void) 
{
	struct queue *q;

	q = malloc(sizeof(struct queue));

	q->head = q->tail = 0;

	return q;
}

int queueIsEmpty(const struct queue *q)
{
	return (q->head == 0);
}

/*push a new value to queue*/
void enqueue(struct queue *q, int value)
{
	struct element *e;

	e = malloc(sizeof(struct element));
	assert(e);

	e->value = value;

	e->next = 0;

	/*check for empty queue*/
	if(q->head == 0) {
		q->head = e;
	}
	else {
		q->tail->next = e;
	}

	q->tail = e;
}

int dequeue(struct queue *q)
{
	assert(!queueIsEmpty(q));

	int retValue;
	struct element *e;
	
	retValue = q->head->value;

	e = q->head;
	q->head = e->next;
	free(e);

	return retValue;
}

/*print contents of queue, head first*/
void queuePrint(struct queue *q)
{
	struct element *e;

	for(e = q->head; e != 0; e = e->next) {
		printf("%d ", e->value);
	}

	putchar('\n');
}

/*free the queue and all its elements*/
void queueDestroy(struct queue *q)
{
	while(!queueIsEmpty(q)) {
		dequeue(q);
	}

	free(q);
}

int main(int argc, char **argv)
{
	int i;
	struct queue *q;

	q = queueCreate();

	for(i = 0; i < 5; i++) {
		printf("enq %d\n", i);
		enqueue(q, i);
		queuePrint(q);
	}

	while(!queueIsEmpty(q)) {
		printf("deq gets %d\n", dequeue(q));
		queuePrint(q);
	}

	queueDestroy(q);

	return 0;
}
