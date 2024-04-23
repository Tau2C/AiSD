#include "DataTypes.h"

typedef struct SListNode ListNode;

typedef struct SListNode {
  Finger data;
  ListNode * next;
  ListNode * previous;
} ListNode;

typedef struct SDoubleLinkedList {
  ListNode * head;
} DoubleLinkedList;

ListNode * listFind(const DoubleLinkedList * list, const Finger * finger);
ListNode * listInsert(DoubleLinkedList * list, ListNode * newNode);
void listRemove(DoubleLinkedList * list, ListNode * nodeToRemove);
void listPrint(DoubleLinkedList * list);