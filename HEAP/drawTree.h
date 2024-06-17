#include <stdio.h>
#include <stdlib.h>

typedef struct tnode
{
	int val;
	struct Tnode *parent;
	struct Tnode *left;
	struct Tnode *right;
} tnode;

int _print_t(tnode *tree, int is_left, int offset, int depth, char s[20][255]);
void print_t(tnode *tree);
void printTabAsHeap(int tab[], int length);