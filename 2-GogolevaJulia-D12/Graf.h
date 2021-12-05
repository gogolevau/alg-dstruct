#ifndef GRAF_H
#define GRAF_H

typedef int** Graf;

Graf GrafFromFile(const char* filename, int* nodes, int* colors);
int ColorGraf(Graf graph, int nodes, int colors);
int* GetNodeColorsFromGraf(Graf graf, int nodes);
void SolveColorizingGraf(const char* input_filename, const char* output_filename);

#endif
