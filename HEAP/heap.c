#include "heap.h"

void printHeap(heap h)
{
	printTabAsHeap(h.A, h.heapSize + 1);
}

int parent(int i)
{
	return i / 2;
}

int left(int i)
{
	return 2 * i;
}

int right(int i)
{
	return 2 * i + 1;
}

void heapRestore(heap *inputHeap, int i)
{
	int l = left(i);
	int r = right(i);
	int biggest = 0;
	if (l <= inputHeap->heapSize && inputHeap->A[l] > inputHeap->A[i])
		biggest = l;
	else
		biggest = i;
	if (r <= inputHeap->heapSize && inputHeap->A[r] > inputHeap->A[biggest])
		biggest = r;
	if (biggest != 0 && biggest != i)
	{
		int tmp = inputHeap->A[i];
		inputHeap->A[i] = inputHeap->A[biggest];
		inputHeap->A[biggest] = tmp;
		heapRestore(inputHeap, biggest);
	}
}

void heapBuild(heap *inputHeap, int *table, int length)
{
	inputHeap->A = table;
	inputHeap->heapSize = length;
	for (size_t i = length / 2; i > 0; i--)
	{
		heapRestore(inputHeap, i);
	}
}

int heapRemoveMax(heap *inputHeap, int *out)
{
	if (inputHeap->heapSize < 1)
		return 1;
	*out = inputHeap->A[1];
	inputHeap->A[1] = inputHeap->A[inputHeap->heapSize];
	inputHeap->heapSize -= 1;
	heapRestore(inputHeap, 1);
	return 0;
}

void heapInsert(heap *inputHeap, int v)
{
	inputHeap->heapSize += 1;
	int i = inputHeap->heapSize;
	while (i > 1 && inputHeap->A[parent(i)] < v)
	{
		inputHeap->A[i] = inputHeap->A[parent(i)];
		i = parent(i);
	}
	inputHeap->A[i] = v;
}
