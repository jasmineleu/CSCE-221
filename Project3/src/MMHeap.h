/************************************************
**  File			:   MMHeap.h
**  Project		: 	CSCE-221 Project 3, Fall 2019
**  Author		: 	Jasmine Leu
**  Date			:   11/13/2019
**  Section		: 	502
**  E-mail 		:		jasmineleu@tamu.edu

** 	This file contains the header file for MMHeap.h.

************************************************/

#ifndef MMHEAP_H
#define MMHEAP_H
#include <string.h>
#include <cmath>
#include <math.h>
#include <iostream>
using namespace std;

template <typename T>
class MMHeap
{
  T** pData;
  size_t length; // not capacity

public:
  MMHeap() : pData(nullptr), length(0) {};
  MMHeap(const int& initialSize) : length(0) {
    pData = new T*[initialSize];
  };
  ~MMHeap() {};

  // returns number of items in the min-max heap; should run in constant time
  size_t size() const { return length; };

  // should run in O(log n) time
  void insert (T* px) {
    pData[++length] = px;
    int i = length;
    int level = ceil(log2(length+1)-1);
    if(i != 1) {
      if(level%2 == 0) {  // min level
        if(*pData[i] > *pData[i/2]) {
          T temp = *pData[i/2];
          *pData[i/2] = *px;
          *px = temp;
          bubbleUpMax(i/2);
        }
        else {
          bubbleUpMin(i);
        }
      }
      else {  // max level
        if(*pData[i] < *pData[i/2]) {
          T temp = *pData[i/2];
          *pData[i/2] = *px;
          *px = temp;
          bubbleUpMin(i/2);
        }
        else {
          bubbleUpMax(i);
        }
      }
    }
  };

  void bubbleUpMin(int i) {
    if(i >= 4 && *pData[i] < *pData[i/4]) {
      T temp = *pData[i/4];
      *pData[i/4] = *pData[i];
      *pData[i] = temp;
      bubbleUpMin(i/4);
    }
  };

  void bubbleUpMax(int i) {
    if(i >= 4 && *pData[i] > *pData[i/4]) {
      T temp = *pData[i/4];
      *pData[i/4] = *pData[i];
      *pData[i] = temp;
      bubbleUpMax(i/4);
    }
  };

  // prints out the contents of the min-max heap
  void dump() {
    int level = ceil(log2(length+1)-1);

    cout << "---------------------------------------" << endl;
    cout << "--- min-max heap dump ---" << endl;
    cout << "  Size = " << length << endl;
    cout << "  Minimum = " << *getMin() << endl;
    cout << "  Maximum = " << *getMax() << endl;
    cout << "  Last level is " << ((level % 2 == 0)?"even": "odd")<< endl;
    cout << "--- heap data items ---" << endl;
    for(int i = 1; i <= length; ++i) {
      cout << "H[" << i << "] = " << *pData[i] << endl;
    }
    cout << "---------------------------------------" << endl;
  };

  // Throws an exception if empty
  T* getMin() {
    if(length == 0) {
      throw runtime_error("pData is empty.");
    }
    return pData[1];
  };

  // Throws an exception if empty
  T* getMax() {
    if(length == 0) {
      throw runtime_error("pData is empty.");
    }
    if(length == 1) { return pData[1]; }
    if(length == 2) { return pData[2]; }
    return ((*pData[2] > *pData[3])? pData[2] : pData[3]);
  };

  // Removes and returns the smallest item. Should run in O(log n).
  T deleteMin() {
    T min = *getMin();
    pData[1] = pData[length];
    pData[length] = NULL;
    delete pData[length--];
    pushDownMin(1);
    return min;
  };

  void pushDownMin(int i) {
    int smallestC = 0;
    int smallestGC = 0;
    // ONE CHILD
    if(pData[i*2] != NULL && pData[i*2+1] == NULL) {
      if(*pData[i*2] < *pData[i]) { // if child < x
        // swap child and x
        T temp = *pData[i*2];
        *pData[i*2] = *pData[i];
        *pData[i] = temp;
      }
    }
    // TWO CHILDREN AND NO GRANDCHILDREN
    else if(pData[i*2] != NULL && pData[i*2+1] != NULL && pData[i*4] == NULL) {
      // NO GRANDCHILDREN
      if(pData[i*4] == NULL) {
        smallestC = (*pData[i*2] <= *pData[i*2+1])? i*2 : i*2+1;
        if(*pData[smallestC] < *pData[i]) {
          // swap child and x
          T temp = *pData[smallestC];
          *pData[smallestC] = *pData[i];
          *pData[i] = temp;
        }
      }
    }
    // TWO CHILDREN AND HAS AT LEAST ONE GRANDCHILD
    else if(pData[i*4] != NULL){
      // ONE GRANDCHILD
      if (pData[i*4+1] == NULL) {
        smallestC = (*pData[i*2] <= *pData[i*2+1])? i*2 : i*2+1;
        smallestGC = i*4;
      }
      // TWO GRANDCHILDREN
      else if (pData[i*4+1] != NULL && pData[i*4+2] == NULL) {
        smallestC = (*pData[i*2] <= *pData[i*2+1])? i*2 : i*2+1;
        smallestGC = (*pData[i*4] <= *pData[i*4+1])? i*4 : i*4+1;
      }
      // THREE GRANDCHILDREN
      else if (pData[i*4+1] != NULL && pData[i*4+2] != NULL && pData[i*4+3] == NULL) {
        smallestC = (*pData[i*2] <= *pData[i*2+1])? i*2 : i*2+1;
        int smallestA = (*pData[i*4] <= *pData[i*4+1])? i*4 : i*4+1;
        smallestGC = (*pData[smallestA] <= *pData[i*4+2])? smallestA : i*4+2;
      }
      // FOUR GRANDCHILDREN
      else if (pData[i*4+1] != NULL && pData[i*4+2] != NULL && pData[i*4+3] != NULL ) {
        smallestC = (*pData[i*2] <= *pData[i*2+1])? i*2 : i*2+1;
        int smallestA = (*pData[i*4] <= *pData[i*4+1])? i*4 : i*4+1;
        int smallestB = (*pData[i*4+2] <= *pData[i*4+3])? i*4+2 : i*4+3;
        smallestGC = (*pData[smallestA] <= *pData[smallestB])? smallestA : smallestB;
      }
      if(*pData[smallestGC] < *pData[smallestC]) { // m is a grandchild
        if(*pData[smallestGC] < *pData[i]) {
          T temp = *pData[smallestGC];
          *pData[smallestGC] = *pData[i];
          *pData[i] = temp;
          if(*pData[smallestGC] > *pData[smallestGC/2]) {
            T temp = *pData[smallestGC];
            *pData[smallestGC] = *pData[smallestGC/2];
            *pData[smallestGC/2] = temp;
          }
          pushDownMin(smallestGC);
        }
      }
      else if(*pData[smallestC] < *pData[smallestGC] && *pData[smallestC] < *pData[i]) {
        T temp = *pData[smallestC];
        *pData[smallestC] = *pData[i];
        *pData[i] = temp;
      }
    }
  };

