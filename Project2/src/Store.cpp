#include "Store.h"

//   vector< stack<Food*> > m_bins;
Store::Store() {
  for(int i = 0; i < 5; ++i) {
    m_bins.push_back((stack<Food*>()));
  }
}
Store::~Store() {}

void Store::addFood(Food* food) {
  FOOD_TYPE foodType = food->getType();
  if(foodType == Meat)
  {
    m_bins.at(0).push(food);
  }
  else if(foodType == Fruit)
  {
    m_bins.at(1).push(food);
  }
  else if(foodType == Vegetable)
  {
    m_bins.at(2).push(food);
  }
  else if(foodType == Starch)
  {
    m_bins.at(3).push(food);
  }
  else if(foodType == Sweet)
  {
    m_bins.at(4).push(food);
  }
}

Food* Store::getFoodByType(FOOD_TYPE type) {
  Food* food = nullptr;
  if(type == Meat && !m_bins.at(0).empty()) {
    food = m_bins.at(0).top();
    m_bins.at(0).pop();
  }
  else if(type == Fruit && !m_bins.at(1).empty()) {
    food = m_bins.at(1).top();
    m_bins.at(1).pop();
  }
  else if(type == Vegetable && !m_bins.at(2).empty()) {
    food = m_bins.at(2).top();
    m_bins.at(2).pop();
  }
  else if(type == Starch && !m_bins.at(3).empty()) {
    food = m_bins.at(3).top();
    m_bins.at(3).pop();
  }
  else if(type == Sweet && !m_bins.at(4).empty()){
    food = m_bins.at(4).top();
    m_bins.at(4).pop();
  }
  return food;
}

void Store::stockStore(string filename) {
  string line = "";
  string name = "";
  string food = "";
  string skip;
  FOOD_TYPE foodEnum;
  double cost;
  ifstream infile(filename);
  if(!infile.is_open()) {
    cout << "The file was not successfully opened." << endl;
    exit(1);
  }
  while(getline(getline(infile, skip, '"'), name, '"') >> food >> cost) {
    // cast into enum
    if(food == "meat") { foodEnum = Meat; }
    else if(food == "fruit") { foodEnum = Fruit; }
    else if(food == "vegetable") { foodEnum = Vegetable; }
    else if(food == "starch") { foodEnum = Starch; }
    else { foodEnum = Sweet; }

    Food* temp = new Food(name, foodEnum, cost);
    addFood(temp);
  }
  infile.close();
}

void Store::printStore(ofstream& out) {
  out << "---------- Store ----------" << endl;
  out << "Meat: " << m_bins.at(0).size() << " ";
  printStack(out, m_bins.at(0));
  out << endl;
  out << "Fruit: " << m_bins.at(1).size() << " ";
  printStack(out, m_bins.at(1));
  out << endl;
  out << "Vegetable: " << m_bins.at(2).size() << " ";
  printStack(out, m_bins.at(2));
  out << endl;
  out << "Starch: " << m_bins.at(3).size() << " ";
  printStack(out, m_bins.at(3));
  out << endl;
  out << "Sweet: " << m_bins.at(4).size() << " ";
  printStack(out, m_bins.at(4));
  out << endl;
}

void Store::printStack(ofstream& out, stack<Food*> const& oldStack) {
  stack<Food*> tempStack = oldStack;
  if(!tempStack.empty()) {
    tempStack.top()->printFood(out);
    tempStack.pop();
    while(!tempStack.empty()) {
      out << ", ";
      tempStack.top()->printFood(out);
      tempStack.pop();
    }
  }
}
