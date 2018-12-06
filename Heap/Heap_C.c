//
// Created by MatBot on 11/4/2017.
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "Heap_C.h"

#define parent(n) (((n)-1)/2)
#define leftChild(n) (((n)*2)+1)
#define rightChild(n) (((n)*2)+2)

struct Heap
{
    int *treeArray;
    int size;
    int capacity;
};

void _heapInit(Heap *h, int capacity)
{
    assert(capacity);
    assert(h);
    h->treeArray = (int*)malloc(sizeof(int)*capacity);
    assert(h->treeArray);
    h->size = 0;
    h->capacity = capacity;
}

Heap* newHeap(int capacity)
{
    Heap *h = (Heap*)malloc(sizeof(Heap));
    assert(h);
    _heapInit(h,capacity);
    return h;
}

/*************Needs more implementation after custom user def included in struct. Louden pg.244****************/
void _freeHeap(Heap *heap)
{
    if(heap->treeArray)
    {
        free(heap->treeArray); 	/* free the space on the heap */
        heap->treeArray = NULL;   	/* make it point to null */
    }
    heap->size = 0;
    heap->capacity = 0;
}
void heapDestroy(Heap *heap)
{
    _freeHeap(heap);
    free(heap);
}

void _heapResize(Heap *heap)
{
    assert(heap);

    Heap tempHeap;
    _heapInit(&tempHeap,heap->capacity*2);

    for(int i=0;i<heap->size;i++) {
        tempHeap.treeArray[i] = heap->treeArray[i];
    }
    tempHeap.size = heap->size;
//    Heap *tempHeap = newHeap(heap->capacity *2);
//    for(int i=0;i<heap->size;i++) {
//        tempHeap->treeArray[i] = heap->treeArray[i];
//        tempHeap->size++;
//    }

    _freeHeap(heap);
    *heap = tempHeap;
}

void _heapSwap(Heap *heap, int i, int j)
{
    assert(heap);
    //assert(heap->size>0);
    /*assert((i>=0) && (i<heap->size));
    assert((j>=0) && (j<heap->size));*/

    int swap = heap->treeArray[i];
    heap->treeArray[i] = heap->treeArray[j];
    heap->treeArray[j] = swap;
}

void _heapFloat(Heap *h, int pos)
{
    if(h->treeArray[pos]<h->treeArray[parent(pos)]) {
        _heapSwap(h,pos,parent(pos));
        _heapFloat(h,parent(pos));
    }
}

void _heapSink(Heap *h, int p)
{
    if(rightChild(p)<h->size && h->treeArray[rightChild(p)]<h->treeArray[leftChild(p)]) {

        if(h->treeArray[rightChild(p)]<h->treeArray[p]) {

            _heapSwap(h,p,rightChild(p));
            _heapSink(h,rightChild(p));
        }
    }
    else if(leftChild(p)<h->size) {

        if(h->treeArray[leftChild(p)] < h->treeArray[p]) {

            _heapSwap(h,p,leftChild(p));
            _heapSink(h,leftChild(p));
        }
    }
}

void heapInsert(Heap *heap, int val)
{
    printf("Inserting: %d\n",val);
    assert(heap);
    if(heap->size >= heap->capacity) {
        _heapResize(heap);
    }

    heap->treeArray[heap->size] = val;

    _heapFloat(heap,heap->size);

    heap->size++;
    printHeap(heap);
}

int heapExtract(Heap *heap)
{
    assert(heap);
    //assert(heap->size);

    _heapSwap(heap,0,heap->size-1);
    heap->size--;
    _heapSink(heap,0);

    return heap->treeArray[heap->size];
}

void printHeap(Heap *h)
{
    for(int i=0;i<h->size;i++) {
        printf("%d ",h->treeArray[i]);
    }
    printf("\n");
}

Heap* _heapify(int *arr, int size)
{
    Heap *hArr = newHeap(size);
    hArr->treeArray = arr;
    hArr->size = size;
    printHeap(hArr);

    for(int i=(size/2)-1;i>=0;i--) {
        _heapSink(hArr,i);
    }
    return hArr;
}

void heapSort(int *arr, int size)
{
    Heap *h = _heapify(arr,size);
    printHeap(h);

    while(h->size>0) {
        _heapSwap(h,0,h->size-1);
        h->size--;
        _heapSink(h,0);
        printHeap(h);
    }
    h->size = size;
    printHeap(h);
    free(h);
}
void sortHeap(Heap *heap)
{
    Heap h = *heap;
    while(h.size>0) {
        _heapSwap(&h,0,h.size-1);
        h.size--;
        _heapSink(&h,0);
        printHeap(&h);
    }
    h.size = heap->size;
    printHeap(&h);
}