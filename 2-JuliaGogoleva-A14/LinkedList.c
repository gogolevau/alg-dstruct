#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

LinkedList* LinkedListInit(){
	LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
	if (list == NULL)
		return NULL;
	
	list->next = NULL;
	list->key = INT_MAX;
	list->value = INT_MAX;
	
	return list;
}
LinkedListNode* LinkedListSearch(LinkedList* list, int key){
	if (list == NULL)
		return NULL;
	
	LinkedListNode* node;
	for (node = list; node->next != NULL && node->key != key; node = node->next);
	if (node->key == key)
		return node;
	else
		return NULL;
}

int LinkedListDelete(LinkedList* list, int key){
	if (list == NULL)
		return 1;
	
	LinkedListNode* node;
	for (node = list; node->next != NULL && node->next->key != key; node = node->next);
	
	if (node->next && node->next->key == key){
		LinkedListNode* del_node = node->next;
		node->next = node->next->next;
		free(del_node);
		return 0;
	}
	else
		return 1;
}

int LinkedListInsert(LinkedList* list, int key, int value){
	LinkedListNode* new_node = (LinkedListNode*)malloc(sizeof(LinkedListNode));
	if (new_node == NULL)
		return 0;
	
	new_node->key = key;
	new_node->value = value;
	
	LinkedListNode* node = list;
	while (node->next != NULL){
		if (node->key == key){
			node->value = value;
			return 0;
		}
		
		if (node->next->key > key){
			new_node->next = node->next;
			node->next = new_node;
			return 1;
		}
		
		node = node->next;
	}
	node->next = new_node;
	new_node->next = NULL;
	return 1;
}

void LinkedListFree(LinkedList* list){
	if (list == NULL)
		return;
	
	LinkedListNode* prev_node = list;
	LinkedListNode* node = list->next;
	
	if (prev_node->next == NULL){
		free(prev_node);
	}
	else{
		while(node != NULL){
			free(prev_node);
			prev_node = node;
			node = node->next;
		}
	}
}

void LinkedListPrint(LinkedList* list){
	if (list == NULL){
		printf("NULL\n");
		return;
	}

	LinkedListNode* node = list->next;

	while (node != NULL) {
		printf("%d[%d]->", node->key, node->value);
		node = node->next;
	}
}
