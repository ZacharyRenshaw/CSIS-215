/*
* File:   BDictionary.h -- implement a dictionary use an array-based bag
* Author: Prof Terri Sipantzi
*
* You may use this template to implement your Dictionary
*/

//<BDictionary.h> -- Implementation of dictionary
//CSIS 215-<D01>

#ifndef BDICTIONARY_H
#define	BDICTIONARY_H

#include "ABag.h"
#include "dictionaryADT.h"
#include "kvpair.h"

template <typename Key, typename E>
class BDictionary : public Dictionary<Key, E> {
public:
	// constructor
	BDictionary(int cap)
	{
		dictionary = new ABag<KVpair<Key, E>>(cap); // creates dictionary out of bag structure
	}

	// destructor
	~BDictionary()
	{
		dictionary->~ABag(); // uses bag destructor to delete data
	}

	// methods: clear, insert, remove, removeAny, find, size, etc.
	// clears contents of dictionary
	void clear()
	{
		dictionary->emptyBag(); // uses bag emptyBag() to clear all data
	}

	// insert item into dictionary
	bool insert(const Key& k, const E& e)
	{
		KVpair<Key, E> item = KVpair<Key, E>(k, e); // creates item
		return(dictionary->addItem(item)); // adds item to dictionary and returns success value
	}

	// removes item from dictionary
	bool remove(const Key& k, E& rtnVal)
	{
		KVpair<Key, E> item = KVpair<Key, E>(k, rtnVal); // creates item
		bool success = dictionary->remove(item); // removes item
		if (success) // updates item if successful remove
		{
			rtnVal = item.value();
		}
		return success;
	}

	// removes item from the top of the dictionary
	bool removeAny(E& returnValue)
	{
		if (size() <= 0) // returns false if the dictionary is empty
		{
			return false;
		}
		else // removes item if items exist
		{
			KVpair<Key, E> item;
			dictionary->removeTop(item); // removes item and stores value
			returnValue = item.value(); // returns value of item removed
			return true;
		}
	}

	// finds item in dictionary
	bool find(const Key& k, E& returnValue) const
	{
		KVpair<Key, E> item = KVpair<Key, E>(k, returnValue); // creates item
		bool success = dictionary->find(item); // finds item using bag function
		if (success) // return item value if found
		{
			returnValue = item.value();
		}
		return success; // returns success of find
	}

	// returns size of the dictionary
	int size()
	{
		return dictionary->size(); // uses bags size function
	}

private:
	//Pointer to a ABag object.  You'll need to instantiate the bag in your constructor:
	// dictionary = new ABag<KVpair<Key, E>>(size) or something similar depending on how
	// you've implemented your ABag constructor(s).
	//This pointer gives you access to the bag which stores your data and provides the 
	//functions you need to build your dictionary.
	ABag<KVpair<Key, E>>* dictionary;
};


#endif	/* BDICTIONARY_H */

