//Jennifer Parnell
//CSC 231
//Project 3
//Using Binary Tree

#include <iostream>
#include <string>
#include "Node.h"

using namespace std;

#ifndef BinaryTree_H
#define BinaryTree_H

class BinaryTree
{
	Node* root;
public:
	BinaryTree();
	~BinaryTree();
	Node* Root() { return root; };
	void addNode(Word theWord);
	void levelOrder(Node* node);
	void inOrder(Node* node);
	void postOrder(Node* node);
	Node * findMin(Node * root);
	void preOrder(Node*node);
	Node* deleteNode(Node* root, string fword);
	bool search(Node * root, string key);
	void editNode(Node * node, string fword);
	void flashcardsInOrder(Node * node);
	void cardsInOrder(Node * node, int option);
	void flashcardsPreOrder(Node * node);
	void flashcardsPostOrder(Node * node);
	void flashcardsRandom(Node * node);
	int randomNumber();
	void randomTraversal(Node * node);
	void writeTraversal(Node * node, ofstream &wordTextFile);

private:
	void addNode(Word key, Node* node);
	void freeNode(Node* node);
};

#endif // !BinaryTree_h
