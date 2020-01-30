/************************************************
**  File			:   QHeap.h
**  Project		: 	CSCE-221 Project 3, Fall 2019
**  Author		: 	Jasmine Leu
**  Date			:   11/13/2019
**  Section		: 	502
**  E-mail 		:		jasmineleu@tamu.edu

** 	This file contains the header file for QHeap.h.

************************************************/

#ifndef QHEAP_H
#define QHEAP_H
#include "MMHeap.h"
#include <exception>
#include <string>
template <typename T>

class QHeap {
  MMHeap<T>** heaps;

public:
  QHeap() : heaps(nullptr) {};
  QHeap(const int& initialSize) {
    heaps = new MMHeap<T>*[4];
    heaps[0] = new MMHeap<T>(initialSize);
    heaps[1] = new MMHeap<T>(initialSize);
    heaps[2] = new MMHeap<T>(initialSize);
    heaps[3] = new MMHeap<T>(initialSize);
  };
  ~QHeap() {};

  // adds an item to the quartile heap; should run in O(log n) time
  void insert(T* px) {
    // fewer than 4 items
    if(heaps[3]->size() == 0) {
      // FIRST ITEM
      if(heaps[0]->size() == 0) {
        heaps[0]->insert(px);
      }
      // SECOND ITEM
      else if(heaps[1]->size() == 0) {
        if(*px > *heaps[0]->getMax()) {  // bigger than first item
          heaps[1]->insert(px);
        }
        else {
          heaps[0]->insert(px);
          heaps[1]->insert(heaps[0]->getMax());
          heaps[0]->deleteMax();
        }
      }
      // THIRD ITEM
      else if(heaps[2]->size() == 0) {
        if(*px > *heaps[1]->getMax()) {  // biggest
          heaps[2]->insert(px);
        }
        else if(*px > *heaps[0]->getMax() && *px < *heaps[1]->getMax()) {
          heaps[1]->insert(px);
          heaps[2]->insert(heaps[1]->getMax());
          heaps[1]->deleteMax();
        }
        else {  // smallest
          heaps[0]->insert(px);
          heaps[1]->insert(heaps[0]->getMax());
          heaps[2]->insert(heaps[1]->getMax());
          heaps[1]->deleteMax();
          heaps[2]->deleteMax();
        }
      }
      // FOURTH ITEM
      else {
        if(*px > *heaps[2]->getMax()) {  // biggest
          heaps[3]->insert(px);
        }
        else if(*px > *heaps[1]->getMax() && *px < *heaps[2]->getMax()) {
          heaps[2]->insert(px);
          heaps[3]->insert(heaps[2]->getMax());
          heaps[2]->deleteMax();
        }
        else if(*px > *heaps[0]->getMax() && *px < *heaps[1]->getMax()) {
          heaps[1]->insert(px);
          heaps[2]->insert(heaps[1]->getMax());
          heaps[3]->insert(heaps[2]->getMax());
          heaps[1]->deleteMax();
          heaps[2]->deleteMax();
        }
        else {  // smallest
          heaps[0]->insert(px);
          heaps[1]->insert(heaps[0]->getMax());
          heaps[2]->insert(heaps[1]->getMax());
          heaps[3]->insert(heaps[2]->getMax());
          heaps[0]->deleteMax();
          heaps[1]->deleteMax();
          heaps[2]->deleteMax();
        }
      }
    }
    // more than 4 items
    else {
      // biggest
      if(*px >= *heaps[3]->getMax()) {
        heaps[3]->insert(px);
        resizeDown(3);
      }
      else if(*px >= *heaps[2]->getMin() && *px < *heaps[3]->getMin()) {
        heaps[2]->insert(px);
        resizeUp(2);
        resizeDown(3);
      }
      else if(*px >= *heaps[1]->getMin() && *px < *heaps[2]->getMin()) {
        heaps[1]->insert(px);
        resizeUp(1);
        resizeDown(3);
      }
      else {
        heaps[0]->insert(px);
        resizeUp(0);
        resizeDown(3);
      }
    }
  };

  void resizeDown(int x) {
    if(x >= 1 && heaps[x]->size() > heaps[x-1]->size()) {
      heaps[x-1]->insert(heaps[x]->getMin());
      heaps[x]->deleteMin();
      resizeDown(x-1);
    }
  };

  void resizeUp(int x) {
    if(x <=2 && heaps[x]->size() > heaps[x+1]->size()) {
      heaps[x+1]->insert(heaps[x]->getMax());
      heaps[x]->deleteMax();
      resizeUp(x+1);
    }
  };

  // if there are fewer than 4 items, then these calls may result in an exception
  T* getMin() {
    if(heaps[3]->size() == 0) {
      throw runtime_error("Fewer than 4 items in quartile heap");
    }
    return heaps[0]->getMin();
  };

  T* getMax() {
    if(heaps[3]->size() == 0) {
      throw runtime_error("Fewer than 4 items in quartile heap");
    }
    return heaps[3]->getMax();
  };

  // 25th percentile is the maximum item in the first min-max heap
  T* get25() {
    if(heaps[3]->size() == 0) {
      throw runtime_error("Fewer than 4 items in quartile heap");
    }
    return heaps[0]->getMax();
  };

  T* get50() {
    if(heaps[3]->size() == 0) {
      throw runtime_error("Fewer than 4 items in quartile heap");
    }
    return heaps[1]->getMax();
  };

  T* get75() {
    if(heaps[3]->size() == 0) {
      throw runtime_error("Fewer than 4 items in quartile heap");
    }
    return heaps[2]->getMax();
  };

  void dump() {
    cout << "***********************************" << endl;
    cout << "***** Quartile heap statistics ..." << endl;
    cout << "  Minimum = " << *getMin() << endl;
    cout << "  25th Percentile = " << *get25() << endl;
    cout << "  Median = " << *get50() << endl;
    cout << "  75th Percentile = " << *get75() << endl;
    cout << "  Maximum = " << *getMax() << endl;

    cout << "***** First Quartile heap dump ..." << endl;
    heaps[0]->dump();
    cout << "***** Second Quartile heap dump ..." << endl;
    heaps[1]->dump();
    cout << "***** Third Quartile heap dump ..." << endl;
    heaps[2]->dump();
    cout << "***** Fourth Quartile heap dump ..." << endl;
    heaps[3]->dump();

    cout << "***** End of Quartile heap dump" << endl;
    cout << "***********************************" << endl;
  };
};

#endif
