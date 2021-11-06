#include "gtest/gtest.h"

extern "C" {
#include <stdlib.h>
#include "SkipList.h"
#include "LinkedList.h"
}


SkipList* test_skip_list_creation(){
	SkipList* list;
	list = (SkipList*) malloc(sizeof(SkipList));
	SkipListNode* header = (SkipListNode*) malloc(sizeof(SkipListNode));
	list->header = header;
	header->key = INT_MAX;
	header->value = INT_MAX;
	header->next = (SkipListNode**) malloc(sizeof(SkipListNode*) * MAX_LEVEL);

	for (int i = 0; i < MAX_LEVEL; i++)
		header->next[i] = header;

	list->level = 1;
	return list;
}


TEST(InitSkipListCase, Initialisation) {
	SkipList* list = SkipListInit();
	ASSERT_TRUE(list != nullptr);
	ASSERT_TRUE(list->header != nullptr);
	ASSERT_TRUE(list->header->next != nullptr);
	ASSERT_TRUE(list->header->next[0] == list->header);
	EXPECT_TRUE(list->level == 1);
	EXPECT_TRUE(list->header->key == INT_MAX);
}



TEST(SkipListSearchCase, SearchInEmptyList) {
	SkipList* list;
	list = (SkipList*) malloc(sizeof(SkipList));
	SkipListNode* header = (SkipListNode*) malloc(sizeof(SkipListNode));
	list->header = header;
	header->key = INT_MAX;
	header->value = INT_MAX;
	header->next = (SkipListNode**) malloc(sizeof(SkipListNode*) * MAX_LEVEL);

	for (int i = 0; i < MAX_LEVEL; i++) {
		header->next[i] = NULL;
	}

	list->level = 1;

	SkipListNode* search_result = SkipListSearch(list, 1);
	EXPECT_TRUE(search_result == nullptr);
}



TEST(SkipListSearchCase, SearchInListWithOneElementInIt){
	SkipList* list = test_skip_list_creation();
	
	int key = 1;
	int value = 1;
	
	SkipListNode* update[MAX_LEVEL];
	SkipListNode* element = list->header;
	
	update[1] = element;
	element = element->next[1];
	
	update[2] = list->header;
	list->level = 2;
	
	element = (SkipListNode*)malloc(sizeof(SkipListNode));
	element->key = key;
	element->value = value;
	element->next = (SkipListNode**)malloc(sizeof(SkipListNode*) * 3);
	
	element->next[1] = update[1]->next[1];
	update[1]->next[1] = element;
	
	element->next[2] = update[2]->next[2];
	update[2]->next[2] = element;
	
	SkipListNode* search_result = SkipListSearch(list, 1);
	ASSERT_TRUE(search_result != nullptr);
	EXPECT_TRUE(search_result->value == 1);
}



TEST(SkipListSearchCase, SearchInListWithOneElementWithoutNeedKey){
	SkipList* list = test_skip_list_creation();
	
	int key = 1;
	int value = 1;

	SkipListNode* update[MAX_LEVEL];
	SkipListNode* element = list->header;

	update[1] = element;
	element = element->next[1];
	
	update[2] = list->header;
	list->level = 2;
	
	element = (SkipListNode*)malloc(sizeof(SkipListNode));
	element->key = key;
	element->value = value;
	element->next = (SkipListNode**)malloc(sizeof(SkipListNode*) * 3);
	
	element->next[1] = update[1]->next[1];
	update[1]->next[1] = element;
	
	element->next[2] = update[2]->next[2];
	update[2]->next[2] = element;
	
	SkipListNode* search_result = SkipListSearch(list, 2);
	ASSERT_TRUE(search_result == nullptr);
}

TEST(SkipListDeleteCase, DeleteElementFromEmptyList){
	SkipList* list = test_skip_list_creation();
	int res = SkipListDelete(list, 1);
	ASSERT_TRUE(res == 1);
}



TEST(SkipListDeleteKeyCase, DeleteElementFromNotEmptyListWithNeedKey){
	SkipList* list = test_skip_list_creation();
	
	int key = 1;
	int value = 1;
	
	SkipListNode* update[MAX_LEVEL];
	SkipListNode* element = list->header;
	
	update[1] = element;
	element = element->next[1];
	
	update[2] = list->header;
	list->level = 2;
	
	element = (SkipListNode*)malloc(sizeof(SkipListNode));
	element->key = key;
	element->value = value;
	element->next = (SkipListNode**)malloc(sizeof(SkipListNode*) * 3);
	
	element->next[1] = update[1]->next[1];
	update[1]->next[1] = element;
	
	element->next[2] = update[2]->next[2];
	update[2]->next[2] = element;
	
	int res = SkipListDelete(list, 1);
	ASSERT_TRUE(res == 0);
}



TEST(SkipListDeleteKeyCase, DeleteElementFromNotEmptyWithNotNeedKey){
	SkipList* list = test_skip_list_creation();
	
	int key = 1;
	int value = 1;
	
	SkipListNode* update[MAX_LEVEL];
	SkipListNode* element = list->header;
	
	update[1] = element;
	element = element->next[1];
	
	update[2] = list->header;
	list->level = 2;
	
	element = (SkipListNode*)malloc(sizeof(SkipListNode));
	element->key = key;
	element->value = value;
	element->next = (SkipListNode**)malloc(sizeof(SkipListNode*) * 3);
	
	element->next[1] = update[1]->next[1];
	update[1]->next[1] = element;
	
	element->next[2] = update[2]->next[2];
	update[2]->next[2] = element;
	
	int res = SkipListDelete(list, 2);
	ASSERT_TRUE(res == 1);
}

