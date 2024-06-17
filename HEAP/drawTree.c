#include <stdint.h>
#include "drawTree.h"

int _print_t(tnode *tree, int is_left, int offset, int depth, char s[20][255])
{
	/*Author this funstion is user1571409 from stackoverflow.com*/
	char b[20];
	int width = 5;

	if (!tree)
		return 0;

	sprintf(b, "(%3d)", tree->val);

	int left = _print_t(tree->left, 1, offset, depth + 1, s);
	int right = _print_t(tree->right, 0, offset + left + width, depth + 1, s);

#ifdef COMPACT
	for (int i = 0; i < width; i++)
		s[depth][offset + left + i] = b[i];

	if (depth && is_left)
	{

		for (int i = 0; i < width + right; i++)
			s[depth - 1][offset + left + width / 2 + i] = '-';

		s[depth - 1][offset + left + width / 2] = '.';
	}
	else if (depth && !is_left)
	{

		for (int i = 0; i < left + width; i++)
			s[depth - 1][offset - width / 2 + i] = '-';

		s[depth - 1][offset + left + width / 2] = '.';
	}
#else
	for (int i = 0; i < width; i++)
		s[2 * depth][offset + left + i] = b[i];

	if (depth && is_left)
	{

		for (int i = 0; i < width + right; i++)
			s[2 * depth - 1][offset + left + width / 2 + i] = '-';

		s[2 * depth - 1][offset + left + width / 2] = '+';
		s[2 * depth - 1][offset + left + width + right + width / 2] = '+';
	}
	else if (depth && !is_left)
	{

		for (int i = 0; i < left + width; i++)
			s[2 * depth - 1][offset - width / 2 + i] = '-';

		s[2 * depth - 1][offset + left + width / 2] = '+';
		s[2 * depth - 1][offset - width / 2 - 1] = '+';
	}
#endif

	return left + width + right;
}

void print_t(tnode *tree)
{
	/*Author this funstion is user1571409 from stackoverflow.com*/
	char s[20][255];
	for (int i = 0; i < 20; i++)
		sprintf(s[i], "%80s", " ");

	_print_t(tree, 0, 0, 0, s);

	for (int i = 0; i < 20; i++)
		printf("%s\n", s[i]);
}

void printTabAsHeap(int tab[], int length)
{
	tnode *heap;

	heap = (tnode *)malloc(length * sizeof(tnode));

	for (int i = 0; i < length - 1; i++)
	{
		int node, parent, left, right;

		node = i + 1;
		heap[i].val = tab[node];
		parent = (int)(node / 2);
		if (parent > 0)
			heap[i].parent = &heap[parent - 1];
		else
			heap[i].parent = NULL;

		left = 2 * node;
		if (left < length)
			heap[i].left = &heap[left - 1];
		else
			heap[i].left = NULL;

		right = left + 1;

		if (right < length)
			heap[i].right = &heap[right - 1];
		else
			heap[i].right = NULL;
	}
	print_t(heap);

	free(heap);
}