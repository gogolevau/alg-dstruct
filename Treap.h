#pragma once

typedef struct Node {
	int key;
	int priority;
	struct Node* left;
	struct Node* right;
} Node;

typedef struct PairNode {
	struct Node* right;
	struct Node* left;
} PairNode;

Node* Find(Node* tree, int key);
Node* Merge(Node* tree1, Node* tree2);
PairNode Split(Node* tree, int key);
Node* Insert(Node* tree, int key, int value);
Node* Delete(Node* tree, int key);
void Vacant(Node* tree);