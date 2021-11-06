#pragma once

#define MAX_LEVEL 5

#ifndef INT_MAX
	#define INT_MAX 2147483647
#endif

typedef struct SkipListNode 
{
	int key;
	int value;
	struct SkipListNode** next;
} SkipListNode;

typedef struct SkipList 
{
	int level;
	struct SkipListNode* header;
} SkipList;

SkipList* SkipListInit();
SkipListNode* SkipListSearch(SkipList* list, int key);
int SkipListDelete(SkipList* list, int key);
int SkipListInsert(SkipList* list, int key, int value);
void SkipListFree(SkipList* list);
void SkipListPrint(SkipList* list);
