#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "heap.h"

#define START_SIZE 14

int main()
{
	int tab[START_SIZE];
	heap myHeap;

	tab[1] = 957;
	tab[2] = 943;
	tab[3] = 907;
	tab[4] = 891;
	tab[5] = 856;
	tab[6] = 813;
	tab[7] = 792;
	tab[8] = 754;
	tab[9] = 541;
	tab[10] = 512;
	tab[11] = 409;
	tab[12] = 96;
	tab[13] = 24;

	myHeap.A = tab;
	myHeap.heapSize = 13;
	printHeap(myHeap);

	srand(time(NULL));
	for (size_t i = 0; i < 10; i++)
	{
		tab[i + 1] = rand() % 1000;
	}

	heapBuild(&myHeap, tab, 10);

	printHeap(myHeap);

	int out;
	heapRemoveMax(&myHeap, &out);
	printf("%d\n\r", out);
	heapInsert(&myHeap, 888);
	heapInsert(&myHeap, 15);
	heapRemoveMax(&myHeap, &out);
	printf("%d\n\r", out);
	heapInsert(&myHeap, 42);

	printHeap(myHeap);

	return 0;
}
