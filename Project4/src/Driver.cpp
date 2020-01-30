#include "Calculate.h"
#include <iostream>
using namespace std;

void printGreeting() {
  cout << "Jasmine Leu, Section 502" << endl;
}

int main(int argc, char* argv[]) {
  printGreeting();
  Calculate* myCalc = new Calculate(argv[1]);
  delete myCalc;
}
