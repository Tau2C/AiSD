#ifndef LINKEDLIST_1FDI_PRZ
#define LINKEDLIST_1FDI_PRZ

#include "../dataTypes/DataTypes.h"

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
ListNode * listFind2(const DoubleLinkedList * list, const Finger * finger);
ListNode * listInsert(DoubleLinkedList * list, ListNode * newNode);
ListNode * listRemove(DoubleLinkedList * list, ListNode * nodeToRemove);

#endif
