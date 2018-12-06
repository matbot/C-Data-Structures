#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct element {
	struct element *next;
	int value;
};

typedef struct element *Stack;	/*could make a struct with one element, but this is easier.*/

#define STACK_EMPTY (0)

int stackIsEmpty(const Stack *s)
{
	return (*s == 0);
}

void stackPush(Stack *s, int value)
{
	struct element *e;

	e = malloc(sizeof(struct element));
	assert(e);

	e->value = value;
	e->next = *s;
	*s = e;
}

int stackPop(Stack *s)
{
	int retVal;
	struct element *e;

	assert(!stackIsEmpty(s));

	retVal = (*s)->value;

	e = *s;
	*s = e->next;
	free(e);

	return retVal;
}

/*print stack on a single line*/
void stackPrint(const Stack *s)
{
	struct element *e;

	for(e = *s; e != 0; e = e->next) {
		printf("%d ", e->value);
	}

	putchar('\n');
}

int main(int argc, char **argv)
{
	int i;
	Stack s;

	s = 0;


	for(i = 0; i < 5; i++) {
		printf("push %d\n", i);
		stackPush(&s, i);
		stackPrint(&s);
	}
	
	while(!stackIsEmpty(&s)) {
		printf("pop gets %d\n", stackPop(&s));
		stackPrint(&s);
	}

	return 0;
}
