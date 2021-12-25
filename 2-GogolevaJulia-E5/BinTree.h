#ifndef GRAF_H
#define GRAF_H

typedef struct BinTreeNode{
	void* value;
	struct BinTreeNode* left;
	struct BinTreeNode* right;
} BinTreeNode;

typedef int(*CompareFunction)(void*, void*);

typedef struct{
	BinTreeNode* head;
	CompareFunction fun;
}BinTree;

void BinTreeInsert(BinTree* tree, void* val);
int BinTreeSearch(BinTree tree, void* val);
void BinTreeRemove(BinTree* tree, void* val);
void BinTreePrint(BinTree tree);

#endif
