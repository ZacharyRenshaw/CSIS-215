/*
* File:   bagtestmain.cpp
* Author: Prof Sipantzi -- CSIS 215 -- Programming Assignment 1 -- Bag Dictionary
*
* Created on July 14, 2012, 11:45 AM
* Updated pointers to smart pointers in ABag and BDictionary on 12/14/2018
*/

//<bagtestmain.cpp> -- Tests the bag and dictionaries
//CSIS 215><D01>


#include <string>
#include <sstream>
#include "ABag.h"
#include "BDictionary.h"

using namespace std;

const size_t DICTIONARY_SIZE = 20;

void PauseScreen(); //Used to pause screen output

/*
* Tests BDictionary with int and string objects only.
*/
int main(int argc, char** argv) {
	cout << "<Zachary Renshaw> -- CSIS 215 Programming Assignment 1 -- Bag Dictionary" << endl << endl;

	BDictionary<int, string> myIntStrDict(DICTIONARY_SIZE);
	BDictionary<string, int> myStrIntDict(DICTIONARY_SIZE);

	// myIntStrDict tests
	// INSERT: myIntStrDict
	cout << "Testing dictionary with <int, string> KV Pair\n";
	for (int i = 1; i <= DICTIONARY_SIZE; i++) {
		stringstream sn;
		sn << "Beth " << i * 10;
		myIntStrDict.insert(i * 10, sn.str());
	}
	cout << "INSERT: Size of myIntStrDict is " << myIntStrDict.size() << endl;

	// REMOVEANY: myIntStrDict
	string strData;
	if (myIntStrDict.removeAny(strData) == true) {
		cout << "REMOVEANY: My string data is " << strData << endl;
	}
	else {
		cout << "RemoveAny() failed -- dictionary is empty.\n";
	}
	cout << "Size of myIntStrDict is " << myIntStrDict.size() << "\n";

	// FIND: test for myIntStrDict.find
	int intKey = 40;
	if (myIntStrDict.find(intKey, strData) == true) {
		cout << "FIND: My data at key==" << intKey << " is: " << strData << "\n";
		cout << "Size of myIntStrDict is " << myIntStrDict.size() << "\n";
	}
	else {
		cout << "Could not find a record at " << intKey << "\n";
	}

	// REMOVE: myIntStrDict
	intKey = 60;
	if (myIntStrDict.remove(intKey, strData) == true) {
		cout << "REMOVE: Removed key " << intKey << " which was " << strData << "\n";
	}
	else {
		cout << "Could not find key " << intKey << "\n";
	}
	cout << "Size of my dictionary is " << myIntStrDict.size() << "\n";

	// CLEAR: myIntStrDict
	myIntStrDict.clear();
	cout << "CLEAR: Size of myIntStrDict is " << myIntStrDict.size() << "\n\n";
	/* end myIntStrDict tests ---------------------------------------------*/

	// myStrIntDict tests
	// INSERT: myStrIntDict
	cout << "Testing dictionary with <string, int> KV Pair\n";
	myStrIntDict.insert("Terri", 57);
	myStrIntDict.insert("Beth", 53);
	myStrIntDict.insert("Jeremy", 19);
	myStrIntDict.insert("Nathan", 17);
	myStrIntDict.insert("Zipper", 2);
	myStrIntDict.insert("Button", 1);
	myStrIntDict.insert("Kiwi", 7);
	myStrIntDict.insert("Masoala", 10);

	cout << "INSERT: Size of myStrIntDict is " << myStrIntDict.size() << endl;

	// REMOVEANY: myStrIntDict
	int intData;
	if (myStrIntDict.removeAny(intData) == true) {
		cout << "REMOVEANY: My int data is " << intData << endl;
	}
	else {
		cout << "RemoveAny() failed -- dictionary is empty.\n";
	}
	cout << "Size of myIntStrDict is " << myStrIntDict.size() << "\n";

	// FIND: myStrIntDict.find
	string strKey = "Kiwi";
	if (myStrIntDict.find(strKey, intData) == true) {
		cout << "FIND: " << strKey << "\'s age is " << intData << endl;
		cout << "Size of myStrIntDict is " << myStrIntDict.size() << "\n";
	}
	else {
		cout << "Could not find a record at " << strKey << "\n";
	}

	// REMOVE: myStrIntDict
	strKey = "Button";
	if (myStrIntDict.remove(strKey, intData) == true) {
		cout << "REMOVE: Removed key " << strKey << " which was " << intData << "\n";
	}
	else {
		cout << "Could not find key " << strKey << "\n";
	}
	cout << "Size of my dictionary is " << myStrIntDict.size() << "\n";

	// CLEAR: myStrIntDict
	myStrIntDict.clear();
	cout << "CLEAR: Size of myStrIntDict is " << myStrIntDict.size() << "\n\n";

	/* end myStrIntDict tests ---------------------------------------------*/

	/* Demonstrate any Bag functions that were not used/demonstrated in the implemention
	of your BDictionary and ABag using a Bag of KVpairs<int, string>. */

	cout << endl << "Bag Tests:" << endl;
	// create new bag
	ABag<KVpair<int, string>> myBag(10); //Used to test bag functions not previously demonstrated
	// insert items
	myBag.addItem(KVpair<int, string>(1, "hello"));
	myBag.addItem(KVpair<int, string>(2, "hi"));
	myBag.addItem(KVpair<int, string>(3, "test"));

	// test size and capacity functions
	cout << "Capacity is " << myBag.bagCapacity() << endl;
	cout << "Size is " << myBag.size() << endl;

	// test inspect top
	KVpair<int, string> test;
	myBag.inspectTop(test);
	cout << "INSPECT TOP: " << test.key() << " " << test.value() << endl;

	// empty bag
	test = KVpair<int, string>(1, "hello");
	myBag.emptyBag();
	cout << "Size after empty is " << myBag.size() << endl;

	// testing += function
	test = KVpair<int, string>(4, "new value");
	cout << "TESTING += FUNCTION: ";
	myBag += test;
	cout << "New size is " << myBag.size() << endl;

	// inspect top
	myBag.inspectTop(test);
	cout << "INSPECT TOP: " << test.key() << " " << test.value() << endl;

	PauseScreen();

	return 0;
}

//Used to pause the screen wherever desired
void PauseScreen()
{
	char ch;
	cout << "\nPress the Enter key to continue ... ";
	cin.get(ch);
}