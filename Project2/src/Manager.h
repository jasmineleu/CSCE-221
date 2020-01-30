/************************************************
**  File			:   Manager.h
**  Project		: 	CSCE-221 Project 2, Fall 2019
**  Author		: 	Jasmine Leu
**  Date			:   10/23/2019
**  Section		: 	502
**  E-mail 		:		jasmineleu@tamu.edu

** 	This file contains the header file for Manager.h.

************************************************/

#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include "Store.h"
#include "Orders.h"
using namespace std;
class Manager
{
private:
  Store m_store;
  Orders m_orders;

public:
  Manager(string store, string orders);
  ~Manager();
  void createStore(string filename);
  void createOrders(string filename);
  void fillOrders(ofstream& out);
  void printStatus(ofstream& out);
};

#endif
