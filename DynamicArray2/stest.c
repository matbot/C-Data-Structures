//
// Created by MatBot on 11/11/2017.
//

#include <stdio.h>
#include "dynamicArray.h"

int main()
{
    int compare(void *a, void *b) {
        if(*(int*)a<*(int*)b) return -1;
        else if(*(int*)a>*(int*)b) return 1;
        else return 0;
    }

    DynamicArray *m = dyNew(10);

    /**********add test***************/
    int n = 5;
    dyHeapAdd(m,&n,compare);
    int o = 7;
    dyHeapAdd(m,&o,compare);
    int l = 2;
    dyHeapAdd(m,&l,compare);




    /*****************remove test**********/
    printf("%d\n", *(int*)dyHeapGetMin(m));
    dyHeapRemoveMin(m,compare);
    printf("%d\n", *(int*)dyHeapGetMin(m));


    dyDelete(m);
}