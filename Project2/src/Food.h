/************************************************
**  File			:   Food.h
**  Project		: 	CSCE-221 Project 2, Fall 2019
**  Author		: 	Jasmine Leu
**  Date			:   10/23/2019
**  Section		: 	502
**  E-mail 		:		jasmineleu@tamu.edu

** 	This file contains the header file for Food.h.

************************************************/

#ifndef FOOD_H
#define FOOD_H
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

enum FOOD_TYPE {Meat, Fruit, Vegetable, Starch, Sweet};

class Food
{
private:
  string m_sName;
  FOOD_TYPE m_eType;
  double m_dCost;

public:
  Food();
  ~Food();
  Food(string name, FOOD_TYPE type, double cost);
  FOOD_TYPE getType();
  double getCost();
  void printFood(ofstream& out);
};

#endif
