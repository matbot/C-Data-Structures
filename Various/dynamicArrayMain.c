#include "dynArray.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int main()
{
	DynArr* a = newDynArr(100);
	srand(0);
	for(int i = 0;i<250;i++) {
		addDynArr(a,rand());
	}
	printf("Size = %i\n",sizeDynArr(a));
	printf("Get = %i\n",getDynArr(a,10));
	printf("Get = %i\n",getDynArr(a,0));
	printf("Get = %i\n",getDynArr(a,249));

	putDynArr(a,0,0);
	printf("Get = %i\n",getDynArr(a,0));
	printf("Get = %i\n",getDynArr(a,10));

	swapDynArr(a,0,10);
	printf("Get = %i\n",getDynArr(a,0));
	printf("Get = %i\n",getDynArr(a,10));

	removeAtDynArr(a,0);
	printf("Get = %i\n",getDynArr(a,9));

	removeDynArr(a,0);
	printf("Contains 0 = %i\n",containsDynArr(a,0));



	deleteDynArr(a);
	return 0;
}
