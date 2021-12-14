#pragma warning (disable:4996)
#define _CRT_SECURE_NO_WORNINGS

#include <stdlib.h>
#include <stdio.h>
#include "BinTree.h"


int main(){
	char command;
	int value;
	
	BinTree tree = NULL;

	while (scanf("%c", &command) >= 1){
		if (command != 'p' && command != 'q')
			scanf("%i", &value);
		switch(command){
			case 'a':
				BinTreeInsert(&tree, value);
				break;
			case 'r':
				BinTreeRemove(&tree, value);
				break;
			case 'f':
				if (BinTreeSearch(tree, value))
					puts("yes");
				else
					puts("no");
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
