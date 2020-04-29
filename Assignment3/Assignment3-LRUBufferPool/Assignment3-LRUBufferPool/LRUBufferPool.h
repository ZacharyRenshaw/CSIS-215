#include <list>
#include "BufferPoolADT.h"
#include "BufferBlock.h"

//<LRUBufferPool.h> -- Creates an implementation of an LRU Buffer Pool off of BufferPoolADT
//CSIS 215><D01>

#ifndef LRUBufferPool_H
#define LURBufferPool_H

class LRUBufferPool : public BufferPoolADT {
public:
	LRUBufferPool() {} // default constructor

	// constructor mainly used
	LRUBufferPool(string filename, int poolSize = 5, int blockSize = 4096)
	{
		char* temp; // for storing input of read function
		temp = new char[blockSize]; // initiate temp

		fstream input; // creates fstream object and opens file
		input.open(filename, fstream::binary | fstream::in);

		// creates the first 5 buffer blocks
		for (int i = 0; i < poolSize; i++)
		{
			input.read(temp, blockSize); // reads file
			BufferBlock block(temp, i, blockSize);
			buffer.push_back(block); // pushes buffer block onto back
			temp = new char[blockSize]; // resets temp
		}
		input.close(); // closes file
	}

	~LRUBufferPool() {} // destructor

	// Copy "sz" bytes from position "pos" of the buffered
	//   storage to "space".
	void getBytes(char* space, int sz, int pos)
	{
		buffer.begin()->getData(pos, sz, space); // reads from pos of size bytes

		int element = floor(pos / BLOCKSIZE); // to determine the block number

		list<BufferBlock>::iterator it; // iterator to iterate over list
		for (it = buffer.begin(); it != buffer.end(); it++)
		{
			if (it->getID() == element) // if element is a match
			{
				BufferBlock copy = *it; // stores a copy of the item
				try {
					buffer.erase(it); // erase item
				}
				catch (...) {}
				buffer.push_front(copy); // push new element onto front
				return; // return function
			}
		}
		
		char* temp;
		temp = new char[BLOCKSIZE];

		buffer.begin()->getData((element+1)*BLOCKSIZE, BLOCKSIZE, temp); // reads data into temp
		BufferBlock newBuffer(temp, element, BLOCKSIZE); // creates new buffer block
		buffer.pop_back(); // deletes last item
		buffer.push_front(newBuffer); // puts new item at front of list
	}

	// Print the order of the buffer blocks using the block id
	//	 numbers.
	void printBufferBlockOrder()
	{
		cout << "My buffer block order from most recently used to LRU is:" << endl;
		list<BufferBlock>::iterator it; // to iterate over list
		for (it = buffer.begin(); it != buffer.end(); it++)
			cout << it->getID() << " "; // print id of each item
		cout << endl << endl;
	}

	// Get the block id number of the least recently used 
	//	 buffer block.
	int getLRUBlockID()
	{
		return buffer.back().getID(); // returns block id
	}

private:
	list<BufferBlock> buffer; // for storing the list of buffer blocks
};

#endif	/* LRUBufferPool_H */