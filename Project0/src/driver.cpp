#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

#include "Continent.cpp"
using namespace std;
void readFromFiles(string, string, vector <Country>&, vector <Continent>&);

int main() {
  vector <Country> countries;
  vector <Continent> continents;
  readFromFiles("2013WorldBankEducationCensusData.txt", "CountriesContinents.txt", countries, continents);
  for(unsigned i = 0; i < continents.size(); ++i)
    cout << continents.at(i);
  return 0;
}

void readFromFiles(string file1, string file2, vector <Country> &countries, vector <Continent> &continents) {
  string name;
  long pop;
  string line;
  // FIRST FILE
  ifstream infile(file1);
  if(!infile.is_open()) {
    cout << "The file was not successfully opened." << endl;
    exit(1);
  }
  getline(infile, line); // Skips first line
  while(getline(infile, line)) {
    string temp;
    stringstream file1(line);
    Country cou;
    file1 >> name >> pop;
    cou.setName(name);
    cou.setPopulation(pop);
    // Adult literacy rate
    file1 >> temp;
    if(temp != "N/A")
      cou.setLiteracyRate(atof(temp.c_str()));
    else
      cou.setLiteracyRate(-1);
    // Expenditure on education as % of GDP
    file1 >> temp;
    if(temp != "N/A")
      cou.setEducationGDP(atof(temp.c_str()));
    else
      cou.setEducationGDP(-1);
    // Primary completion rate, both sexes
    file1 >> temp;
    if(temp != "N/A")
      cou.setPrimaryTotal(atof(temp.c_str()));
    else
      cou.setPrimaryTotal(-1);
    // Primary Completion rate, male
    file1 >> temp;
    if(temp != "N/A")
      cou.setPrimaryMale(atof(temp.c_str()));
    else
      cou.setPrimaryMale(-1);
    // Primary Completion rate, female
    file1 >> temp;
    if(temp != "N/A")
      cou.setPrimaryFemale(atof(temp.c_str()));
    else
      cou.setPrimaryFemale(-1);
    // Youth literacy rate, female
    file1 >> temp;
    if(temp != "N/A")
      cou.setYouthLitRateFem(atof(temp.c_str()));
    else
      cou.setYouthLitRateFem(-1);
    // Youth literacy rate, male
    file1 >> temp;
    if(temp != "N/A")
      cou.setYouthLitRateMale(atof(temp.c_str()));
    else
      cou.setYouthLitRateMale(-1);
    // Push back
    countries.push_back(cou);
  }
  infile.close();


  vector <Country> countriesFound;
  string continentName;
  int numCountries;
  // SECOND FILE
  ifstream infile2(file2);
  if(!infile2.is_open()) {
    cout << "The file wasn't successfully opened." << endl;
    exit(1);
  }
  string tempCountry;
  string countryName;
  string temp = "";
  while(getline(infile2,temp)) {
    Continent continent;
    continentName = temp.substr(0,temp.find(" "));
    temp = temp.substr(temp.find("- ") + 2);
    numCountries = stoi(temp.c_str());
    continent.setContinentName(continentName);
    for(int i = 0; i < numCountries; ++i) {
      getline(infile2, tempCountry);
      // Removing "-", " ", ",", and "."
      tempCountry.erase(remove(tempCountry.begin(), tempCountry.end(), '-'), tempCountry.end());
      tempCountry.erase(remove(tempCountry.begin(), tempCountry.end(), ' '), tempCountry.end());
      tempCountry.erase(remove(tempCountry.begin(), tempCountry.end(), ','), tempCountry.end());
      tempCountry.erase(remove(tempCountry.begin(), tempCountry.end(), '.'), tempCountry.end());
      for(int j = 0; j < countries.size(); ++j) {
        countryName = countries.at(j).getName();
        // Removing "-", " ", ",", and "."
        countryName.erase(remove(countryName.begin(), countryName.end(), '-'), countryName.end());
        countryName.erase(remove(countryName.begin(), countryName.end(), ' '), countryName.end());
        countryName.erase(remove(countryName.begin(), countryName.end(), ','), countryName.end());
        countryName.erase(remove(countryName.begin(), countryName.end(), '.'), countryName.end());
        // if country names match
        if(tempCountry == countryName || countryName.find(tempCountry) != -1) {
          countriesFound.push_back(countries.at(j));
          countries.erase(countries.begin() + j);
          break;
        }
      }
    }
    continent.setCountriesInContinent(countriesFound);
    continents.push_back(continent);
    countriesFound.clear();
    infile2.clear();
  }
  infile2.close();

}
