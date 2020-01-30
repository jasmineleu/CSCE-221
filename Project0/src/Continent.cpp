#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "Country.cpp"

class Continent : public Country {
private:
  string continentName; // not on UML
  vector<Country> countriesInContinent;
  Country highestPopulation;
  Country highestGDPSpent;
  Country highestLiteracyRate;

public:
  string getContinentName() { return continentName; }
  void setContinentName(string newName) { continentName = newName; }

  vector<Country> getCountriesInContinent() { return countriesInContinent; }
  void setCountriesInContinent(vector<Country> newCountriesInContinent) { countriesInContinent = newCountriesInContinent; }

  long getTotalPopulation() {
    long totalPopulation = 0;
    for(int i = 0; i < getCountriesInContinent().size(); ++i) {
      totalPopulation += getCountriesInContinent().at(i).getPopulation();
    }
    return totalPopulation;
  }

  Country getHighestPopulation() {
    float highestPopulation = 0;
    int index = 0;
    for(int i = 0; i < countriesInContinent.size(); ++i) {
      if(highestPopulation < getCountriesInContinent().at(i).getPopulation()) {
        highestPopulation = getCountriesInContinent().at(i).getPopulation();
        index = i;
      }
    }
    return countriesInContinent.at(index);
  }

  void setHighestPopulation(Country newHighestPopulation) { highestPopulation = newHighestPopulation; }

  Country getHighestGDPSpent() {
    float highestGDPSpent = 0;
    int index = 0;
    for(int i = 0; i < countriesInContinent.size(); ++i) {
      if(highestGDPSpent < getCountriesInContinent().at(i).getEducationGDP()) {
        highestGDPSpent = getCountriesInContinent().at(i).getEducationGDP();
        index = i;
      }
    }
    return countriesInContinent.at(index);
  }
  
  void setHighestGDPSpent(Country newHighestGDPSpent) { highestGDPSpent = newHighestGDPSpent; }

  Country getHighestLiteracyRate() {
    float highestLiteracyRate = 0;
    int index = 0;
    for(int i = 0; i < countriesInContinent.size(); ++i) {
      if(highestLiteracyRate < getCountriesInContinent().at(i).getLiteracyRate()) {
        highestLiteracyRate = getCountriesInContinent().at(i).getLiteracyRate();
        index = i;
      }
    }
    return countriesInContinent.at(index);
  }

  void setHighestLiteracyRate(Country newHighestLiteracyRate) { highestLiteracyRate = newHighestLiteracyRate; }
};

ostream& operator<<(ostream& os, Continent& cont) {
  os << cont.getContinentName() << endl;
  os << " Population: " << cont.getTotalPopulation() << endl;
  os << " Country with highest literacy rate: " << cont.getHighestLiteracyRate().getName() << " with a population of " << cont.getHighestLiteracyRate().getPopulation() <<
  " and a literacy rate of " << cont.getHighestLiteracyRate().getLiteracyRate() << endl;
  os << " Country with highest GDP spendature on education: " << cont.getHighestGDPSpent().getName() << " with a population of " << cont.getHighestGDPSpent().getPopulation() <<
  " and a GDP of " << cont.getHighestGDPSpent().getEducationGDP() << endl;
  os << " Country with highest population: " << cont.getHighestPopulation().getName() << " with a population of " << cont.getHighestPopulation().getPopulation() << endl;
  return os;
}
