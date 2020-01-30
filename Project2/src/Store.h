/************************************************
**  File			:   Store.h
**  Project		: 	CSCE-221 Project 2, Fall 2019
**  Author		: 	Jasmine Leu
**  Date			:   10/23/2019
**  Section		: 	502
**  E-mail 		:		jasmineleu@tamu.edu

** 	This file contains the header file for Store.h.

************************************************/

#ifndef STORE_H
#define STORE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <string>
#include "Food.h"
using namespace std;

class Store
{
private:
  vector< stack<Food*> > m_bins;
public:
  Store();
  ~Store();
  void addFood(Food* food);
  Food* getFoodByType(FOOD_TYPE type);
  Food* popFoodByType(FOOD_TYPE type);
  void stockStore(string filename);
  void printStore(ofstream& out);
  void printStack(ofstream& out, stack<Food*> const& oldStack);
};

#endif
