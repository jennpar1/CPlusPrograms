//Jennifer Parnell
//CSC 231
//Project 3
//Using Binary Tree

// Code based on http://www.cplusplus.com/forum/beginner/131457/
// Demonstrates tree traversals in a binary tree.

#include <iostream>
#include <queue>
#include <string>
#include <conio.h>
#include <fstream>
#include <ctime>
#include "BinaryTree.h"
#include "Word.h"

using namespace std;

void pressAnyKey();

// Node class
//class Node	// Node.h
//{
//	// Word word;
//	string key;
//	Node* left;
//	Node* right;
//	friend class BinaryTree;
//public:
//	Node() { key = "-1"; left = NULL; right = NULL; };
//};

// Tree class
//class BinaryTree	//Tree.h
//{
//	Node* root;
//public:
//	BinaryTree();
//	~BinaryTree();
//	Node* Root() { return root; };
//	void addNode(string theKey);
//	void levelOrder(Node* n);
//	void InOrder(Node*);
//	void PostOrder(Node*);
//	void Preorder(Node* node);
//	void BinaryTree::PostOrder();
//private:
//	void addNode(string theKey, Node* leaf);
//	void freeNode(Node* leaf);
//
//};

// Constructor
BinaryTree::BinaryTree()	//Tree.cpp
{
	root = NULL;
}

// Destructor.
BinaryTree::~BinaryTree()
{
	freeNode(root);
}

// Free the node.
// What kind of traversal is this? Post-order.
void BinaryTree::freeNode(Node* leaf)
{
	if (leaf != NULL)
	{
		freeNode(leaf->left);
		freeNode(leaf->right);
		delete leaf;
	}
}

// Add a node.
void BinaryTree::addNode(Word theKey)
{
	// No elements. Add to the root position.
	if (root == NULL)
	{
		//cout << "Add root node ... " << theKey.print() << endl;
		Node* n = new Node();
		n->key = theKey;
		root = n;
	} 
	else // Otherwise traverse to the correct position.
	{
		//cout << "Add new node ... " << theKey.print() << endl;
		addNode(theKey, root);
	}
}

// Add a node using recursion.
void BinaryTree::addNode(Word theKey, Node* leaf)
{

	if (theKey.getWord() <= leaf->key.getWord()) // If less, go left.
	{
		if (leaf->left != NULL)	// Keep searching recursively until empty node position.
		{
			addNode(theKey, leaf->left);
		}
		else							// Add node into empty correct position.
		{
			Node* n = new Node();
			n->key = theKey;
			leaf->left = n;
		}
	}
	else
	{
		if (leaf->right != NULL)	// Keep searching recursively until empty node position.
		{
			addNode(theKey, leaf->right);
		}
		else						// Add node into empty correct position.
		{
			Node* n = new Node();
			n->key= theKey;
			leaf->right = n;
		}
	}
}

// Print the tree level-order assisted by queue
void BinaryTree::levelOrder(Node* n)
{
	// Create a queue
	queue<Node*> q;

	// Push the root
	q.push(n);

	while (!q.empty())
	{
		// Dequeue a node from front
		Node *node = q.front();
		cout << node->key.print() << endl;

		// Enqueue the left children
		if (node->left != NULL)
		{
			q.push(node->left);
		}

		// Enqueue the right children
		if (node->right != NULL)
		{
			q.push(node->right);
		}

		// Pop the visited node
		q.pop();
	}
}

void BinaryTree::preOrder(Node* node)			// example to call myTree.PreOrder(myTree.root);
{										// PreOrder couts parents before their children
	if (node)							//
	{
		cout << node->key.print() << endl;
		preOrder(node->left);
		preOrder(node->right);
	}
}

void BinaryTree::inOrder(Node* node)
{
	if (node != NULL)
	{
		inOrder(node->left);
		cout << node->key.print() << endl;
		inOrder(node->right);
	}
}

void BinaryTree::postOrder(Node* node)		// PostOrder couts children first
{										// Helpful when deleting because it starts at the leaves and works it way up
	if (node != NULL)
	{
		postOrder(node->left);
		postOrder(node->right);
		cout << node->key.print() << endl;
	}
}

Node* BinaryTree::findMin(Node* root)
{
	while (root->left != NULL) root = root->left;
	return root;
}

Node* BinaryTree::deleteNode(Node* root, string fword)
{
	if (root == NULL) return root;
	else if (fword < root->key.getWord()) root->left = deleteNode(root->left, fword);
	else if (fword > root->key.getWord()) root->right = deleteNode(root->right, fword);
	// Wohoo... I found you, Get ready to be deleted	
	else 
	{
		// Case 1:  No child
		if (root->left == NULL && root->right == NULL) 
		{
			delete root;
			root = NULL;
		}
		//Case 2: One child 
		else if (root->left == NULL) 
		{
			struct Node *temp = root;
			root = root->right;
			delete temp;
		}
		else if (root->right == NULL) 
		{
			struct Node *temp = root;
			root = root->left;
			delete temp;
		}
		// case 3: 2 children
		else 
		{
			struct Node *temp = findMin(root->right);
			root->key = temp->key;
			root->right = deleteNode(root->right, temp->key.print());

			// Find parent and save as parentOfTarget. 
			// Set leftChild to true or false appropriately.
			// Find leftMax and parentOfLeftMax.		
			// Make leftMax child of parentOfTarget.
			// Set leftMax node pointers to equal target's node pointers.
			// Delete target.
			// Set parentOfLeftMax's right to NULL.
			// Much more easily done with parent node. :-)
		}
	}
	return root;
}

