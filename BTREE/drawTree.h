#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef DRAW_TREE_H

#define DRAW_TREE_H

typedef struct Tnode
{
	int val;
	char *name;
	char *surname;
	struct Tnode *parent;
	struct Tnode *left;
	struct Tnode *right;
} tnode;

int _print_t(tnode *tree, int is_left, int offset, int depth, char s[20][255]);
void print_t(tnode *tree);

#endif // DRAW_TREE_H
