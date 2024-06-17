#include "drawTree.h"

typedef struct heap
{
	int *A;
	int heapSize;
} heap;

void printHeap(heap h);

int parent(int i);
int left(int i);
int right(int i);

void heapBuild(heap *inputHeap, int *table, int length);
void heapRestore(heap *inputHeap, int i);

int heapRemoveMax(heap *inputHeap, int *out);
void heapInsert(heap *inputHeap, int v);