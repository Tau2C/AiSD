#include <stdio.h>
#include "LinkedList.h"

int main(void) {

	Finger fingers[5];
	int i;
	
	createFingers(fingers);

	if(fingersEqual(& fingers[0], & fingers[0])) {
		puts("finger_0 == finger_0: Ok");
	}
	if(! fingersEqual(& fingers[0], & fingers[1])) {
		puts("finger_0 != finger_1: Ok");
	}
	
	for(i = 0; i<5; i++) {
		printFingerInfo(& fingers[i]);
	}

	DoubleLinkedList list;
	ListNode nodes[5];
	
	list.head = NULL;

	for (i = 0; i < sizeof(fingers) / sizeof(Finger); i++)
	{
		nodes[i].data = fingers[i];
	}

	listInsert(&list, &nodes[0]);
	listInsert(&list, &nodes[1]);
	listInsert(&list, &nodes[2]);
	listInsert(&list, &nodes[3]);
	listInsert(&list, &nodes[4]);

	listPrint(&list);
	
	printFingerInfo(&listFind(&list, &fingers[3])->data);
	putchar('\n');

	Finger finger = {
		0x1337,
		"Chyba ty",
	};
	ListNode finger_node = {
		finger
	};

	listInsert(&list, &finger_node);
	listPrint(&list);

	listRemove(&list, listFind(&list, &finger));
	
	listPrint(&list);
	 
	return 0;
}