TEST(SkipListDeleteListCase, DeleteNULLSkipList){
	ASSERT_NO_FATAL_FAILURE(SkipListFree(NULL));
}

TEST(SkipListDeleteListCase, DeleteEmptySkipList){
	SkipList* list = test_skip_list_creation();
	ASSERT_NO_FATAL_FAILURE(SkipListFree(list));
}

TEST(SkipListDeleteListCase, DeleteNotEmptySkipList){
	SkipList* list = test_skip_list_creation();

	int key = 1;
	int value = 1;
	
	SkipListNode* update[MAX_LEVEL];
	SkipListNode* element = list->header;
	
	update[1] = element;
	element = element->next[1];
	
	update[2] = list->header;
	list->level = 2;
	
	element = (SkipListNode*)malloc(sizeof(SkipListNode));
	element->key = key;
	element->value = value;
	element->next = (SkipListNode**)malloc(sizeof(SkipListNode*) * 3);
	
	element->next[1] = update[1]->next[1];
	update[1]->next[1] = element;
	
	element->next[2] = update[2]->next[2];
	update[2]->next[2] = element;
	
	ASSERT_NO_FATAL_FAILURE(SkipListFree(list));
}



TEST(InitLinkedListCase, SkipListInitialisation) {
	LinkedList* list = LinkedListInit();
	ASSERT_TRUE(list != nullptr);
	ASSERT_TRUE(list->next == nullptr);
	EXPECT_TRUE(list->value == INT_MAX);
	EXPECT_TRUE(list->key == INT_MAX);
}

TEST(LinkedListSearchCase, SearchInEmptyList) {
	LinkedList* list = (LinkedList*)malloc(sizeof(LinkedListNode));
	list->next = NULL;
	list->key = INT_MAX;
	list->value = INT_MAX;

	LinkedListNode* search_result = LinkedListSearch(list, 1);
	EXPECT_TRUE(search_result == nullptr);
}



TEST(LinkedListSearchCase, SearchInListWithOneElementInIt){
	LinkedList* list = (LinkedList*)malloc(sizeof(LinkedListNode));
	list->next = NULL;
	list->key = INT_MAX;
	list->value = INT_MAX;
	
	list->next = (LinkedListNode*)malloc(sizeof(LinkedListNode));
	list->next->key = 1;
	list->next->value = 2;

	LinkedListNode* search_result = LinkedListSearch(list, 1);
	ASSERT_TRUE(search_result != nullptr);
	EXPECT_TRUE(search_result->value == 2);
}



TEST(LinkedListSearchCase, SearchInListWithOneElementWithoutNeedKey){
	LinkedList* list = (LinkedList*)malloc(sizeof(LinkedListNode));
	list->next = NULL;
	list->key = INT_MAX;
	list->value = INT_MAX;
	
	list->next = (LinkedListNode*)malloc(sizeof(LinkedListNode));
	list->next->key = 1;
	list->next->value = 2;

	LinkedListNode* search_result = LinkedListSearch(list, 2);
	ASSERT_TRUE(search_result == nullptr);
}

TEST(LinkedListDeleteKeyCase, DeleteElementFromEmptyList){
	LinkedList* list = (LinkedList*)malloc(sizeof(LinkedListNode));
	list->next = NULL;
	list->key = INT_MAX;
	list->value = INT_MAX;
	
	int res = LinkedListDelete(list, 1);
	ASSERT_TRUE(res == 1);
}



TEST(LinkedListDeleteKeyCase, DeleteElementFromNotEmptyListWithNeedKey){
	LinkedList* list = (LinkedList*)malloc(sizeof(LinkedListNode));
	list->next = NULL;
	list->key = INT_MAX;
	list->value = INT_MAX;
	
	list->next = (LinkedListNode*)malloc(sizeof(LinkedListNode));
	list->next->key = 1;
	list->next->value = 2;
	
	int res = LinkedListDelete(list, 1);
	ASSERT_TRUE(res == 0);
}



TEST(LinkedListDeleteKeyCase, DeleteElementFromNotEmptyWithNotNeedKey){
	LinkedList* list = (LinkedList*)malloc(sizeof(LinkedListNode));
	list->next = NULL;
	list->key = INT_MAX;
	list->value = INT_MAX;
	
	list->next = (LinkedListNode*)malloc(sizeof(LinkedListNode));
	list->next->key = 2;
	list->next->value = 2;
	
	int res = LinkedListDelete(list, 1);
	ASSERT_TRUE(res == 1);
}

TEST(LinkedListDeleteListCase, DeleteNULLList){
	ASSERT_NO_FATAL_FAILURE(LinkedListFree(NULL));
}

TEST(LinkedListDeleteListCase, DeleteEmptyList){
	LinkedList* list = (LinkedList*)malloc(sizeof(LinkedListNode));
	list->next = NULL;
	list->key = INT_MAX;
	list->value = INT_MAX;
	ASSERT_NO_FATAL_FAILURE(LinkedListFree(list));
}

TEST(LinkedListDeleteListCase, DeleteNotEmptyList){
	LinkedList* list = (LinkedList*)malloc(sizeof(LinkedListNode));
	list->next = NULL;
	list->key = INT_MAX;
	list->value = INT_MAX;
	
	list->next = (LinkedListNode*)malloc(sizeof(LinkedListNode));
	list->next->key = 2;
	list->next->value = 2;
	
	
	ASSERT_NO_FATAL_FAILURE(LinkedListFree(list));
}
