#pragma once

#ifndef INT_MAX
	#define INT_MAX 2147483647
#endif

typedef struct LinkedListNode{
	struct LinkedListNode* next;
	int key;
	int value;
} LinkedListNode;

typedef struct LinkedListNode LinkedList;

LinkedList* LinkedListInit();
LinkedListNode* LinkedListSearch(LinkedList* list, int key);
int LinkedListDelete(LinkedList* list, int key);
int LinkedListInsert(LinkedList* list, int key, int value);
void LinkedListFree(LinkedList* list);
void LinkedListPrint(LinkedList* list);
