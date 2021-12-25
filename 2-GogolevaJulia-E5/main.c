#pragma warning (disable:4996)
#define _CRT_SECURE_NO_WORNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "BinTree.h"

#define LINE_LEN 100

int IntCompare(int* a, int*b){
	return *a-*b;
}

int main(){
	char command;
	int value;
	char string[LINE_LEN];
	void* value_p;
	
	BinTree tree;
	tree.head = NULL;
	
	// for int implementation
	// tree.fun = (CompareFunction)IntCompare;
	
	// for str implementation
	tree.fun = (CompareFunction)strcmp;
	

	while (scanf("%c", &command) >= 1){
		if (command != 'p' && command != 'q'){
			// for int implementation
			// scanf("%i", &value);
			// value_p = (int*)malloc(sizeof(int));
			// *value_p = value;
			
			// for str implementation
			fgets(string, LINE_LEN, stdin);
			int strlength = strlen(string) - 2;
			value_p = malloc(sizeof(char) * (strlength + 1));
			memcpy(value_p, string + 1, strlength);
			((char*)value_p)[strlength] = '\0';
		}
		switch(command){
			case 'a':
				BinTreeInsert(&tree, value_p);
				break;
			case 'r':
				BinTreeRemove(&tree, value_p);
				break;
			case 'f':
				if (BinTreeSearch(tree, value_p))
					puts("yes");
				else
					puts("no");
				
				free(value_p);
				break;
			case 'p':
				BinTreePrint(tree);
				break;
			case 'q':
				return 0;
				break;
		}
	}
	
	return 0;
}
