#include "Manager.h"

Manager::Manager(string store, string orders) {
  createStore(store);
  createOrders(orders);
}

Manager::~Manager() {}

void Manager::createStore(string filename) {
  m_store.stockStore(filename);
}

void Manager::createOrders(string filename) {
  m_orders.loadOrders(filename);
}

void Manager::fillOrders(ofstream& out) {
  Order* currentOrder;
  Food* deleteFood;
  Food* food;
  FOOD_TYPE request;
  queue<FOOD_TYPE> tempUnfilled;
  while(!m_orders.unfilledIsEmpty()) { // goes through orders
    currentOrder = nullptr;
    food = nullptr;
    currentOrder = m_orders.getCurrentOrder();
    while(!(currentOrder->requestsIsEmpty())) { // goes through requests in currentOrder
      request = currentOrder->getNextRequest();
      food = m_store.getFoodByType(request);

      if(food != nullptr) { // store matches request
        currentOrder->addFoodToOrder(food);
      }

      // nothing in store matches request & no partial order; return to Store
      else if(food == nullptr && !currentOrder->isAcceptPartial()) {
        // first of requests
        if(currentOrder->filledRequestsIsEmpty()) {
          tempUnfilled.push(request);
          while(!currentOrder->requestsIsEmpty()) {
            tempUnfilled.push(currentOrder->getNextRequest());
          }
        }
        // middle of requests
        else {
          while(!currentOrder->filledRequestsIsEmpty()) {

            // return everything back to store
            deleteFood = currentOrder->popFoodFromOrder();
            m_store.addFood(deleteFood);
            // put everything back in unfilled requests
            tempUnfilled.push(deleteFood->getType());
          }
          tempUnfilled.push(request);

        }
        break;
      }

      else if(food == nullptr && currentOrder->isAcceptPartial()) { // add food to unfilled requests
        tempUnfilled.push(request);
      }
    }
    while(!tempUnfilled.empty()) {
      currentOrder->addRequestToOrder(tempUnfilled.front());
      tempUnfilled.pop();
    }
    currentOrder->setOrderComplete(true);
    m_orders.completeOrder();
  }
}

void Manager::printStatus(ofstream& out) {
  m_store.printStore(out);
  m_orders.printOrders(out);
}
