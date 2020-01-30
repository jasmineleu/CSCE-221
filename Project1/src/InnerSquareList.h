/************************************************
**  File			:   InnerSuqareList.h
**  Project		: 	CSCE-221 Project 1, Fall 2019
**  Author		: 	Jasmine Leu
**  Date			:   10/4/2019
**  Section		: 	502
**  E-mail 		:		jasmineleu@tamu.edu

** 	This file contains the header file for InnerSquareLists.

************************************************/

#ifndef INNERSQUARELIST_H
#define INNERSQUARELIST_H

#define INTNULL -1

#include <iostream>

// Node used in the SquareList
typedef struct tagNode
{
	int value;
	struct tagNode* next;
}Node;

class InnerSquareList
{
private:
	//pointer to the first Node in the inner list
	Node* m_header;

	//pointer to the last node in the inner list
	Node* m_tail;

	//number of the nodes
	size_t m_length;

public:
	Node* getHeader();

	Node* getTail();

	InnerSquareList();

	//initialize an inner list with given data
	InnerSquareList(Node* header, Node* tail, size_t length);

	~InnerSquareList();

	//delete all dynamically allocated nodes
	void clean();

	//data should be at position "pos" after insertion
	void add(int pos, int data);

	//push_front of STL
	void addFirst(int data);

	//insert as the last element
	void addLast(int data);

	//remove node, position starts from 0
	int remove(int pos);

	//return the element at position pos
	int get(int pos) const;

	//change the value at position pos to data
	void set(int pos, int data);

	//total number of nodes in the inner list
	// conducts this in constant time.
	size_t sizeOfThisInnerList() const;

	//find the index of given data, return -1 if not found
	int indexOf(int data) const;

	//merge another inner list to rear of current inner list
	//the second inner list should be empty after merge
	// conducts this in constant time.
	void merge(InnerSquareList &isl);

	//split an inner list at mid point, return the second half
	//the first half should be the same, or one element less thant the
	//second half. This method should take O(t) time, where t is the
	// length of the original inner list
	InnerSquareList split();

	//print of all node values and the last node in O(n)
	//check the sample output for format
	void dump();
};

#endif
