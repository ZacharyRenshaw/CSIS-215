// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.

//<BSTNode.h> -- Create node template for BST
//CSIS 215><D01>
// <Sources>
// https://algorithms.tutorialhorizon.com/double-threaded-binary-tree-complete-implementation/

// This is the file to include for access to the complete binary node
// template implementation

#include "book.h"
#include "BinNode.h"

#ifndef BSTNODE_H
#define BSTNODE_H

// Simple binary tree node implementation
template <typename Key, typename E>
class BSTNode : public BinNode<E> {
private:
	Key k;                  // The node's key
	E it;                   // The node's value
	BSTNode* lc;            // Pointer to left child
	BSTNode* rc;            // Pointer to right child
	bool isThreadedLeft;	// displays whether left child is threaded or not
	bool isThreadedRight;   // displays whether right child is threaded or not

public:
	// Two constructors -- with and without initial values
	BSTNode() { lc = rc = NULL; }
	BSTNode(Key K, E e, BSTNode* l = NULL, BSTNode* r = NULL)
	{
		k = K; it = e; lc = l; rc = r;
	}
	~BSTNode() {}             // Destructor

	// isThreaded setters/getters
	bool getIsThreadedLeft() {return isThreadedLeft;}			 // return left thread
	void setIsThreadedLeft(bool set) { isThreadedLeft = set; }   // set left thread
	bool getIsThreadedRight() {return isThreadedRight;}			 // return right thread
	void setIsThreadedRight(bool set) { isThreadedRight = set; } // set right thread

	// Functions to set and return the value and key
	E& element() { return it; }
	void setElement(const E& e) { it = e; }
	Key& key() { return k; }
	void setKey(const Key& K) { k = K; }

	// Functions to set and return the children
	inline BSTNode* left() const { return lc; }
	void setLeft(BinNode<E>* b) { lc = (BSTNode*)b; }
	inline BSTNode* right() const { return rc; }
	void setRight(BinNode<E>* b) { rc = (BSTNode*)b; }

	// Return true if it is a leaf, false otherwise
	bool isLeaf() { return (lc == NULL) && (rc == NULL); }
};

#endif