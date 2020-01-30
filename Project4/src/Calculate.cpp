#include "Calculate.h"
#include <iostream>
using namespace std;

Calculate::Calculate(string fileName) {
  outputFileStream.open("results.txt");
  readFile(fileName);
}

Calculate::~Calculate() {
  outputFileStream.close();
}

bool Calculate::isOperator(string str) {
  if(str == "(" || str == ")" || str == "+" || str == "-" || str == "*" || str == "/" || str == "%"
    || str == "^") { return true; }
  return false;
}

// validates the file
void Calculate::readFile(string fileName) {
  string str;
  string line;
  bool validEquation;

  ifstream infile;
  infile.open(fileName);

  if(!infile.is_open()) {
    cout << "could not open file." << endl;
    exit(1);
  }

  while(getline(infile, line)) {
    validEquation = true;
    // clear value stack
    while (!value_stack.empty( )) { value_stack.pop(); }
    while (!operator_stack.empty( )) { operator_stack.pop(); }
    while (!priority_stack.empty( )) { priority_stack.pop(); }
    operator_stack.push("$");
    priority_stack.push(-1);

    equation.clear();
    istringstream iss(line);
    while(iss >> str) {
      if(!isNum(str) && !isOperator(str) && str != "") {
        outputFileStream << "ERROR: invalid equation" << endl;
        validEquation = false;
        break;
      }
      else {
        equation.push_back(str);
      }
    }
    if(validEquation) {
      // cout << "the equation(list) we are looking at is: ";
      // cout << "[";
      // vector<string>::iterator i;
      // for(i = equation.begin(); i != equation.end()-1; ++i) {
      //   cout << "'" <<  *i << "', ";
      // }
      // cout << "'" << *i << "']" << endl;
      push();
    }

  }
}

bool Calculate::isNum(string str) {
  for(int i = 0; str[i] != '\0'; i++) {
    if(isdigit(str[i])) { return true; }
  }
  return false;
}

// writes results to a file; parameters can vary
void Calculate::writeResults() {
  // didn't really need this method
}


// can only push a symbol on the stack if its input priority is greater to what priority is
// currently at top of the stack. otherwise must pop and process to make priority value lower
// could use this function in conjunction with stack's push function
void Calculate::push() {
  bool notDone = true;
  bool notDone1 = true;
  while(!equation.empty()) {
    string curr = equation.at(0);
    // cout << "  looking at " << curr << " in the equation" << endl;
    // value
    if(!isOperator(curr)) {
      value_stack.push(stod(curr));
      // cout << "adding a value to ValueStack" << endl;
      equation.erase(equation.begin());
    }

    // non-value
    else if(curr == ")") {
      // cout << "pop and process, found a )" << endl;
      bool a = popAndProcess();
      if(!a) { return; }
      if(operator_stack.top() == "$") {
        outputFileStream << "invalid" << endl;
        return;
      }

      while(notDone1 && operator_stack.top() != "(") {
        notDone1 = popAndProcess();
      }
      if(!notDone1) { return; }
      operator_stack.pop();
      priority_stack.pop();
      equation.erase(equation.begin());

    }
    else if(inputPriority[curr] > stackPriority[operator_stack.top()]) {
      // cout << curr << " was just added to opStack" << endl;
      // cout << stackPriority[curr] << " was just added to inputStack" << endl;

      priority_stack.push(stackPriority[curr]);
      operator_stack.push(curr);
      equation.erase(equation.begin());
    }
    else if(inputPriority[curr] <= stackPriority[operator_stack.top()]) {
      // cout << "STACK VALUE >= the new INPUT PRIORITY. So pop and process, and recheck." << endl;
      popAndProcess();
    }
  }

  // empty
  while(notDone && operator_stack.top() != "$") {
    // cout << "END OF EQUATION, so pop and process until op Stack is only a $" << endl;
    notDone = popAndProcess();
  }
  if(!notDone) { return; }

  if(value_stack.size() != 1) {
    outputFileStream << "invalid" << endl;
    return;
  }
  outputFileStream << value_stack.top() << endl;
}


// actual calculation is done
bool Calculate::popAndProcess() {
  string op = operator_stack.top();
  if(value_stack.empty()) {
    outputFileStream << "invalid" << endl;
    return false;
  }
  operator_stack.pop();
  priority_stack.pop();
  double var2 = value_stack.top();
  value_stack.pop();

  if(value_stack.empty()) {
    outputFileStream << "invalid" << endl;
    return false;
  }
  double var1 = value_stack.top();
  value_stack.pop();

  double var1Dec;
  double var1Int;
  var1Dec = modf(var1, &var1Int);
  double var2Dec;
  double var2Int;
  var2Dec = modf(var2, &var2Int);
  if(op == "+") {
    // cout << "new answer being placed into the VALUE stack is: " << var1 + var2 << endl;
    value_stack.push(var1 + var2);
  }

  else if(op == "-") {
    // cout << "new answer being placed into the VALUE stack is: " << var1 - var2 << endl;
    value_stack.push(var1 - var2);
  }

  else if(op == "*") {
    // cout << "new answer being placed into the VALUE stack is: " << var1 * var2 << endl;
    value_stack.push(var1 * var2);
  }

  else if(op == "/") {
    // cout << "new answer being placed into the VALUE stack is: " << var1 / var2 << endl;
    value_stack.push(var1 / var2);
  }

  else if(op == "%") {
    if(var1Dec != 0 || var2Dec != 0) {
      outputFileStream << "invalid" << endl;
      return false;
    }
    // cout << "new answer being placed into the VALUE stack is: " << (int)var1 % (int)var2 << endl;
    value_stack.push((int)var1 % (int)var2);
  }

  else if(op == "^") {
    if(var1Dec != 0 || var2Dec != 0) {
      outputFileStream << "invalid" << endl;
      return false;
    }
    value_stack.push(pow((int)var1, (int)var2));
  }
  return true;
}
