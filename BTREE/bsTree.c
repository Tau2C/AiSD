#include <stdlib.h>
#include "bsTree.h"

tnode *bstCreateNode(int value, char* name, char* surname)
{
	tnode *result;

	result = (tnode *)malloc(sizeof(tnode));
	result->val = value;
	result->left = NULL;
	result->parent = NULL;
	result->right = NULL;
	result->name = malloc(strlen(name));
	strcpy(result->name, name);
	result->surname = malloc(strlen(surname));
	strcpy(result->surname, surname);

	return result;
}

void freeBstNode(tnode* node)
{
	free(node->name);
	free(node->surname);
	free(node);
}

tnode* find_by_value(tnode* tree, int value)
{
	if (tree->val < value)
	{
		return find_by_value(tree->right, value);
	}
	else if (tree->val > value)
	{
		return find_by_value(tree->left, value);
	}
	else if (tree->val == value)
	{
		return tree;
	}
	return NULL;
}

tnode *bstAdd(tnode *root, tnode *newLeaf)
{
	if (root == NULL)
		return newLeaf;
	if (newLeaf == NULL)
		return root;
	tnode *y = NULL;
	tnode *x = root;
	while (x != NULL)
	{
		y = x;
		if (newLeaf->val < x->val)
			x = x->left;
		else
			x = x->right;
	}
	newLeaf->parent = y;
	if (y == NULL)
	{
		return newLeaf;
	}
	else
	{
		if (newLeaf->val < y->val)
			y->left = newLeaf;
		else
			y->right = newLeaf;
	}
	return root;
}

void free_tree(tnode *node)
{
	if (node != NULL)
	{
		if (node->left != NULL)
			free_tree(node->left);
		if (node->right != NULL)
			free_tree(node->right);
		freeBstNode(node);
	}
}