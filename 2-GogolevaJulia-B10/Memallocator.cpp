#include <stdlib.h>
#include "Memallocator.h"

typedef struct MemBlock
{
	struct MemBlock* next;
	int reserved_flag;
	unsigned size;
} MemBlock;

static MemBlock* start;


int MemInit(void* pMemory, int size) {
	start = (MemBlock*)pMemory;
	start->size = size - sizeof(MemBlock);
	start->reserved_flag = 0;
	start->next = NULL;
	return 1;
}


void MemDone()
{
	start = NULL;
}

void* MemAlloc(int size)
{
	MemBlock* block = start;

	while (block != NULL)
	{
		if (block->reserved_flag == 0 && block->size >= size)
		{
			if (block->size > sizeof(MemBlock) + size)
			{
				MemBlock* next_block = (MemBlock*)(((char*)block) + sizeof(MemBlock) + size);
				next_block->size = block->size - size - sizeof(MemBlock);
				next_block->next = block->next;
				next_block->reserved_flag = 0;
				block->size = size;
				block->next = next_block;
				block->reserved_flag = 1;
			}
			else
				block->reserved_flag = 1;

			return (void*)(((char*)block) + sizeof(MemBlock));
		}
		block = block->next;
	}
	return NULL;
}

void MemFree(void* p)
{
	MemBlock* deallocated_block = (MemBlock*)(((char*)p) - sizeof(MemBlock));


	deallocated_block->reserved_flag = 0;

	if (deallocated_block != start)
	{
		MemBlock* prev = start;

		while (prev->next != NULL)
		{
			if (prev->next == deallocated_block)
			{
				if (prev->reserved_flag == 0)
				{
					prev->next = deallocated_block->next;
					prev->size += deallocated_block->size + sizeof(MemBlock);
					deallocated_block = prev;
				}
				break;
			}
			prev = prev->next;
		}
	}

	if (deallocated_block->next != NULL && deallocated_block->next->reserved_flag == 0)
	{
		deallocated_block->size += deallocated_block->next->size + sizeof(MemBlock);
		deallocated_block->next = deallocated_block->next->next;
	}
}

int MemGetMinimumSize()
{
	return sizeof(MemBlock);
}

int MemGetBlockSize()
{
	return sizeof(MemBlock);
}





















