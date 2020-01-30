/************************************************
**  File			:   SquareList.cpp
**  Project		: 	CSCE-221 Project 1, Fall 2019
**  Author		: 	Jasmine Leu
**  Date			:   10/4/2019
**  Section		: 	502
**  E-mail 		:		jasmineleu@tamu.edu

** 	This file contains the cpp file for SquareList.

************************************************/

#include <cmath>
#include "SquareList.h"
using namespace std;


SquareList::SquareList() : inners() {}
SquareList::~SquareList() {
  list<InnerSquareList>::iterator it;
  for(it = inners.begin(); it!=inners.end(); ++it)
  {
    it->clean();
  }
}

//Keep the length of each inner list satisfying the definition of a Square List
void SquareList::consolidate()
{
  list<InnerSquareList>::iterator it;
  list<InnerSquareList>::iterator it2;
  // Traverse the top-level list
  for(it = inners.begin(); it!=inners.end(); it++) {
    // If empty inner list, remove inner list
    if(it->sizeOfThisInnerList() == 0)
    {
      it = inners.erase(it);
      it--;
      continue;
    }
    // If two adjacent short inner lists are encountered, merge into single inner list
    if(it != inners.begin() && prev(it)->sizeOfThisInnerList() < sqrt(size())/2
      && it->sizeOfThisInnerList() <  sqrt(size())/2)
    {
      prev(it)->merge(*it);
      it = inners.erase(it);
      it--;
      continue;
    }
    // If inner list has more than 2√n items, split into 2 of equal length
    if(it->sizeOfThisInnerList() > 2*sqrt(size()))
    {
      inners.insert(next(it), it->split());
    }
  }
}

void SquareList::addFirst(int data)
{
  if(inners.front().getHeader() == nullptr)
  {
    InnerSquareList *newList = new InnerSquareList();
    newList->addFirst(data);
    inners.push_front(*newList);
  }
  else
  {
    inners.front().addFirst(data);
  }
  consolidate();
}


void SquareList::addLast(int data)
{
  if(inners.front().getHeader() == nullptr)
  {
    InnerSquareList newList;
    newList.addFirst(data);
    inners.push_front(newList);
  }
  else
  {
    inners.back().addLast(data);
  }
  consolidate();
}

int SquareList::removeFirst()
{
  if(inners.front().getHeader() == nullptr)
  {
    return -1;
  }
  int r = inners.front().remove(0);
  consolidate();
  return r;
}

//insert a value to be at location "pos"
void SquareList::add(int pos, int data)
{
  list<InnerSquareList>::iterator it;
  for(it = inners.begin(); it!=inners.end(); ++it)
  {
    if(pos >= it->sizeOfThisInnerList())
    {
      pos -= it->sizeOfThisInnerList();
    }
    else
    {
      it->add(pos, data);
      consolidate();
      return;
    }
  }
}

int SquareList::remove(int pos)
{
  list<InnerSquareList>::iterator it;
  for(it = inners.begin(); it!=inners.end(); ++it)
  {
    if(pos >= it->sizeOfThisInnerList())
    {
      pos -= it->sizeOfThisInnerList();
    }
    else
    {
      int r = it->remove(pos);
      consolidate();
      return r;
    }
  }
  return -1;
}

int SquareList::get(int pos)
{
  list<InnerSquareList>::iterator it;
  for(it = inners.begin(); it!=inners.end(); ++it)
  {
    if(pos >= it->sizeOfThisInnerList())
    {
      pos -= it->sizeOfThisInnerList() ;
    }
    else
    {
      return it->get(pos);
    }
  }
  return -1;
}

void SquareList::set(int pos, int data)
{
  list<InnerSquareList>::iterator it;
  for(it = inners.begin(); it!=inners.end(); ++it)
  {
    if(pos >= it->sizeOfThisInnerList())
    {
      pos -= it->sizeOfThisInnerList();
    }
    else
    {
      it->set(pos, data);
      break;
    }
  }
}

//total number of nodes in all inner lists
int SquareList::size()
{
  int s = 0;
  list<InnerSquareList>::iterator it;
  for(it = inners.begin(); it !=inners.end(); ++it)
  {
    s += it->sizeOfThisInnerList();
  }
  return s;
}

//Position of first occurence of a value
int SquareList::indexOf(int data)
{
  int totPos = 0;
  list<InnerSquareList>::iterator it;
  for(it = inners.begin(); it!=inners.end(); ++it)
  {
    for(int pos = 0; pos < it->sizeOfThisInnerList(); pos++)
    {
      if(it->get(pos) == data)
      {
        totPos += pos;
        return totPos;
      }
      totPos += it->sizeOfThisInnerList();
    }
  }
  return -1;
}

//Printing out information of Square List for debugging
void SquareList::dump()
{
  cout << "*********************************************************" << endl;
  cout << "SquareList dump: " << endl;
  cout << "Total size = " << size() << ", # of lists = " << inners.size() << endl;
  list<InnerSquareList>::iterator it;
  for(it = inners.begin(); it!=inners.end(); ++it)
  {
    it->dump();
  }
  cout << "*********************************************************" << endl;
}
