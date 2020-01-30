/************************************************
**  File			:   SquareList.h
**  Project		: 	CSCE-221 Project 1, Fall 2019
**  Author		: 	Jasmine Leu
**  Date			:   10/4/2019
**  Section		: 	502
**  E-mail 		:		jasmineleu@tamu.edu

** 	This file contains the header file for SquareList.

************************************************/

#ifndef SQUARELIST_H
#define SQUARELIST_H

#include <list>
#include <cmath>
#include "InnerSquareList.h"

class SquareList
{
	//the horizonal list containing all inner lists
	std::list<InnerSquareList> inners;
public:
	SquareList();
	~SquareList();

	//Keep the length of each inner list satisfying the definition of a Square List
	void consolidate();

	//insert
	void addFirst(int data);

	void addLast(int data);

	int removeFirst();

	//insert a value to be at location "pos"
	void add(int pos, int data);

	int remove(int pos);

	int get(int pos);

	void set(int pos, int data);

	//total number of nodes in all inner lists
	int size();

	//Position of first occurence of a value
	int indexOf(int data);

	//Printing out information of Square List for debugging
	void dump();
};

#endif