//To search an element in BST, returns true if element is found
bool BinaryTree::search(Node* root, string fword) 
{
	if (root == NULL) 
	{
		cout << "Word could not be located." << endl;
		return false;
	}
	else if (root->key.getWord() == fword) 
	{
		cout << root->key.print() << endl;
		return true;
	}
	else if (fword <= root->key.getWord()) 
	{
		return search(root->left, fword);
	}
	else 
	{
		return search(root->right, fword);
	}
}

void BinaryTree::editNode(Node* root, string fword)
{
	if (root == NULL)
	{
		cout << "Word could not be located to edit" << endl;
	}
	else if (root->key.getWord() == fword)
	{
		char choice;
		cout << root->key.print() << endl;
		cout << "Is this the word or meaning you want to edit? Y/N " << endl;
		cin >> choice;
		if (choice == 'Y' || 'y')
		{
			int num;
			cout << "Press 1 to change word or 2 to change meaning." << endl;
			cin >> num;
			switch (num)
			{
			case 1: 
			{
				string changeWord;
				cout << "Enter change to word: " << endl;
				cin >> changeWord;
				root->key.setWord(changeWord);
				break;
			}
			case 2:
			{
				string changeMean;
				cout << "Enter change to meaning: " << endl;
				cin >> changeMean;
				root->key.setMeaning(changeMean);
				break;
			}
			}
		}
		else if (choice == 'N'||"n")
		{
			editNode(root, fword);
		}
		else
		{
			cout << "Did not understand input. " << endl;
		}
	}
	else if (fword <= root->key.getWord())
	{
		editNode(root->left, fword);
	}
	else 
	{
		editNode(root->right, fword);
	}
}

int choice = 0;
void BinaryTree::flashcardsInOrder(Node* node)
{
	//int choice;
	if (node)	
	{
		flashcardsInOrder(node->left);
		cout << node->key.getWord() << endl;
		pressAnyKey();
		cout << node->key.getMeaning() << endl;
		pressAnyKey();
		flashcardsInOrder(node->right);
	}
	
}


void BinaryTree::flashcardsPreOrder(Node* node)
{
	if (node)
	{
		cout << node->key.getWord() << endl;
		cout << "Press any key to show meaning. " << endl;
		_getch();
		cout << node->key.getMeaning() << endl;
		cout << "Press any key to show next word. " << endl;
		_getch();
		preOrder(node->left);
		preOrder(node->right);
		
		
	}
}

void BinaryTree::flashcardsPostOrder(Node* node)		// PostOrder couts children first
{										// Helpful when deleting because it starts at the leaves and works it way up
	if (node != NULL)
	{
		flashcardsPostOrder(node->left);
		flashcardsPostOrder(node->right);
		cout << node->key.getWord() << endl;
		cout << "Press any key to show meaning. " << endl;
		_getch();
		cout << node->key.getMeaning() << endl;
		cout << "Press any key to show next word. " << endl;
		_getch();
	}
}

void BinaryTree::flashcardsRandom(Node* node)
{
	
}

int BinaryTree::randomNumber()
{
	srand((unsigned int)time(NULL)); //activates the generator
	int a = rand() % 3;
	return a;
}

void BinaryTree::randomTraversal(Node* n)
{
	queue<Node*> q;

	// Push the root
	q.push(n);

	while (!q.empty())
	{
		// Dequeue a node from front
		Node *node = q.front();
		cout << node->key.print() << endl;

		// Enqueue the left children
		if (node->left != NULL)
		{
			q.push(node->left);
		}

		// Enqueue the right children
		if (node->right != NULL)
		{
			q.push(node->right);
		}
		
		// Pop the visited node
		q.pop();
	}

}

void BinaryTree::writeTraversal(Node* node, ofstream &wordTextFile)
{
	if (node)
	{
		/*if (!root)
		{
			wordTextFile << endl;
		}*/
		wordTextFile << node->key.print() << endl;
		writeTraversal(node->left, wordTextFile);
		writeTraversal(node->right, wordTextFile);

	}
}

//void BinaryTree::postOrder()		// Set a parameter
//{
//	postOrder(root);
//}

// Test main program
//int main()
//{
//	BinaryTree myTree;
//	myTree.addNode("Q");
//
//	BinaryTree* tree = new BinaryTree();
//	tree->addNode("F");
//	tree->addNode("E");
//	tree->addNode("K");
//	tree->addNode("J");
//	tree->addNode("L");
//	tree->addNode("B");
//	tree->addNode("A");
//	tree->addNode("H");
//	tree->addNode("I");
//	tree->addNode("G");
//	tree->addNode("C");
//	tree->addNode("D");
//
//	cout << "\nLevel order traversal" << endl;
//	tree->levelOrder(tree->Root());
//	cout << endl;
//
//	cout << "\nPre order traversal" << endl;
//	tree->Preorder(tree->Root());
//	cout << endl;
//
//	cout << "\nIn order traversal" << endl;
//	tree->InOrder(tree->Root());
//	cout << endl;
//
//	cout << "\nPost order traversal" << endl;
//	tree->PostOrder(tree->Root());
//	tree->PostOrder();
//	cout << endl;
//
//	system("pause");
//
//	delete tree;
//	return 0;
