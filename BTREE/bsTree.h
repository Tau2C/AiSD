#include "drawTree.h"

/**
*    Creates an empty BST node.
*    @param value the key value of the node
*    @param name name of the person in tree
*    @param lastname lastname of the person in tree
*   @return a node with NULL parent, left and right
*/
tnode* bstCreateNode(int value, char* name, char* lastname);

/**
*   Adds the newLeaf to the BST.
*   @param root the root node of the BST
*   @param newLeaf the node to be added to the BST
*   @return the root of the BST
*/
tnode* bstAdd(tnode *root, tnode *newLeaf);

tnode* find_by_value(tnode* tree, int value);

void freeBstNode(tnode* node);

void free_tree(tnode *root);