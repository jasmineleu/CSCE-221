/************************************************
**  File			:   Order.h
**  Project		: 	CSCE-221 Project 2, Fall 2019
**  Author		: 	Jasmine Leu
**  Date			:   10/23/2019
**  Section		: 	502
**  E-mail 		:		jasmineleu@tamu.edu

** 	This file contains the header file for Order.h.

************************************************/

#ifndef ORDER_H
#define ORDER_H

#include "Food.h"
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using namespace std;

class Order
{
private:
  string m_sCustomerName;
  bool m_bAcceptsPartialOrder;
  bool m_bOrderCompleted;
  queue <FOOD_TYPE> m_requests;
  queue <Food*> m_filledRequests;

public:
  Order();
  ~Order();
  bool requestsIsEmpty();
  bool filledRequestsIsEmpty();
  void setCustomerName(string name);
  void setAcceptPartial(bool acceptPartial);
  void setOrderComplete(bool orderCompleted);
  bool isAcceptPartial();

  FOOD_TYPE& getNextRequest();
  void addRequestToOrder(FOOD_TYPE food);
  void addFoodToOrder(Food* food);
  Food* popFoodFromOrder();


  void printOrder(ofstream& out);
  void printRequests();

};

#endif
