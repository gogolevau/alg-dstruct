#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "LinkedList.h"
#include "SkipList.h"


int main(int argc, char** argv){
	FILE* csv_table = fopen("Compare.csv", "wr");
	fprintf(csv_table, "Test\tOperations\tSkipList\tLinkedList\n");
	
	for (int i = 1; i <= 100; i++){
		clock_t begin, end;
		double linked_list_time_result, skip_list_time_result;
		
		long operations_amount = i * 100;
		
		begin = clock();
		SkipList* skip_list = SkipListInit();
		
		for (long k = 0; k < operations_amount; k++)
			SkipListInsert(skip_list, k, k);
		
		for (long k = 0; k < operations_amount; k++)
			SkipListSearch(skip_list, k);
		
		for (long k = 0; k < operations_amount/2; k++)
			SkipListDelete(skip_list, k);
		
		SkipListFree(skip_list);
		end = clock();
		
		skip_list_time_result = (double)(end - begin) / CLOCKS_PER_SEC;
	
		
		begin = clock();
		LinkedList* linked_list = LinkedListInit();
		
		for (long k = 0; k < operations_amount; k++)
			LinkedListInsert(linked_list, k, k);
		
		for (long k = 0; k < operations_amount; k++)
			LinkedListSearch(linked_list, k);
		
		for (long k = 0; k < operations_amount/2; k++)
			LinkedListDelete(linked_list, k);
		
		LinkedListFree(linked_list);
		end = clock();
		
		linked_list_time_result = (double)(end - begin) / CLOCKS_PER_SEC;
	
		operations_amount = operations_amount * 2.5;
		fprintf(csv_table, "%d\t%lu\t%lf\t%lf\n", i, operations_amount, skip_list_time_result, linked_list_time_result);
	}
	fclose(csv_table);
	return 0;
}
