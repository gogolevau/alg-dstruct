#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include "Memallocator.h"

#define MAX_ITER 100
#define STEP 100
#define MAX_ELEMENTS MAX_ITER * STEP


int main()
{
	setlocale(LC_ALL, "RUS");

	FILE* file = fopen("tests.csv", "w");
	fprintf(file, "Numb;count;memalloc;malloc\n");

	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);

	void* mem = malloc(MemGetMinimumSize() * MAX_ELEMENTS + MAX_ELEMENTS);
	MemInit(mem, MemGetMinimumSize() * MAX_ELEMENTS + MAX_ELEMENTS);

	for (int i = 1; i < MAX_ITER + 1; i++)
	{
		LARGE_INTEGER start, end;
		double std1_res, std2_res;
		int counter = i * STEP;

		QueryPerformanceCounter(&start);

		for (int k = 0; k < counter; k++)
		{
			void* arr[MAX_ELEMENTS];
			if (k < counter / 2)
			{
				arr[k] = malloc(1);
			}
			else free(arr[counter - 1 - k]);
		}
		QueryPerformanceCounter(&end);
		std1_res = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;

		QueryPerformanceCounter(&start);

		for (int k = 0; k < counter; k++)
		{
			void* arr[MAX_ELEMENTS];
			if (k < counter / 2) {
				arr[k] = MemAlloc(1);
			}
			else MemFree(arr[counter - 1 - k]);
		}
		QueryPerformanceCounter(&end);
		std2_res = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
		fprintf(file, "%d;%d;%lf;%lf\n", i, counter, std2_res, std1_res);
	}

	MemDone();
	free(mem);
}