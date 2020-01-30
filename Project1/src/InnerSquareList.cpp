/************************************************
**  File			:   InnerSuqareList.cpp
**  Project		: 	CSCE-221 Project 1, Fall 2019
**  Author		: 	Jasmine Leu
**  Date			:   10/4/2019
**  Section		: 	502
**  E-mail 		:		jasmineleu@tamu.edu

** 	This file contains the cpp file for InnerSquareLists.

************************************************/

#include "InnerSquareList.h"
using namespace std;

Node *InnerSquareList::getHeader()
{
  return m_header;
}

Node *InnerSquareList::getTail()
{
  return m_tail;
}

InnerSquareList::InnerSquareList() : m_header(nullptr), m_tail(nullptr), m_length(0){}

//initialize an inner list with given data
InnerSquareList::InnerSquareList(Node* header, Node* tail, size_t length)
  : m_header(header), m_tail(tail), m_length(length) {}

InnerSquareList::~InnerSquareList() {}

//delete all dynamically allocated nodes
void InnerSquareList::clean()
{
  Node* curr = m_header;
  while(curr != nullptr)
  {
    Node* next = curr->next;
    delete next;
    curr = next;
  }
  m_header = nullptr;
  m_tail = nullptr;
  m_length = 0;
}

//data should be at position "pos" after insertion
void InnerSquareList::add(int pos, int data)
{
  if(pos == 0)
    addFirst(data);
  else if(pos == m_length)
    addLast(data);
  else
  {
    Node* curr = m_header;
    Node* temp = new Node();
    temp->value = data;
    for(int i = 0; curr!=nullptr && i<pos-1; ++i)
    {
      curr = curr->next;
    }
    temp->next = curr->next;
    curr->next = temp;
    m_length++;
  }
}

//push_front of STL
void InnerSquareList::addFirst(int data)
{
  Node* newNode = new Node();
  newNode->value = data;
  if(m_header == nullptr)
  {
    m_tail = newNode;
    newNode->next = nullptr;
  }
  else
  {
    newNode->next = m_header;
  }
  m_header = newNode;
  this->m_length++;
}

//insert as the last element
void InnerSquareList::addLast(int data)
{
  Node* newNode = new Node();
  newNode->value = data;
  if(m_header == nullptr)
  {
    m_header = newNode;
    m_tail = newNode;
  }
  else
  {
    m_tail->next = newNode;
    m_tail = newNode;
  }
  this->m_length++;
}

//remove node, position starts from 0
int InnerSquareList::remove(int pos)
{
  Node* temp = m_header;
  if(m_header == nullptr) return -1;
  if(pos == 0)
  {
    m_header = temp->next;
    m_length--;
    return temp->value;
  }

  for(int i = 0; temp->next!=nullptr && i<pos-1; ++i)
  {
    temp = temp->next;
  }
  Node* n = temp->next;
  int v = temp->next->value;
  temp->next = temp->next->next;
  delete n;
  if(temp->next == nullptr)
  {
    m_tail = temp;
  }
  m_length--;
  return v;
}

//return the element at position pos
int InnerSquareList::get(int pos) const
{
  int start = 0;
  Node* curr = m_header;
  while(start < pos)
  {
    curr = curr->next;
    start++;
  }
  return curr->value;
}

//change the value at position pos to data
void InnerSquareList::set(int pos, int data)
{
  int start = 0;
  Node* curr = m_header;
  while(start != pos)
  {
    curr = curr->next;
    start++;
  }
  curr->value = data;
}

//total number of nodes in the inner list
// conducts this in constant time.
size_t InnerSquareList::sizeOfThisInnerList() const
{
  return this->m_length;
}

//find the index of given data, return -1 if not found
int InnerSquareList::indexOf(int data) const
{
  int start = 0;
  Node* curr = m_header;
  while(curr != nullptr)
  {
    if(curr->value == data)
    {
      return start;
    }
    curr = curr->next;
    start ++;
  }
  return -1;
}

//merge another inner list to rear of current inner list
//the second inner list should be empty after merge
// conducts this in constant time.
void InnerSquareList::merge(InnerSquareList &isl)
{
  Node* temp = isl.m_header;
  Node* dNode = nullptr;
  while(temp != nullptr)
  {
    addLast(temp->value);
    dNode = temp;
    temp = temp->next;
    delete dNode;
  }
}

//split an inner list at mid point, return the second half
//the first half should be the same, or one element less than the second half
InnerSquareList InnerSquareList::split()
{
  Node* temp = m_header->next;
  Node* prev = m_header;
  Node* tempTail = nullptr;
  for(unsigned int i = 1; i < m_length/2; ++i)
  {
    prev = prev->next;
    temp = temp->next;
  }
  size_t length = m_length - m_length/2;
  m_length /= 2;
  tempTail = m_tail;
  m_tail = prev;
  prev->next = nullptr;

  return InnerSquareList(temp, tempTail, length);
}

//print of all node values and the last node in O(1)
//check the sample output for format
void InnerSquareList::dump()
{
  Node* curr = m_header;
  cout << "=========================================================" << endl;
  cout << "InnerList dump: " << endl;
  cout << "size = " << sizeOfThisInnerList() << endl;
  while(curr != nullptr)
  {
    cout << "[" << curr->value << "]" << " ";
    curr = curr->next;
  }
  cout << endl;
  cout << "tail.data = " << m_tail->value << endl;
}
