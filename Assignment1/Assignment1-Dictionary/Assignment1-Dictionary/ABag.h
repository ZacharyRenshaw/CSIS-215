/*
* File:   ABag.h
* Author: Prof Terri Sipantzi
*
* You may use this template to implement your ABag.
*/

//<ABag.h> -- Implementation of Bag
//CSIS 215-<D01>


#ifndef ABAG_H
#define	ABAG_H

#include "book.h"
#include "bagADT.h"

template <typename E>
class ABag : public Bag<E> {
public:
	// constructor
	ABag(int cap) // stores capacity
	{
		capacity = cap; // sets values
		used = 0;
		data = new E[cap];
	}

	// destructor
	~ABag()
	{
		delete[] data; // deletes items in ABag data
	}

	// bag methods: addItem, remove, operator+=, size, etc.

	// adds item to the top of bag
	bool addItem(const E& item)
	{
		if (used < capacity) // if the bag is not full
		{
			data[used] = item; // add new item and update size
			used++;
			return true;
		}
		else // return false if bag is full
		{
			return false;
		}
	}

	// removes the item from the bag
	bool remove(E& item)
	{
		for (int i = used - 1; i >= 0; i--) // searches starting from top of bag
		{
			if (data[i] == item) // if item found
			{
				item = data[i]; // new item return value
				for (int j = i + 1; j <= used; j++) // shift everything down
				{
					data[i] = data[j];
					i++;
				}
				used--; // decrement bag size
				return true;
			}
		}
		return false; // return false if item not found
	}

	// removes top element from bag
	bool removeTop(E& returnValue)
	{
		if (used <= 0) // return false if bag is empty
		{
			return false;
		}
		else
		{
			returnValue = data[used - 1]; // returns item
			used -= 1; // decrements size to delete item
			return true;
		}
	}

	// finds item and stores it in returnValue
	bool find(E& returnValue) const
	{
		for (int i = used - 1; i >= 0; i--) // searches from top of bag
		{
			if (data[i] == returnValue) // if item is found
			{
				returnValue = data[i]; // reutrn value of item
				return true;
			}
		}
		return false; // return false if not found
	}

	// returns items at top of bag
	bool inspectTop(E& item) const
	{
		if (used <= 0) // returns false if bag is empty
		{
			return false;
		}
		else
		{
			item = data[used - 1]; // updates item with item at top of bag
			return true;
		}
	}

	// clears all bag data
	void emptyBag()
	{
		delete[] data; // deletes data
		used = 0; // resets size
		data = new E[capacity]; // creates new array
	}

	// adds new item to the top of bag
	bool operator+=(const E& addend)
	{
		bool theBool = addItem(addend); // adds item to top
		return theBool;
	}

	// returns size of the bag
	int size() const
	{
		return used;
	}

	// returns largest size of the bag
	int bagCapacity() const
	{
		return capacity;
	}

private:
	E *data;            // an array of items
	int used;           // number of items the data array currently holds
	int capacity;       // the number of items the bag can hold (size of array)
};

#endif	/* ABAG_H */

