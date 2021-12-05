#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graf.h"

#define NODE_WITHOUT_COLOR (-1)

Graf GrafFromFile(const char* filename, int* nodes, int* colors){
	
	FILE* file = fopen(filename, "r");
	if (file == NULL)
		return NULL;
	
	fscanf(file, "%d %d", nodes, colors);
	
	Graf graf = (Graf)malloc(sizeof(int*) * (*nodes));
	if (graf == NULL){
		fclose(file);
		return NULL;
	}
	for (int i = 0; i < *nodes; i++){
		graf[i] = (int*)malloc(sizeof(int) * (*nodes));
		if (graf[i] == NULL){
			for (int k = 0; k < i; k++)
				free(graf[i]);
			free(graf);
			fclose(file);
			return NULL;
		}
		memset(graf[i], 0, sizeof(int) * (*nodes));
	}
	
	int node1, node2;
	while (fscanf(file, "%d %d\n", &node1, &node2) == 2){
		node1--;
		node2--;
		graf[node1][node2] = NODE_WITHOUT_COLOR;
		graf[node2][node1] = NODE_WITHOUT_COLOR;
	}
	
	if (*nodes == 1)
		graf[0][0] = NODE_WITHOUT_COLOR;
	
	fclose(file);
	return graf;
}

void FreeGraf(Graf graf, int nodes){
	for (int i = 0; i < nodes; i++)
		free(graf[i]);
	free(graf);
}

static int __ColorGraf(Graf graf, int nodes, int node, int colors, int* colorized){
	int* colors_check = (int*)malloc(sizeof(int) * colors);
	memset(colors_check, 0, sizeof(int) * colors);
	
	for (int i = 0; i < nodes; i++){
		if (graf[node][i] != 0 && graf[node][i] != NODE_WITHOUT_COLOR)
			colors_check[graf[node][i]-1] = 1;
	}
	

	for (int c = 1; c <= colors; c++){
		if (colors_check[c-1] == 0){
			
			for (int k = 0; k < nodes; k++)
				if (graf[k][node] != 0)
					graf[k][node] = c;
				
			(*colorized)++;
				
			for (int i = 0; i < nodes; i++){
				if (graf[node][i] == NODE_WITHOUT_COLOR){
					if (__ColorGraf(graf, nodes, i, colors, colorized) == 1){
						free(colors_check);
						return 1;
					}
				}
			}
			
			if (nodes == *colorized){
				free(colors_check);
				return 1;
			}
			break;
		}
	}
	free(colors_check);
	return 0;
}


int ColorGraf(Graf graf, int nodes, int colors){
	int colorized = 0;
	return __ColorGraf(graf, nodes, 0, colors, &colorized);
}

int* GetNodeColorsFromGraf(Graf graf, int nodes){
	
	int* node_colors = (int*)malloc(sizeof(int) * nodes);
	int* node_cursor = node_colors;
	
	if (node_colors == NULL)
		return NULL;
	
	for (int i = 0; i < nodes; i++){
		for (int k = 0; k < nodes; k++){
			if (graf[k][i] != 0 && graf[k][i] != NODE_WITHOUT_COLOR){
				*node_cursor++ = graf[k][i];
				break;
			}
		}
	}
	
	return node_colors;
}

void SolveColorizingGraf(const char* input_filename, const char* output_filename){
	int nodes, colors;
	Graf graf = GrafFromFile(input_filename, &nodes, &colors);
	
	FILE* output_file = fopen(output_filename, "w");
	if (output_file == NULL)
		return;
	
	if (ColorGraf(graf, nodes, colors) == 0){
		putc('0', output_file);
	}
	else{
		int* node_colors = GetNodeColorsFromGraf(graf, nodes);
		
		for (int i = 0; i < nodes; i++){
			if (i < nodes - 1)
				fprintf(output_file, "%d ", node_colors[i]);
			else
				fprintf(output_file, "%d", node_colors[i]);
		}
		free(node_colors);
	}
	FreeGraf(graf, nodes);
	fclose(output_file);
}
