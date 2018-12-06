//
// Created by MatBot on 11/4/2017.
//

#ifndef HEAP_C_HEAP_C_H
#define HEAP_C_HEAP_C_H

typedef struct Heap Heap;

Heap* newHeap(int capacity);
void heapDestroy(Heap *heap);

void heapInsert(Heap *heap, int val);
int heapExtract(Heap *heap);

void printHeap(Heap *heap);

void heapSort(int *arr, int size);
void sortHeap(Heap *h);

#endif //HEAP_C_HEAP_C_H
