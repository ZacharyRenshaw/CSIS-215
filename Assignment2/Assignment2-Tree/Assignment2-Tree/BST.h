// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.

// This file includes all of the pieces of the BST implementation

//<BST.h> -- Implements BSTNode.h into a tree
//CSIS 215><D01>
// <Sources>
// https://algorithms.tutorialhorizon.com/double-threaded-binary-tree-complete-implementation/

// Include the node implementation
#include "BSTNode.h"

// Include the dictionary ADT
#include "dictionary.h"
#include <string>

#ifndef BST_H
#define BST_H

using namespace std;

// Binary Search Tree implementation for the Dictionary ADT
template <typename Key, typename E>
class BST : public Dictionary<Key, E> {
private:
	BSTNode<Key, E>* root;   // Root of the BST

	int nodecount;         // Number of nodes in the BST

	// Private "helper" functions
	void clearhelp(BSTNode<Key, E>*);
	BSTNode<Key, E>* inserthelp(BSTNode<Key, E>*,
		const Key&, const E&);
	BSTNode<Key, E>* deletemin(BSTNode<Key, E>*);
	BSTNode<Key, E>* getmin(BSTNode<Key, E>*);
	BSTNode<Key, E>* removehelp(BSTNode<Key, E>*, const Key&);
	E* findhelp(BSTNode<Key, E>*, const Key&) const;
	void printhelp(BSTNode<Key, E>*, int) const;
	void vist(BSTNode<Key, E>*) const;
	void printSpaces(int space) const; // print spaces for formatting print method
	BSTNode<int, string>* findNext(BSTNode<int, string>* node);
	BSTNode<int, string>* findReverse(BSTNode<int, string>* node);

public:
	BST() { root = NULL; nodecount = 0;}  // Constructor

	//Note from Prof Sipantzi -- I've commented out the destructor
	//since you would have to change clearhelp() to make it work with
	//doubly-threaded trees and that is not part of the assignment.
	//~BST() { clearhelp(root); }            // Destructor

	void clear()   // Reinitialize tree
	{
		clearhelp(root); root = NULL; nodecount = 0;
	}

	// Prints the tree in order from least to greatest
	void printInOrder()
	{
		if (root == NULL) cout << "The BST is empty.\n"; // do not run if root is empty
		else
		{
			cout << endl << "REGULAR ORDER:" << endl;
			BSTNode<Key, E> *currentNode = root; // create copies of root
			BSTNode<Key, E> *copy = root;

			// traverse tree in order
			while (currentNode->getIsThreadedRight() == false) // for moving right
			{
				currentNode = currentNode->right();
			}

			while (copy->getIsThreadedLeft() == false) // for moving left
			{
				copy = copy->left();
			}
			cout << copy->element() << endl;

			while (copy->key() != currentNode->key()) // run until it reaches the end
			{
				copy = findNext(copy); // calls findNext function to get next element
				cout << copy->element() << endl;
			}
		}
	}
	
	// Prints the tree in reverse order from greatest to least
	void printReverse()
	{
		if (root == NULL) cout << "The BST is empty.\n"; // do not run if root is empty
		else
		{
			cout << endl << "REVERSE ORDER:" << endl;
			BSTNode<Key, E> *currentNode = root; // create copies of root
			BSTNode<Key, E> *copy = root;

			// traverse tree in reverse order
			while (currentNode->getIsThreadedLeft() == false) // for moving left
			{
				currentNode = currentNode->left();
			}

			while (copy->getIsThreadedRight() == false) // for moving right
			{
				copy = copy->right();
			}
			cout << copy->element() << endl;

			while (copy->key() != currentNode->key()) // run until it reaches the end
			{
				copy = findReverse(copy); // calls findReverse function to get next element
				cout << copy->element() << endl;
			}
		}
	}


	// Insert a record into the tree.
	// k Key value of the record.
	// e The record to insert.
	void insert(const Key& k, const E& e) {
		root = inserthelp(root, k, e);
		nodecount++;
	}

	// Remove a record from the tree.
	// k Key value of record to remove.
	// Return: The record removed, or NULL if there is none.
	E* remove(const Key& k) {
		E* temp = findhelp(root, k);   // First find it
		if (temp != NULL) {
			root = removehelp(root, k);
			nodecount--;
		}
		return temp;
	}
	// Remove and return the root node from the dictionary.
	// Return: The record removed, null if tree is empty.
	E* removeAny() {  // Delete min value
		if (root != NULL) {
			E* temp = new E;
			*temp = root->element();
			root = removehelp(root, root->key());
			nodecount--;
			return temp;
		}
		else return NULL;
	}

