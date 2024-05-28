#include <stdio.h>
#include <stdlib.h>
#include "bsTree.h"

int main(void)
{
	/*
		tnode *root, *leaf1, *leaf2, *leaf3;

		root = bstCreateNode(0);
		leaf1 = bstCreateNode(1);
		leaf2 = bstCreateNode(2);
		leaf3 = bstCreateNode(3);

		root->left = leaf1;
		leaf1->parent = root;
		root->right = leaf2;
		leaf2->parent = root;
		leaf3->parent = leaf1;
		leaf1->left = leaf3;

		print_t(root);
		free_tree(root);
	*/

	tnode *tak = NULL;

	tak = bstAdd(tak, bstCreateNode(0, "Kamil", "Śliwa"));
	tak = bstAdd(tak, bstCreateNode(4, "Kamil", "Śliwa"));
	tak = bstAdd(tak, bstCreateNode(3, "Mateusz", "Pokrywka"));
	tak = bstAdd(tak, bstCreateNode(7, "Kamil", "Śliwa"));
	tak = bstAdd(tak, bstCreateNode(5, "Łukasz", "Pachla"));

	print_t(tak);

	tnode* luka = find_by_value(tak, 5);
	printf("%s %s\n\r", luka->name, luka->surname);

	luka = find_by_value(tak, 3);
	printf("%s %s\n\r", luka->name, luka->surname);

	luka = find_by_value(tak, 0);
	printf("%s %s\n\r", luka->name, luka->surname);

	free_tree(tak);

	return 0;
}
