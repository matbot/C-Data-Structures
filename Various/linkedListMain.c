#include "linkedList.h"
#include <stdio.h>

int main(){
	struct LinkedList* l = linkedListCreate();
	linkedListAddFront(l, (TYPE)1);
    linkedListAddBack(l, (TYPE)2);
    linkedListAddBack(l, (TYPE)3);
    linkedListAddFront(l, (TYPE)4);
	linkedListAddFront(l, (TYPE)5);
	linkedListAddBack(l, (TYPE)6);
	linkedListPrint(l);
	printf("%i\n", linkedListFront(l));
	printf("%i\n", linkedListBack(l));
	linkedListRemoveFront(l);
	linkedListRemoveBack(l);
	linkedListPrint(l);
/* BAG */
	
      struct LinkedList* k = linkedListCreate(); 
       linkedListAdd (k, (TYPE)10);
       linkedListAdd (k, (TYPE)11);
	 linkedListAdd (k, (TYPE)13);
       linkedListAdd(k, (TYPE)14);
       linkedListRemove(k, (TYPE)11);
       linkedListPrint(k);

    struct LinkedList* it = linkedListCreate();
    struct LinkedList* jt = linkedListCreate();
    for(int i=0;i<25;i++) {
        linkedListAddFront(it,i);
        linkedListAddBack(jt,i);
    }
    for(int i=0;i<25;i++) {
        linkedListRemove(it,i);
        i++;
    }
    linkedListPrint(it);
    linkedListPrint(jt);
    linkedListDestroy(l);
    linkedListDestroy(k);
    linkedListDestroy(it);
    linkedListDestroy(jt);
	return 0;
}