	// Return Record with key value k, NULL if none exist.
	// k: The key value to find. */
	// Return some record matching "k".
	// Return true if such exists, false otherwise. If
	// multiple records match "k", return an arbitrary one.
	E* find(const Key& k) const { return findhelp(root, k); }

	// Return the number of records in the dictionary.
	int size() { return nodecount; }

	void print() const { // Print the contents of the BST
		if (root == NULL) cout << "The BST is empty.\n";
		else printhelp(root, 0);
	}

};

// Visit -- prints out root
template <typename Key, typename E>
void BST<Key, E>::vist(BSTNode<Key, E>* r) const {
	cout << "Node - " << r->element() << endl;
}

// Clean up BST by releasing space back free store
template <typename Key, typename E>
void BST<Key, E>::
clearhelp(BSTNode<Key, E>* root) {
	if (root == NULL) return;
	clearhelp(root->left());
	clearhelp(root->right());
	delete root;
}

// Insert a node into the BST, returning the updated tree
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::inserthelp(BSTNode<Key, E>* root, const Key& k, const E& it)
{
	bool left = false; // set true to move left in tree
	bool right = false; // set true to move right in tree
	BSTNode<Key, E> *node = new BSTNode<Key, E>(k, it); // create new node with passed in parameters

	if (root == NULL) // make new node the root if no root
	{
		// set left and right nodes to itself
		node->setLeft(node);
		node->setRight(node);

		// set each thread value to true
		node->setIsThreadedLeft(true);
		node->setIsThreadedRight(true);
		return node; // return tree
	}
	else // if tree has a root:
	{
		int rootValue = root->key();
		while (true) // run until break statement
		{
			if (root->key() > k) // if root key is less than k
			{
				if (root->getIsThreadedLeft() == true) // if the left element is a thread
				{
					// set left to true to insert left
					right = false;
					left = true;
					break; // exit loop
				}
				else
				{
					root = root->left(); // move left
				}
			}
			else
			{
				if (root->getIsThreadedRight() == true) // if the right element if a thread
				{ 
					// set right to true to insert right
					left = false;
					right = true;
					break; // exit loop
				}
				else
				{
					root = root->right(); // move right
				}
			}
		}
		// insert either left or right depending on which value is set
		if (left) // if left is true
		{
			// set all nodes and threads
			node->setLeft(root->left());
			root->setLeft(node); // set left node
			node->setIsThreadedLeft(root->getIsThreadedLeft());
			root->setIsThreadedLeft(false); // left node is not a thread
			node->setRight(root); // set right node
			node->setIsThreadedRight(true); // right node is a thread
		}
		else if (right) // if right is true
		{
			// set all nodes and threads
			node->setRight(root->right());
			root->setRight(node); // set right node
			node->setIsThreadedRight(root->getIsThreadedRight());
			root->setIsThreadedRight(false); // right node is not a thread
			node->setLeft(root); // set left node
			node->setIsThreadedLeft(true); // left node is a thread 
		}

		// update root value back to original because it was shifted in the insertion
		while (root->key() != rootValue) // run until value is correct
		{
			if (k < root->key()) // move right if k is less than root 
			{
				root = root->right();
			}
			else
			{
				root = root->left(); // move left otherwise
			}
		}		
		return root; // return updated tree
	}
}

// Delete the minimum value from the BST, returning the revised BST
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::
getmin(BSTNode<Key, E>* rt) {
	if (rt->left() == NULL)
		return rt;
	else return getmin(rt->left());
}
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::
deletemin(BSTNode<Key, E>* rt) {
	if (rt->left() == NULL) // Found min
		return rt->right();
	else {                      // Continue left
		rt->setLeft(deletemin(rt->left()));
		return rt;
	}
}

// Remove a node with key value k
// Return: The tree with the node removed
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::
removehelp(BSTNode<Key, E>* rt, const Key& k) {
	if (rt == NULL) return NULL;    // k is not in tree
	else if (k < rt->key())
		rt->setLeft(removehelp(rt->left(), k));
	else if (k > rt->key())
		rt->setRight(removehelp(rt->right(), k));
	else {                            // Found: remove it
		BSTNode<Key, E>* temp = rt;
		if (rt->left() == NULL) {     // Only a right child
			rt = rt->right();         //  so point to right
			delete temp;
		}
		else if (rt->right() == NULL) { // Only a left child
			rt = rt->left();          //  so point to left
			delete temp;
		}
		else {                    // Both children are non-empty
			BSTNode<Key, E>* temp = getmin(rt->right());
			rt->setElement(temp->element());
			rt->setKey(temp->key());
			rt->setRight(deletemin(rt->right()));
			delete temp;
		}
	}
	return rt;
}

