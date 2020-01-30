/************************************************
**  File			:   CensusCity.h
**  Project		: 	CSCE-221 Project 3, Fall 2019
**  Author		: 	Jasmine Leu
**  Date			:   11/13/2019
**  Section		: 	502
**  E-mail 		:		jasmineleu@tamu.edu

** 	This file contains the header file for CensusCity.h.

************************************************/

#ifndef CENSUSCITY_H
#define CENSUSCITY_H
#pragma once
#include <string>

class CensusCity
{
	std::string city;
	std::string state;
	int census2010;
	int estimate2011;
	bool use2011;

public:
	CensusCity() :city(""), state(""), census2010(0), estimate2011(0), use2011(false) {};
	CensusCity(std::string aCity, std::string aState, int n1, int n2, bool tf) :city(aCity), state(aState), census2010(n1), estimate2011(n2), use2011(tf) {};
	~CensusCity() {};

	friend bool operator< (const CensusCity &a, const CensusCity &b) {
    return (a.getValue() < b.getValue());
  };
  friend bool operator<= (const CensusCity &a, const CensusCity &b) {
    return (a.getValue() <= b.getValue());
  };

  friend bool operator> (const CensusCity &a, const CensusCity &b) {
    return (a.getValue() > b.getValue());
  };

  friend bool operator>= (const CensusCity &a, const CensusCity &b) {
    return (a.getValue() >= b.getValue());
  };

  friend bool operator== (const CensusCity &a, const CensusCity &b) {
    return (a.getValue() == b.getValue());
  };

  int getValue() const {
		return ((use2011)? estimate2011:census2010);
	};

	friend std::ostream& operator<<(std::ostream& os, const CensusCity &a) {
		os << a.city + ", " + a.state + " (" + std::to_string(a.census2010) + ", " + std::to_string(a.estimate2011) + ")";
		return os;
	};
	std::string  toString() { return city + ", " + state + " (" + std::to_string(census2010) + ", " + std::to_string(estimate2011) + ")"; }

	// friend int compare(const CensusCity& c1, const CensusCity& c2);
};


// int compare(const CensusCity& c1, const CensusCity& c2)
// {
// 	if (c1.use2011)
// 	{
// 		if (c1.estimate2011 < c2.estimate2011)
// 			return -1;
// 		if (c1.estimate2011 > c2.estimate2011)
// 			return 1;
// 		return 0;
// 	}
// 	else {
// 		if (c1.census2010 < c2.census2010)
// 			return -1;
// 		if (c1.census2010 > c2.census2010)
// 			return 1;
// 		return 0;
// 	}
// }

#endif
