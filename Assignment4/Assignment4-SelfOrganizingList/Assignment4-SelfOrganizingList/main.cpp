#include <iostream>
#include <fstream>
#include "TransposeHeuristic.h"
#include "FrontHeuristic.h"
#include "CountHeuristic.h"

//<main.cpp> -- Main class for testing all heuristics
//CSIS 215><D01>

using namespace std;

int main() {
	cout << "<Zachary Renshaw> -- CSIS 215 Programming Assignment 4 -- Self Organizing List" << endl << endl;
	
	// create count heuristic
	cout << "COUNT HEURISTIC: " << endl;
	CountHeuristic<char>* count = new CountHeuristic<char>();

	// add chars to count
	count->add('A');
	count->add('B');
	count->add('C');
	count->add('D');
	count->add('E');
	count->add('F');
	count->add('G');
	count->add('H');

	// find chars in count
	count->find('F');
	count->find('D');
	count->find('F');
	count->find('G');
	count->find('E');
	count->find('G');
	count->find('F');
	count->find('A');
	count->find('D');
	count->find('F');
	count->find('G');
	count->find('E');
	count->find('H');
	count->find('I');

	// print stats
	cout << "The number of compares is: " << count->getCompares() << endl;
	cout << "My final list structure with frequencies is: " << endl;
	count->printlist();
	cout << "My list size is: " << count->size() << endl << endl;


	// create front heuristic
	cout << "FRONT HEURISTIC: " << endl;
	FrontHeuristic<char>* front = new FrontHeuristic<char>();

	// add chars to front
	front->add('A');
	front->add('B');
	front->add('C');
	front->add('D');
	front->add('E');
	front->add('F');
	front->add('G');
	front->add('H');

	// find chars in front
	front->find('F');
	front->find('D');
	front->find('F');
	front->find('G');
	front->find('E');
	front->find('G');
	front->find('F');
	front->find('A');
	front->find('D');
	front->find('F');
	front->find('G');
	front->find('E');
	front->find('H');
	front->find('I');

	// print stats
	cout << "The number of compares is: " << front->getCompares() << endl;
	cout << "My final list structure with frequencies is: " << endl;
	front->printlist();
	cout << "My list size is: " << front->size() << endl << endl;


	// create transpose heuristic
	cout << "TRANSPOSE HEURISTIC: " << endl;
	TransposeHeuristic<char>* transpose = new TransposeHeuristic<char>();
	
	// add chars to transpose
	transpose->add('A');
	transpose->add('B');
	transpose->add('C');
	transpose->add('D');
	transpose->add('E');
	transpose->add('F');
	transpose->add('G');
	transpose->add('H');

	// find chars in transpose
	transpose->find('F');
	transpose->find('D');
	transpose->find('F');
	transpose->find('G');
	transpose->find('E');
	transpose->find('G');
	transpose->find('F');
	transpose->find('A');
	transpose->find('D');
	transpose->find('F');
	transpose->find('G');
	transpose->find('E');
	transpose->find('H');
	transpose->find('I');

	// print stats
	cout << "The number of compares is: " << transpose->getCompares() << endl;
	cout << "My final list structure with frequencies is: " << endl;
	transpose->printlist();
	cout << "My list size is: " << transpose->size() << endl << endl;
	

	// create count heuristic 2 and open the file
	cout << "COUNT HEURISTIC 2: " << endl;
	CountHeuristic<string>* count2 = new CountHeuristic<string>();
	fstream input; 
	input.open("test.txt", fstream::binary | fstream::in);
	string word;

	// read file word by word
	while (input >> word)
	{
		count2->find(word);
	}
	input.close();

	// print stats
	cout << "The number of compares is: " << count2->getCompares() << endl;
	cout << "My final list structure with frequencies is: " << endl;
	count2->printlist(10);
	cout << "My list size is: " << count2->size() << endl << endl;


	// create front heuristic 2 and open the file
	cout << "FRONT HEURISTIC 2: " << endl;
	FrontHeuristic<string>* front2 = new FrontHeuristic<string>();
	fstream input2;
	input2.open("test.txt", fstream::binary | fstream::in);
	string word2;

	// read file word by word
	while (input2 >> word2)
	{
		front2->find(word2);
	}
	input2.close();

	// print stats
	cout << "The number of compares is: " << front2->getCompares() << endl;
	cout << "My final list structure with frequencies is: " << endl;
	front2->printlist(10);
	cout << "My list size is: " << front2->size() << endl << endl;


	// create transpose heuristic 2 and open the file
	cout << "TRANSPOSE HEURISTIC 2: " << endl;
	TransposeHeuristic<string>* transpose2 = new TransposeHeuristic<string>();
	fstream input3;
	input3.open("test.txt", fstream::binary | fstream::in);
	string word3;

	// read file word by word
	while (input3 >> word3)
	{
		transpose2->find(word3);
	}
	input3.close();

	// print stats
	cout << "The number of compares is: " << transpose2->getCompares() << endl;
	cout << "My final list structure with frequencies is: " << endl;
	transpose2->printlist(10);
	cout << "My list size is: " << transpose2->size() << endl << endl;



	//close program
	cout << endl << endl;
	system("pause");
	return 0;
}