/************************************************
**  File			:   Orders.h
**  Project		: 	CSCE-221 Project 2, Fall 2019
**  Author		: 	Jasmine Leu
**  Date			:   10/23/2019
**  Section		: 	502
**  E-mail 		:		jasmineleu@tamu.edu

** 	This file contains the header file for Orders.h.

************************************************/

#ifndef ORDERS_H
#define ORDERS_H

#include "Order.h"
#include <queue>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;

class Orders
{
private:
  queue<Order*> m_ordersUnfilled;
  queue<Order*> m_ordersComplete;
  Order* m_pCurrentOrder;

public:
  Orders();
  ~Orders();
  bool unfilledIsEmpty();
  void addOrder(Order* order);
  void completeOrder();
  Order* getCurrentOrder();
  void loadOrders(string filename);
  void printOrders(ofstream& out);
};

#endif