// Find a node with the given key value
template <typename Key, typename E>
E* BST<Key, E>::findhelp(BSTNode<Key, E>* root,
	const Key& k) const {
	if (root == NULL) return NULL;          // Empty tree
	if (k < root->key())
		return findhelp(root->left(), k);   // Check left
	else if (k > root->key())
		return findhelp(root->right(), k);  // Check right
	else {
		E* temp = new E;
		*temp = root->element();
		return temp;  // Found it
	}
}

// Print out a BST structure
template <typename Key, typename E>
void BST<Key, E>::
printhelp(BSTNode<Key, E>* root, int level) const {
	if (root == NULL) return; // return if no root

	static int levelNum = 5; // stores current indent level
	static BSTNode<int, string> *currentNode = root; // copy of root for left printing
	static BSTNode<int, string> *copy = root; // copy of root for right printing

	// find the left most node to stop at
	while (currentNode->getIsThreadedLeft() == false) // move all the way left
	{
		currentNode = currentNode->left();
	}
	while (currentNode->getIsThreadedRight() == false)  // if applicable, move right
	{
		currentNode = currentNode->right();
		while (currentNode->getIsThreadedLeft() == false) // to go as far left as possible
		{
			currentNode = currentNode->left();
		}
	}
	cout << "Left part of tree:" << endl;
	printSpaces(levelNum); // print indent
	cout << root->key() << endl;

	while (root->key() != currentNode->key()) // stop at left most node
	{
		root = root->left(); // move left for first number
		levelNum--;
		printSpaces(levelNum); // print indent
		cout << root->key() << endl;
		if (root->key() == currentNode->key()) // exit loop here if it reaches the bottom
		{
			break;
		}

		// for traversing the left tree
		while (root->getIsThreadedRight() != true) // move right if right is not a thread
		{
			root = root->right();
			levelNum++;
			printSpaces(levelNum);
			cout << root->key() << endl;
		}

		while (root->getIsThreadedLeft() == true) // move left if left is a thread
		{
			root = root->left();
			levelNum--;
		}
	}

	cout << endl << endl << endl << "Right part of tree:" << endl;
	levelNum = 5; // set indent back to 5
	root = copy; 
	printSpaces(levelNum); // print indent
	cout << root->key() << endl;

	// find the right most node to stop at
	while (copy->getIsThreadedRight() == false) // move all the way right
	{
		copy = copy->right();
	}	
	while (copy->getIsThreadedLeft() == false) // if applicable, move left
	{
		copy = copy->left();
		while (copy->getIsThreadedRight() == false) // to go as far right as possible
		{
			copy = copy->right();
		}
	}

	while (root->key() != copy->key()) // stop at right most node
	{
		root = root->right(); // move right for the first number 
		levelNum++;
		printSpaces(levelNum); // print indent
		cout << root->key() << endl;
		if (root->key() == copy->key()) // exit loop here if it reaches the outer node
		{
			break;
		}

		// for traversing the right tree
		while (root->getIsThreadedLeft() != true) // move left if left is not a thread
		{
			root = root->left();
			levelNum--;
			printSpaces(levelNum);
			cout << root->key() << endl;
		}

		while (root->getIsThreadedRight() == true) // move right if right is a thread
		{ 
			root = root->right();
			levelNum++;
		}
	}

}

// Prints indents for print function
template <typename Key, typename E>
void BST<Key, E>::printSpaces(int space) const
{
	for (int i = 0; i < space; i++) // print "  " for each level of indent passed in
	{
		cout << "  ";
	}
}

// Used by printInOrder to find the next element
template <typename Key, typename E>
BSTNode<int, string>* BST<Key, E>::findNext(BSTNode<int, string>* node)
{
	if (node->getIsThreadedRight() == true) // move right 1 if the right node is a thread
	{
		return node->right();
	}

	node = node->right(); // move right
	while (node->getIsThreadedLeft() != true) // move left until left node is a thread
	{
		node = node->left();
	}
	return node; // return the next number
}

// Used by printReverse to find the next element
template <typename Key, typename E>
BSTNode<int, string>* BST<Key, E>::findReverse(BSTNode<int, string>* node)
{
	if (node->getIsThreadedLeft() == true) // move left 1 if the left node is a thread
	{
		return node->left();
	}

	node = node->left(); // move left
	while (node->getIsThreadedRight() != true) // move right until right node is a thread
	{
		node = node->right();
	}
	return node; // return the next number
}

#endif