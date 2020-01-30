/************************************************
**  File			:   Int4MMH.h
**  Project		: 	CSCE-221 Project 3, Fall 2019
**  Author		: 	Jasmine Leu
**  Date			:   11/13/2019
**  Section		: 	502
**  E-mail 		:		jasmineleu@tamu.edu

** 	This file contains the header file for Int4MMH.h.

************************************************/

#ifndef INT4MMH_H
#define INT4MMH_H
#pragma once
#include <string>
class Int4MMH
{
private:
  int value;
public:
  Int4MMH() : value(0) {};
  Int4MMH(int value) { this->value = value; };
  ~Int4MMH() {};

  friend bool operator< (const Int4MMH &a, const Int4MMH &b) {
    return (a.value < b.value);
  };
  friend bool operator<= (const Int4MMH &a, const Int4MMH &b) {
    return (a.value <= b.value);
  };

  friend bool operator> (const Int4MMH &a, const Int4MMH &b) {
    return (a.value > b.value);
  };

  friend bool operator>= (const Int4MMH &a, const Int4MMH &b) {
    return (a.value >= b.value);
  };

  friend bool operator== (const Int4MMH &a, const Int4MMH &b) {
    return (a.value == b.value);
  };

  friend std::ostream& operator<<(std::ostream& os, const Int4MMH &a) {
    os << std::to_string(a.value);
    return os;
  };
};

#endif
