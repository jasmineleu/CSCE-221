/************************************************
**  File			:   Calculate.h
**  Project		: 	CSCE-221 Project 4, Fall 2019
**  Author		: 	Jasmine Leu
**  Date			:   12/4/2019
**  Section		: 	502
**  E-mail 		:		jasmineleu@tamu.edu

** 	This file contains the header file for Calculate.h.

************************************************/

#ifndef CALCULATE_H
#define CALCULATE_H

#include <string>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>
#include <vector>
#include <ctype.h>
#include <cmath>

class Calculate
{
private:
  std::ofstream outputFileStream;
  std::vector<std::string> equation;
  std::map <std::string, int> inputPriority = {
    {"+", 1}, {"-", 1},
    {"*", 2}, {"/", 2}, {"%", 2},
    {"^", 5},
    {"(", 6},
  };
  std::map <std::string, int> stackPriority = {
    {"+", 1}, {"-", 1}, {"*", 2},
    {"/", 2}, {"%", 2},
    {"^", 4},
    {"(", 0},
    {"$", -1},
  };

  std::stack<std::string> operator_stack; // holds char symbols
  std::stack<int> priority_stack; // holds priority value of that symbol
  std::stack<double> value_stack; // holds numbers
public:
  // construct that will accept the filename
  Calculate(std::string fileName);
  ~Calculate();

  bool isOperator(std::string str);
  // validates the file
  void readFile(std::string fileName);
  // matches the regular expression
  bool isNum(std::string str);
  // writes results to a file; parameters can vary
  void writeResults();
  // can only push a symbol on the stack if its input priority is greater to what priority is
  // currently at top of the stack. otherwise must pop and process to make priority value lower
  // could use this function in conjunction with stack's push function
  void push();
  // actual calculation is done
  bool popAndProcess();

};

#endif
