#ifndef GRAF_H
#define GRAF_H

typedef struct BinTreeNode{
	int value;
	struct BinTreeNode* left;
	struct BinTreeNode* right;
} BinTreeNode;

typedef BinTreeNode* BinTree;

void BinTreeInsert(BinTree* tree, int val );
int BinTreeSearch(BinTree tree, int val);
void BinTreeRemove(BinTree* tree, int val);
void BinTreePrint(BinTree tree);

#endif
