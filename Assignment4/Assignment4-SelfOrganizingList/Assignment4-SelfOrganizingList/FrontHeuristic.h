#include "llist.h"
#include "SelfOrderedListADT.h"
#include "list.h"

//<FrontHeuristic.h> -- Implementation of front
//CSIS 215><D01>

#ifndef FrontHeuristic_H
#define	FrontHeuristic_H

template <typename E>
class FrontHeuristic : public SelfOrderedListADT<E>, public LList<E> {
public:
	//Constructor
	FrontHeuristic() 
	{
		LList<E>* itemList = new LList<E>; // list of items
		LList<int>* freqList = new LList<int>; // list of frequencies
		compares = 0; // for counting compares
	}
	// Destructor
	~FrontHeuristic() {}

	// finds the item or adds new item
	bool find(const E& it)
	{
		// move lists to start
		itemList.moveToStart();
		freqList.moveToStart();

		// iterates through list
		for (int i = 0; i < size(); i++)
		{
			compares++;

			// if item is found
			if (itemList.getValue() == it)
			{
				// reorder list and return
				reorder(it, true);
				return true;
			}
			// otherwise
			else
			{
				// move to next item in list
				itemList.next();
				freqList.next();
				continue;
			}
		}
		// if item is not found, add new item and reorder
		add(it);
		reorder(it, false);
		return false;
	}

	//Add new 'it' to the list
	void add(const E& it)
	{
		// appends item and frequency
		itemList.append(it);
		freqList.append(0);
	}

	//Returns the number of accumulated compares
	int getCompares() const
	{
		return compares;
	}

	//Returns the size of the list
	int size() const      
	{
		return itemList.length();
	}

	// prints the entire list
	void printlist()
	{
		// move lists to start
		itemList.moveToStart();
		freqList.moveToStart();

		// iterates through list
		for (int i = 0; i < size(); i++)
		{
			// prints item and moves to next item
			cout << itemList.getValue() << "-" << freqList.getValue() << " ";
			itemList.next();
			freqList.next();
		}
		cout << endl;
	}

	// prints n items from list
	void printlist(int n)
	{
		// move lists to start
		itemList.moveToStart();
		freqList.moveToStart();

		// iterates through lists
		for (int i = 0; i < n; i++)
		{
			// prints item and moves to next item
			cout << itemList.getValue() << "-" << freqList.getValue() << " ";
			itemList.next();
			freqList.next();
		}
		cout << endl;
	}

	// reorders items by moving to the front
	void reorder(const E& it, bool found)
	{
		int foundFreq = 0;
		// if item is found
		if (found)
		{
			// insert frequency + 1 at start
			int foundFreq;
			foundFreq = freqList.getValue();
			freqList.remove();
			freqList.moveToStart();
			freqList.insert(foundFreq + 1);
		}
		// if not found
		else
		{
			// insert 0 frequency at start
			freqList.remove();
			freqList.moveToStart();
			freqList.insert(foundFreq);
		}

		// remove item and insert at start
		itemList.remove();
		itemList.moveToStart();
		itemList.insert(it);
	}

private:
	LList<E> itemList; // stores items
	LList<int> freqList; // stores frequencies
	int compares;  // stores comparisons
};


#endif	/* FrontHeuristic_H */