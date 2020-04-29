//<doubleTreeDriver.cpp> -- Tests the double threaded binary tree
//CSIS 215><D01>
// <Sources>
// https://algorithms.tutorialhorizon.com/double-threaded-binary-tree-complete-implementation/

#include <string>
#include "BST.h"

using namespace std;

void PauseScreen(); //Used to pause screen output

int main(int argc, char** argv) {
	cout << "<Zachary Renshaw> -- CSIS 215 Programming Assignment 2 -- Double Threaded Binary Tree" << endl << endl;
	
	BST<int, string> newTree; // create new double threaded binary tree

	// insert all 13 items into the tree
	newTree.insert(77, "seventy-seven"); 
	newTree.insert(70, "seventy");
	newTree.insert(75, "seventy-five");
	newTree.insert(66, "sixty-six");
	newTree.insert(79, "seventy-nine");
	newTree.insert(68, "sixty-eight");
	newTree.insert(67, "sixty-seven");
	newTree.insert(69, "sixty-nine");
	newTree.insert(90, "ninety");
	newTree.insert(85, "eighty-five");
	newTree.insert(83, "eighty-three");
	newTree.insert(87, "eighty-seven");
	newTree.insert(65, "sixty-five");

	// print size of the tree
	cout << "TEST INSERTHELP FUNCtION:" << endl;
	cout << "The size after inserts is " << newTree.size() << endl << endl;

	cout << "TEST IN ORDER FUNCTION:";
	newTree.printInOrder(); // print tree in order
	cout << endl;

	cout << "TEST REVERSE FUNCTION:";
	newTree.printReverse(); // print tree in reverse
	cout << endl;

	cout << "TEST PRINTHELP FUNCTION:" << endl;
	newTree.print(); // print structure of tree

	PauseScreen();
}

//Used to pause the screen wherever desired
void PauseScreen()
{
	char ch;
	cout << "\nPress the Enter key to continue ... ";
	cin.get(ch);
}