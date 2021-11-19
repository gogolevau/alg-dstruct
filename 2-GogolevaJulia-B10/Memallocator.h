#pragma once

typedef struct MemBlock;

int MemInit(void* pMemory, int size);
void MemDone();
void* MemAlloc(int size);
void MemFree(void* p);
int MemGetMinimumSize();
int MemGetBlockSize();