  // Removes and returns the largest item. Should run in O(log n).
  T deleteMax() {
    T max = *getMax();
    if(length <= 2) {
      return *pData[length--];
    }
    int maxIndex = (*pData[2] > *pData[3])? 2 : 3; // either 2 or 3
    pData[maxIndex] = pData[length];
    pData[length] = NULL;
    delete pData[length--];
    pushDownMax(maxIndex);
    return max;
  };

  void pushDownMax(int i) {
    int largestC = 0;
    int largestGC = 0;
    // ONE CHILD
    if(pData[i*2] != NULL && pData[i*2+1] == NULL) {
      if(*pData[i*2] > *pData[i]) { // if child > x
        // swap child and pData[i]
        T temp = *pData[i*2];
        *pData[i*2] = *pData[i];
        *pData[i] = temp;
      }
    }
    // TWO CHILDREN AND NO GRANDCHILDREN
    else if(pData[i*2] != NULL && pData[i*2+1] != NULL && pData[i*4] == NULL) {
      // NO GRANDCHILDREN
      if(pData[i*4] == NULL) {
        largestC = (*pData[i*2] > *pData[i*2+1])? i*2 : i*2+1;
        if(*pData[largestC] > *pData[i]) {
          // swap child and pData[i]
          T temp = *pData[largestC];
          *pData[largestC] = *pData[i];
          *pData[i] = temp;
        }
      }
    }
    // TWO CHILDREN AND HAS AT LEAST ONE GRANDCHILD
    else if(pData[i*4] != NULL){
      // ONE GRANDCHILD
      if (pData[i*4+1] == NULL) {
        largestC = (*pData[i*2] > *pData[i*2+1])? i*2 : i*2+1;
        largestGC = i*4;
      }
      // TWO GRANDCHILDREN
      else if (pData[i*4+1] != NULL && pData[i*4+2] == NULL) {
        largestC = (*pData[i*2] >= *pData[i*2+1])? i*2 : i*2+1;
        largestGC = (*pData[i*4] >= *pData[i*4+1])? i*4 : i*4+1;
      }
      // THREE GRANDCHILDREN
      else if (pData[i*4+1] != NULL && pData[i*4+2] != NULL && pData[i*4+3] == NULL) {
        largestC = (*pData[i*2] > *pData[i*2+1])? i*2 : i*2+1;
        int largestA = (*pData[i*4] >= *pData[i*4+1])? i*4 : i*4+1;
        largestGC = (*pData[largestA] >= *pData[i*4+2])? largestA : i*4+2;
      }
      // FOUR GRANDCHILDREN
      else if (pData[i*4+1] != NULL && pData[i*4+2] != NULL && pData[i*4+3] != NULL ) {
        largestC = (*pData[i*2] > *pData[i*2+1])? i*2 : i*2+1;
        int largestA = (*pData[i*4] >= *pData[i*4+1])? i*4 : i*4+1;
        int largestB = (*pData[i*4+2] >= *pData[i*4+3])? i*4+2 : i*4+3;
        largestGC = (*pData[largestA] >= *pData[largestB])? largestA : largestB;
      }
      if(*pData[largestGC] > *pData[largestC]) { // m is a grandchild
        if(*pData[largestGC] > *pData[i]) {
          T temp = *pData[largestGC];
          *pData[largestGC] = *pData[i];
          *pData[i] = temp;
          if(*pData[largestGC] < *pData[largestGC/2]) {
            T temp = *pData[largestGC];
            *pData[largestGC] = *pData[largestGC/2];
            *pData[largestGC/2] = temp;
          }
          pushDownMax(largestGC);
        }
      }
      else if(*pData[largestC] > *pData[largestGC]) {
        T temp = *pData[largestC];
        *pData[largestC] = *pData[i];
        *pData[i] = temp;
      }
    }
  };
};

#endif
