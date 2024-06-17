#include <stdlib.h>
#include <stdio.h>
#include "LinkedList.h"
#include <stdbool.h>

ListNode * listFind(const DoubleLinkedList * list, const Finger * finger) {
  ListNode * node;
  bool areFingersEqual;
  
  if(NULL == list) {
    puts("listFind: NULL list");
    exit(-1);
  }
  if(NULL == list->head) {
    puts("listFind: NULL head of the list");
    exit(-1);
  }
  if(NULL == finger) {
    puts("listFind: NULL finger");
    exit(-1);
  }

  node = list->head;
  areFingersEqual = fingersEqual(finger, & node->data);
  while(node != NULL && false == areFingersEqual) {
    node = node->next;
    areFingersEqual = fingersEqual(finger, & node->data);
  }
  
  return node;
}

ListNode * listFind2(const DoubleLinkedList * list, const Finger * finger) {
  ListNode * listNode;

  listNode = list->head;
  while(listNode != NULL && false == fingersEqual(finger, & listNode->data)) {
        listNode  = listNode->next;
  }
  return listNode;
}

ListNode * listInsert(DoubleLinkedList * list, ListNode * newNode) {
  if(NULL == list) {
    puts("listInsert: NULL list");
    exit(-1);
  }

  if(NULL == newNode) {
    puts("listInsert: NULL newNode");
    exit(-1);
  }

  if(NULL != newNode->next || NULL != newNode->previous) {
    puts("listInsert: newNode is in a list");
    exit(-1);
  }

  exit(-1);
}

ListNode * listRemove(DoubleLinkedList * list, ListNode * nodeToRemove) {
  ListNode * node;
  bool fingersEqual;
  
  if(NULL == list) {
    puts("listFind: NULL node");
    exit(-1);
  }
  if(NULL == nodeToRemove) {
    puts("listFind: NULL finger");
    exit(-1);
  }

  exit(-1);
}