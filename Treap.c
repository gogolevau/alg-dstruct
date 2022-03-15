#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Treap.h"


Node* Find(Node* tree, int key) { 
	if (tree == NULL) {
		return NULL;
	}

	if (tree->key == key) {
		return tree;
	}

	if (tree->key > key) {
		Node* newTree = Find(tree->left, key);
		return newTree;
	}
	else {
		Node* newNode = Find(tree->right, key);
		return newNode;
	}
}

Node* Merge(Node* tree1, Node* tree2) { 
	if (tree1 == NULL) {
		return tree2;
	}
	if (tree2 == NULL) {
		return tree1;
	}

	if (tree1->priority > tree2->priority) {
		tree1->right = Merge(tree1->right, tree2);
		return tree1;
	}
	else {
		tree2->left = Merge(tree1, tree2->left);
		return tree2;
	}
}

PairNode Split(Node* tree, int key) {
	if (tree == NULL) {
		PairNode nullTreap = { NULL, NULL };
		return nullTreap;
	}
	else if (key > tree->key) {
		PairNode tmpPair = Split(tree->right, key);
		tree->right = tmpPair.right;
		PairNode newTreap = { tree, tmpPair.left };
		return newTreap;
	}
	else {
		PairNode tmpPair = Split(tree->left, key);
		tree->left = tmpPair.left;
		PairNode newTreap = { tmpPair.right, tree };
		return newTreap;
	}
}

Node* Insert(Node* tree, int key, int value) {
	if (Find(tree, key) != NULL) {
		return tree;
	}

	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL) {
		printf("No memory allocated!");
		return 0;
	}

	if (newNode == NULL) {
		return tree;
	}

	newNode->key = key;
	newNode->priority = value;
	newNode->right = NULL;
	newNode->left = NULL;

	PairNode newPair = Split(tree, key);
	newPair.right = Merge(newPair.right, newNode);

	return Merge(newPair.right, newPair.left);
}

Node* Delete(Node* tree, int key) {
	if (Find(tree, key) == NULL)
		return tree;

	PairNode newPair = Split(tree, key);
	PairNode newTree = Split(newPair.left, key + 1);

	free(newTree.right);

	return Merge(newPair.right, newTree.left);
}

void Vacant(Node* tree) {
	if (tree != NULL) {
		Vacant(tree->left);
		Vacant(tree->right);
		free(tree);
	}
	return;
}

int main(void) {
	char command;
	int value;

	Node* tree = NULL;

	while (fscanf(stdin, "%c %i", &command, &value) > 0) {
		switch (command) {
		case 'a':
			tree = Insert(tree, value, rand());
			break;
		case 'r':
			tree = Delete(tree, value);
			break;
		case 'f':
			if (Find(tree, value))
				printf("yes\n");
			else
				printf("no\n");
			break;
		}
	}
	Vacant(tree);
	return 0;
}