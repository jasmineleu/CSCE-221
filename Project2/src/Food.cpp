#include "Food.h"

Food::Food() : m_sName(""), m_eType(), m_dCost(0.0) {}

Food::Food(string name, FOOD_TYPE type, double cost) {
  m_sName = name;
  m_eType = type;
  m_dCost = cost;
}

Food::~Food() {}

FOOD_TYPE Food::getType() {
  return m_eType;
}

double Food::getCost() {
  return m_dCost;
}

void Food::printFood(ofstream& out) {
  out << m_sName;
}
