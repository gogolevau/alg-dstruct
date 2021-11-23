#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

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

int main(){
	int** graph, size;
	if (ParseGraph(stdin, &graph, &size)){
// 		PrintGraph(graph, size);
		BFS(graph, size);
	}
	return 0;
}
