/*
in Order:
string m_sCustomerName;
bool m_bAcceptsPartialOrder;
bool m_bOrderCompleted;

queue<Order*> m_ordersUnfilled;
queue<Order*> m_ordersComplete;
Order* m_pCurrentOrder;
*/
#include "Orders.h"
Orders::Orders() : m_ordersUnfilled(), m_ordersComplete(), m_pCurrentOrder() {}
Orders::~Orders() {}

bool Orders::unfilledIsEmpty() {
  return m_ordersUnfilled.empty();
}

void Orders::addOrder(Order* order) {
  m_ordersUnfilled.push(order);
}

void Orders::completeOrder() {
  Order* order = m_ordersUnfilled.front();
  m_ordersUnfilled.pop();
  m_ordersComplete.push(order);
}

Order* Orders::getCurrentOrder() {
  m_pCurrentOrder = m_ordersUnfilled.front();
  return m_pCurrentOrder;
}

void Orders::loadOrders(string filename) {
  Order* newOrder;
  string line;
  string name;
  string acceptsPartial;
  bool b_acceptsPartial;
  string food;
  string skip;
  FOOD_TYPE foodEnum;
  ifstream infile(filename);
  if(!infile.is_open()) {
    cout << "The file was not successfully opened." << endl;
    exit(1);
  }
  while(!infile.eof()) {
    newOrder = new Order;
    getline(infile, line);
    name = line.substr(1, line.find_last_of('"')-1);
    stringstream X(line);
    X >> skip >> skip;
    X >> acceptsPartial;

    while(X >> food) {
      if(food == "sweet") { foodEnum = Sweet; }
      else if(food == "starch") { foodEnum = Starch; }
      else if(food == "meat") { foodEnum = Meat; }
      else if(food == "vegetable") { foodEnum = Vegetable; }
      else if(food == "fruit") { foodEnum = Fruit; }
      newOrder->addRequestToOrder(foodEnum);
      // out << food << " ";
    }
    if(acceptsPartial == "yes") { b_acceptsPartial = true; }
    else { b_acceptsPartial = false; }
    newOrder->setCustomerName(name);
    newOrder->setAcceptPartial(b_acceptsPartial);
    // cout << name << " " << acceptsPartial << endl;
    addOrder(newOrder);
  }
  infile.close();
}

void Orders::printOrders(ofstream& out) {
  if(m_ordersComplete.empty()) { // hasn't started yet
    queue<Order*> unfilled = m_ordersUnfilled;
    out << "---------- Orders -----------" << endl;
    while(!unfilled.empty()) {
      unfilled.front()->printOrder(out);
      unfilled.pop();
      out << endl;
    }
  }
  else {
    queue<Order*> completed = m_ordersComplete;
    out << "---------- Orders -----------" << endl;
    while(!completed.empty()) {
      completed.front()->printOrder(out);
      completed.pop();
      out << endl;
    }
  }

}
