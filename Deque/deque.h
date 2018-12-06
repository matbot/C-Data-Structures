#define DEQUE_FRONT (0)
#define DEQUE_BACK (1)
#define DEQUE_EMPTY (-1) /* returned by pop if deque is empty */

typedef struct deque Deque;

/* return a new, empty deque */
Deque *dequeCreate(void);

/* push a new value, onto a specific side of a deque */
void dequePush(Deque *d, int direction, int value);

/* pop and return first value on specific side of deque */
/* returns DEQUE_EMPTY if deque is empty */
int dequePop(Deque *d, int direction);

/* returns 1 if empty, 0 otherwise */
int dequeIsEmpty(const Deque *d);

/* free the deque */
void dequeDestroy(Deque *d);
