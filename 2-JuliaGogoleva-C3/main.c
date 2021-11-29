#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <windows.h>

int ParseGraph(FILE* stream, int***graph_p, int* graph_size){
	int val;
	fscanf(stream, "%d\n", &val);
	
	*graph_size = val;
	
	int** graph = (int**)malloc(sizeof(int*)* val);
	
	if (graph == NULL)
		return 0;
	
	for (int i = 0; i < val; i++){
		graph[i] = (int*)malloc(sizeof(int)*val);
		if (graph[i] == NULL){
			for (i--; i>=0; i--)
				free(graph[i]);
			free(graph);
			return 0;
		}
		memset(graph[i], 0, sizeof(int)*val);
	}
	
	
	while (1){
		int parent_node_index, neighbour_node_index;
		char line[250];
		char* line_p = line;
		
		if(fgets(line, 250, stream) == NULL)
			break;
		
		if (sscanf(line, "%d", &parent_node_index) <= 0)
			break;
		
		while(isdigit(*line_p)) line_p++;
		while(*line_p == ' ') line_p++;
		
		while (sscanf(line_p, "%d", &neighbour_node_index) > 0){
			while(isdigit(*line_p)) line_p++;
			while(*line_p == ' ') line_p++;
			graph[parent_node_index][neighbour_node_index] = 1;
			graph[neighbour_node_index][parent_node_index] = 1;
		}
	}
	*graph_p = graph;
	return 1;
}

void PrintGraph(int** graph, int size){
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			printf("%d ", graph[i][j]);
		}
		printf("\n");
	}
}

void BFS(int** graph, int size){
	int* vector = (int*)malloc(sizeof(int)*(size + 1));
	if (vector == NULL)
		return;
	vector[0] = 0;
	int* vector_tail = vector + 1;
	int* vector_cursor = vector;
	
	while (vector_tail - vector_cursor > 0){
		for (int i = 0; i < size; i++)
			graph[i][*vector_cursor] = 0;
		
		for (int j = 0; j < size; j++){
			if (graph[*vector_cursor][j] == 1){
				*vector_tail++ = j;
				for (int i = 0; i < size; i++)
					graph[i][j] = 0;
			}
		}
		printf("%d ", *vector_cursor);
		vector_cursor++;
	}
}

void TestGen(const char* filename){
	// increasing stack size
	srand(time(NULL));

	int links_amount = 1000;
	int nodes_amount = 10000;
	int links_in_one_node = links_amount / nodes_amount;
	
	FILE* input = fopen(filename, "w");
	fprintf(input, "%u\n", nodes_amount);
	
	for (int node_number = 0; node_number < nodes_amount; node_number++){
		fprintf(input, "%d", node_number);
		for (int links_amount = 0; links_amount <= links_in_one_node; links_amount++)
			fprintf(input, " %d", rand()%nodes_amount);
		fprintf(input, "\n");
	}
	fclose(input);
}

/*
Computer spec:

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
*/

int main(){
	int** graph, size;
	
	LARGE_INTEGER start, end, freq;
    QueryPerformanceFrequency(&freq);
	
	TestGen("Input.txt");
	FILE* file = fopen("Input.txt", "r");
	
	QueryPerformanceCounter(&start);
	if (ParseGraph(file, &graph, &size)){
		BFS(graph, size);
	}
    QueryPerformanceCounter(&end);
	
    printf("Working time %f\n", (double)(end.QuadPart - start.QuadPart) / freq.QuadPart);
	
	fclose(file);
	remove("Input.txt");
	return 0;
}
