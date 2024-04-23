#include <stdlib.h>
#include <stdio.h>
#include "LinkedList.h"
#include <stdbool.h>

ListNode * listFind(const DoubleLinkedList * list, const Finger * finger) {
	ListNode* x = list->head;
	while (x != NULL && !fingersEqual(&(x->data), finger))
	{
		x = x->next;
	}
	return x;
}

ListNode * listInsert(DoubleLinkedList * list, ListNode * newNode) {
	newNode->next = list->head;
	if (list->head != NULL)
		list->head->previous = newNode;
	list->head = newNode;
	newNode->previous = NULL;
}

void listRemove(DoubleLinkedList * list, ListNode * nodeToRemove) {
	if(nodeToRemove->previous != NULL)
		nodeToRemove->previous->next = nodeToRemove->next;
	else
		list->head = nodeToRemove->next;
	if (nodeToRemove->next != NULL)
		nodeToRemove->next->previous = nodeToRemove->previous;
}

void listPrint(DoubleLinkedList *list)
{
	ListNode *x = list->head;
	printf("head: %p\n", x);
	while (x != NULL)
	{
		if (x != list->head)
			printf("%p\n", x);
		printFingerInfo(&x->data);
		x = x->next;
	}
	putchar('\n');
}
