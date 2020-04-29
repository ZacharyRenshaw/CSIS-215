#include "SelfOrderedListADT.h"
#include "llist.h"

//<CountHeuristic.h> -- Implementation of count
//CSIS 215><D01>

#ifndef COUNTHEURISTIC_H
#define	COUNTHEURISTIC_H

template <typename E>
class CountHeuristic : public SelfOrderedListADT<E>, public LList<E> {
public:
	//Constructor
	CountHeuristic() 
	{
		LList<E>* itemList = new LList<E>; // list of items
		LList<int>* freqList = new LList<int>; // list of frequencies
		compares = 0; // for counting compares
	} 
	// Destructor
	~CountHeuristic() {}

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
				// move to the next item
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

		// iterates through lists
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

	// reorders items by count frequency
	void reorder(const E& it, bool found)
	{
		// variables store current frequency and count
		int foundFreq = 0;
		int count = 0;

		// if item is found (otherwise it is added at the end)
		if (found)
		{
			// increase frequency
			foundFreq = freqList.getValue() + 1;

			// iterate through list backwards
			for (int i = size() + 1; i > 0; i--)
			{

				freqList.prev();
				// if item frequency is greater than previous item
				if (foundFreq > freqList.getValue())
				{
					// switch items
					freqList.next();
					freqList.remove();
					freqList.prev();
					freqList.insert(foundFreq);
					itemList.remove();
					itemList.prev();
					itemList.insert(it);
				}
				// if frequency is not greater
				else
				{
					// if this is the first run through the loop
					if (count == 0)
					{
						// insert new frequency
						if(freqList.currPos() != 0)
							freqList.next();
						freqList.remove();
						freqList.insert(foundFreq);
					}
					// move position to start
					itemList.moveToStart();
					freqList.moveToStart();
					return;
				}
				// increment count
				count++;
			}
		}
	}

private:
	LList<E> itemList; // stores items
	LList<int> freqList; // stores frequencies
	int compares; // stores comparisons
};


#endif	/* COUNTHEURISTIC_H */