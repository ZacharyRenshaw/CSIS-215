#include <fstream>
#include "BufferBlockADT.h"

//<BufferBlock.h> -- Creates a Buffer Block implementation off of BufferBlockADT
//CSIS 215><D01>

#ifndef BufferBlock_H
#define	BufferBlock_H

class BufferBlock : public BufferblockADT {
public:
	BufferBlock() {} // default constructor

	// mainly used constructor
	BufferBlock(char* data, int id, int sz = 4096) 
	{
		setBlock(data); // sets block
		theSize = sz; // sets the size
		setID(id); // setz the ID
	}

	~BufferBlock() {} // destructor

	//read the block from pos to pos + sz-1 (or to the end of the block)
	void getData(int pos, int sz, char* data)
	{
		fstream input; // creates new fstream object and opens a file
		input.open("mydatafile.txt", fstream::binary | fstream::in);
		input.seekg(pos); // move to pos
		input.read(data, sz); // read to size
		input.close(); // close the file
	}
	

	//setID
	void setID(int id)
	{
		blockID = id; // sets block id
	}

	//getID
	int getID() const
	{
		return blockID; // returns block id
	}

	//getBlocksize
	int getBlocksize() const
	{
		return theSize; // return block size
	}

	//return the block
	char* getBlock() const
	{
		return block; // returns the block data
	}

	//set the block
	void setBlock(char* blk)
	{
		block = blk; // sets the block data
	}

private:
	char* block; // for storing block data
	int theSize; // for storing the byte size
	int blockID; // for storing the block id
};

#endif	/* BufferBlock_H */