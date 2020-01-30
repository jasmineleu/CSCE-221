#include "Order.h"

Order::Order() : m_sCustomerName(""), m_bAcceptsPartialOrder(false), m_bOrderCompleted(false),
  m_requests(), m_filledRequests() {}

Order::~Order() {}

bool Order::requestsIsEmpty() {
  return m_requests.empty();
}

bool Order::filledRequestsIsEmpty() {
  return m_filledRequests.empty();
}

void Order::setCustomerName(string name) {
  m_sCustomerName = name;
}

void Order::setAcceptPartial(bool acceptPartial) {
  m_bAcceptsPartialOrder = acceptPartial;
}

void Order::setOrderComplete(bool orderCompleted) {
  m_bOrderCompleted = orderCompleted;
}

bool Order::isAcceptPartial() {
  return m_bAcceptsPartialOrder;
}

FOOD_TYPE& Order::getNextRequest() {
  FOOD_TYPE* temp;
  temp = &m_requests.front();
  m_requests.pop();
  return *temp;
}

void Order::addRequestToOrder(FOOD_TYPE food) {
  m_requests.push(food);
}

void Order::addFoodToOrder(Food* food) {
  m_filledRequests.push(food);
}

Food* Order::popFoodFromOrder() {
  Food* food;
  food = m_filledRequests.front();
  m_filledRequests.pop();
  return food;
}

void Order::printOrder(ofstream& out) {
  queue<FOOD_TYPE> requests = m_requests;
  FOOD_TYPE temp;
  Food* food;
  double total = 0;
  // not complete
  if(!m_bOrderCompleted) {
    out << m_sCustomerName << endl;
    out << "Requests: ";
    while(!requests.empty()) {
      temp = requests.front();
      if(temp == Meat) { out << "Meat "; }
      else if(temp == Fruit) { out << "Fruit "; }
      else if(temp == Vegetable) { out << "Vegetable "; }
      else if(temp == Starch) { out << "Starch "; }
      else if(temp == Sweet) { out << "Sweet "; }
      requests.pop();
    }
  }
  // order is complete
   else if(m_bOrderCompleted && m_requests.empty()) {
    out << m_sCustomerName << endl;
    out << "Items: " << endl;
    while(!m_filledRequests.empty()) {
      food = popFoodFromOrder();
      food->printFood(out);
      out << " $" << setprecision(2) << fixed << food->getCost() << endl;
      total += food->getCost();
    }
    out << "***Total: $" << total;
  }
  // partially completed
  else if(m_bOrderCompleted && !m_requests.empty() && m_bAcceptsPartialOrder) {
    out << m_sCustomerName << " (Partial)" << endl;
    out << "Unfilled Requests: ";
    while(!requests.empty()) {
      temp = requests.front();
      if(temp == Meat) { out << "Meat "; }
      else if(temp == Fruit) { out << "Fruit "; }
      else if(temp == Vegetable) { out << "Vegetable "; }
      else if(temp == Starch) { out << "Starch "; }
      else if(temp == Sweet) { out << "Sweet "; }
      requests.pop();
    }
    out << endl;
    out << "Items: " << endl;
    while(!m_filledRequests.empty()) {
      food = popFoodFromOrder();
      food->printFood(out);
      out << " $" << setprecision(2) << fixed << food->getCost() << endl;
      total += food->getCost();
    }
    out << "***Total: $" << total;
  }
  // not completed && not partial
  else if(m_bOrderCompleted && !m_requests.empty() && !m_bAcceptsPartialOrder) {
    out << m_sCustomerName << " - Unable to complete order" << endl;
    out << "Unfilled Requests: ";
    while(!requests.empty()) {
      temp = requests.front();
      if(temp == Meat) { out << "Meat "; }
      else if(temp == Fruit) { out << "Fruit "; }
      else if(temp == Vegetable) { out << "Vegetable "; }
      else if(temp == Starch) { out << "Starch "; }
      else if(temp == Sweet) { out << "Sweet "; }
      requests.pop();
    }
  }
  out << endl;
  out << "-----";
}

void Order::printRequests() {
  queue<FOOD_TYPE> temp = m_requests;
  if(temp.empty()) {
    cout << "NO REQUESTS" << endl;
  }
  while(!temp.empty()) {
    cout << temp.front() << " ";
    temp.pop();
  }
}
