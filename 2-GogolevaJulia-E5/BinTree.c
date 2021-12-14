#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "BinTree.h"

#define BUF_AREA_HEIGH 20
#define BUF_AREA_WIDTH 255

static void BinTreeInsertNode(BinTree* tree, BinTreeNode* new_node){
	
	if (new_node == NULL)
		return;
	
	if (tree == NULL || (*tree) == NULL){
		*tree = new_node;
		return;
	}
	
	BinTreeNode* node = *tree;
	
	while(node != NULL){
		if (new_node->value < node->value){
			if (node->left == NULL){
				node->left = new_node;
				return;
			}
			else{
				node = node->left;
			}
		}
		else if (new_node->value == node->value){
			free(new_node);
			return;
		}
		else{
			if (node->right == NULL){
				node->right = new_node;
				return;
			}
			else{
				node = node->right;
			}
		}
	}
}

void BinTreeInsert(BinTree* tree, int val )
{
	
	BinTreeNode* new_node = (BinTreeNode*)malloc(sizeof(BinTreeNode));
	if (new_node == NULL)
			return;
		
	(new_node)->value = val;
	(new_node)->left = NULL;
	(new_node)->right = NULL;
	
	
	BinTreeInsertNode(tree, new_node);
}


int BinTreeSearch(BinTree tree, int val){
	BinTreeNode* node = tree;
	
	while(node != NULL){
		if (val < node->value){
			node = node->left;
		}
		else if (val == node->value){
			return 1;
		}
		else{
			node = node->right;
		}
	}
	return 0;
}


void BinTreeRemove(BinTree* tree, int val){
	BinTreeNode* node = *tree;
	BinTreeNode* parent = node;
	int leaf_left_flag = 1;
	
	while(node != NULL){
		if (val < node->value){
			parent = node;
			leaf_left_flag = 1;
			node = node->left;
		}
		else if (val == node->value){
			if (node == *tree){
				if ((*tree)->right != NULL){
					node = (*tree)->left;
					(*tree) = (*tree)->right;
					BinTreeInsertNode(tree, node);
				}
				else{
					(*tree) = (*tree)->left;
				}
				return;
			}
			
			if (leaf_left_flag)
				parent->left = NULL;
			else
				parent->right = NULL;
			
			BinTreeInsertNode(tree, node->left);
			BinTreeInsertNode(tree, node->right);
			free(node);
			return;
		}
		else{
			parent = node;
			leaf_left_flag = 0;
			node = node->right;
		}
	}
}

typedef struct{
	int val;
	int subtree_width;
}RecursionReturn;

static int max(int val1, int val2){
	if (val1 > val2)
		return val1;
	return val2;
}

static RecursionReturn _BinTreePrint(BinTreeNode* node, int is_left, int offset, int depth, int max_len_for_subtree_width, char buf[BUF_SIZE][BUF_AREA_WIDTH]) {
	RecursionReturn ret;
	ret.subtree_width = 0;
	
	if (node == NULL){
		ret.val = 0;
		return ret;
	}
	
	char str_val[50] = {0};
	sprintf(str_val, "%d", node->value);
	int str_len = strlen(str_val);
	int max_width = max(str_len, max_len_for_subtree_width);

	RecursionReturn left  = _BinTreePrint(node->left,
									1, offset,
									depth + 2,
									max_len_for_subtree_width,
									buf);
	
	RecursionReturn right = _BinTreePrint(node->right, 0,
									offset + left.val + max_width,
									depth + 2,
									max_len_for_subtree_width,
									buf);

	
	ret.subtree_width += left.subtree_width + right.subtree_width;
	char int_str[25] = {'\0'};
	sprintf(int_str, "<%d>", ret.subtree_width);
	int int_str_len = strlen(int_str);

	if (str_len < int_str_len){
		memcpy(buf[depth] + offset + left.val + (int_str_len - str_len) / 2, str_val, str_len);
		memcpy(buf[depth + 1] + offset + left.val, int_str, int_str_len);
	}
	else{
		memcpy(buf[depth] + offset + left.val, str_val, str_len);
		memcpy(buf[depth + 1] + offset + left.val + (str_len - int_str_len) / 2, int_str, int_str_len);
	}

	if (depth && is_left) {
		for (int i = 0; i < max_width + right.val; i++)
			buf[depth - 1][offset + left.val + max_width / 2 + i] = '-';
		buf[depth - 1][offset + left.val + max_width / 2] = '+';
	}
	else if (depth && !is_left) {
		for (int i = 0; i < left.val + max_width; i++)
			buf[depth - 1][offset - max_width / 2 + i] = '-';
		buf[depth - 1][offset + left.val + max_width / 2] = '+';
	}
	
	ret.subtree_width += str_len;
	ret.val = left.val + max_width + right.val;
	return ret;
}

static int MaxSubtreeWidth(BinTreeNode* node){
	if (node == NULL)
		return 0;
	
	char subtree_string[50] = {0};
	sprintf(subtree_string, "%i",node->value);
	int subtree_width = strlen(subtree_string);
	if (node->left == NULL && node->right == NULL){
		return subtree_width;
	}
	return MaxSubtreeWidth(node->left) + MaxSubtreeWidth(node->right) + subtree_width;
}

void BinTreePrint(BinTree tree){
	char s[BUF_AREA_HEIGH][BUF_AREA_WIDTH];
    for (int i = 0; i < 20; i++){
        sprintf(s[i], "%80s", " ");
	}
	
	char int_str[50];
	sprintf(int_str, "(%d)", MaxSubtreeWidth(tree));
	_BinTreePrint(tree,
										0, 0, 0,
										strlen(int_str),
										s);
	
	
    for (int i = 0; i < 20; i++)
        printf("%s\n", s[i]);
}
