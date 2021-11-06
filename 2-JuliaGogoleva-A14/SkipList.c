#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "SkipList.h"

static void __SkipListNodeFree(SkipListNode* node) {
	if (node != NULL) {
		if (node->next != NULL)
			free(node->next);
		free(node);
	}
}

SkipList* SkipListInit() {
	SkipList* list;
	list = (SkipList*) malloc(sizeof(SkipList));
	if (list == NULL)
		return NULL;
	
	SkipListNode* header = (SkipListNode*) malloc(sizeof(SkipListNode));
	if (header == NULL){
		free(list);
		return NULL;
	}
	
	list->header = header;
	header->key = INT_MAX;
	
	header->next = (SkipListNode**) malloc(sizeof(SkipListNode*) * MAX_LEVEL);
	if (header->next == NULL){
		free(header);
		free(list);
		return NULL;
	}

	for (int i = 0; i < MAX_LEVEL; i++)
		header->next[i] = list->header;

	list->level = 1;

	return list;
}

SkipListNode* SkipListSearch(SkipList* list, int key) {
	if (list == NULL)
		return NULL;
	
	SkipListNode* element = list->header;

	for (int i = list->level; i >= 1; i--) {
		while (element->next[i] && element->next[i]->key < key) {
			element = element->next[i];
		}
	}

	if (element->next[1] && element->next[1]->key == key)
		return element->next[1];
	else
		return NULL;
}

int SkipListDelete(SkipList* list, int key) {
	int i;
	SkipListNode* update[MAX_LEVEL];
	SkipListNode* element = list->header;

	for (i = list->level; i >= 1; i--) {
		while (element->next[i]->key < key)
			element = element->next[i];

		update[i] = element;
	}

	element = element->next[1];

	if (element->key == key) {
		for (i = 1; i <= list->level; i++) {
			if (update[i]->next[i] != element)
				break;

			update[i]->next[i] = element->next[i];
		}

		__SkipListNodeFree(element);

		while (list->level > 1 && list->header->next[list->level] == list->header) 
			list->level--;
		
		return 0;
	}
	
	return 1;
}

int SkipListInsert(SkipList* list, int key, int value) {
	SkipListNode* update[MAX_LEVEL + 1];
	SkipListNode* element = list->header;
	int i, level;

	for (i = list->level; i >= 1; i--) {
		while (element->next[i]->key < key)
			element = element->next[i];
		update[i] = element;
	}

	element = element->next[1];

	if (key == element->key) {
		element->value = value;
		return 0;
	}
	else {
		level = rand() % MAX_LEVEL;

		if (level > list->level) {
			for (i = list->level + 1; i <= level; i++)
				update[i] = list->header;
			list->level = level;
		}

		element = (SkipListNode*)malloc(sizeof(SkipListNode));
		element->key = key;
		element->value = value;
		element->next = (SkipListNode**)malloc(sizeof(SkipListNode*)*(level + 1));

		for (i = 1; i <= level; i++) {
			element->next[i] = update[i]->next[i];
			update[i]->next[i] = element;
		}
	}

	return 1;
}


void SkipListFree(SkipList* list) {
	if (list == NULL)
		return;
	
	SkipListNode* current = list->header->next[1];

	while (current != list->header) {
		SkipListNode* forward = current->next[1];
		free(current->next);
		free(current);
		current = forward;
	}

	free(current->next);
	free(current);
	free(list);
}


void SkipListPrint(SkipList* list) {
	if (list == NULL){
		printf("NULL\n");
		return;
	}

	SkipListNode* node = list->header;

	while (node && node->next[1] != list->header) {
		printf("%d[%d]->", node->next[1]->key, node->next[1]->value);
		node = node->next[1];
	}
}
