#pragma warning (disable:4996)
#define _CRT_SECURE_NO_WORNINGS

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "Graf.h"


#define DIV 1048576
#define WIDTH 7

#define STRESS_TEST_LINKS_AMOUNT 100000
#define STRESS_TEST_NODES_AMOUNT 10000
#define STRESS_TEST_COLORS_AMOUNT 100

/*
Stress test info:
*Computer spec:
CsManufacturer : HUAWEI
CsModel : BOHK-WAX9X
CsName : LAPTOP-T4FCKU10
CsNetworkServerModeEnabled : True
CsNumberOfLogicalProcessors : 8
CsNumberOfProcessors : 1
CsProcessors : {AMD Ryzen 7 3700U with Radeon Vega Mobile Gfx }
CsPowerSupplyState : Safe
CsSystemType : x64-based PC
CsTotalPhysicalMemory : 7448702976
CsPhyicallyInstalledMemory : 8388608
OsVersion : 10.0.19042
OsBuildNumber : 19042
OsForegroundApplicationBoost : Maximum
OsTotalVisibleMemorySize : 7274124
OsFreePhysicalMemory : 2204788
OsTotalVirtualMemorySize : 13041292
OsFreeVirtualMemory : 6367164
OsInUseVirtualMemory : 6674128
OsNumberOfProcesses : 208
OsArchitecture : 64-разрядная

*Test information:

*/


void StressTestGen(const char* filename) {
	srand(time(NULL));

	int links_in_one_node = STRESS_TEST_LINKS_AMOUNT / STRESS_TEST_NODES_AMOUNT;

	FILE* input = fopen(filename, "w");
	
	if (input == NULL)
		return;
	
	links_in_one_node--;
	fprintf(input, "%u %d\n", STRESS_TEST_NODES_AMOUNT, STRESS_TEST_COLORS_AMOUNT);
	
	for (int i = 1; i < STRESS_TEST_NODES_AMOUNT; i++){
		fprintf(input, "%d %d\n", i, i+1);
	}

	for (int node_number = 0; node_number <= STRESS_TEST_NODES_AMOUNT - 1; node_number++) {
		for (int links_amount = 0; links_amount < links_in_one_node; links_amount++)
			fprintf(input, "%d %d\n", node_number + 1, rand() % (STRESS_TEST_NODES_AMOUNT-1) + 1);
	}
	fclose(input);
}

int main(){
	LARGE_INTEGER start, end, freq;
	QueryPerformanceFrequency(&freq);

	StressTestGen("input.txt");

	QueryPerformanceCounter(&start);
	
	SolveColorizingGraf("input.txt", "output.txt");
	
	QueryPerformanceCounter(&end);

	printf("Working time %f\n", (double)(end.QuadPart - start.QuadPart) / freq.QuadPart);
	
	remove("input.txt");

	MEMORYSTATUSEX statex;

	statex.dwLength = sizeof(statex);

	GlobalMemoryStatusEx(&statex);

	printf("There is  %*ld percent of memory in use.\n", WIDTH, statex.dwMemoryLoad);
	printf("There are %*I64d total Mbytes of physical memory.\n", WIDTH, statex.ullTotalPhys / DIV);
	printf("There are %*I64d free Mbytes of physical memory.\n", WIDTH, statex.ullAvailPhys / DIV);
	printf("There are %*I64d total Mbytes of paging file.\n", WIDTH, statex.ullTotalPageFile / DIV);
	printf("There are %*I64d free Mbytes of paging file.\n", WIDTH, statex.ullAvailPageFile / DIV);
	printf("There are %*I64d total Mbytes of virtual memory.\n", WIDTH, statex.ullTotalVirtual / DIV);
	printf("There are %*I64d free Mbytes of virtual memory.\n", WIDTH, statex.ullAvailVirtual / DIV);
	printf("There are %*I64d free Mbytes of extended memory.\n", WIDTH, statex.ullAvailExtendedVirtual / DIV);
	return 0;
}
