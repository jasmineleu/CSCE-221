#include <string>
#include <iostream>
using namespace std;

class Country {
private:
  string name;
  long population;
  float literacyRate;
  float primaryCompletionFemale;
  float primaryCompletionMale;
  float primaryCompletionTotal;
  float educationGDPSpent;
  float youthLitRateFem;
  float youthLitRateMale;

public:
  string getName() { return name; }
  void setName(string newName) { name = newName; }

  long getPopulation() { return population; }
  void setPopulation(long newPop) { population = newPop; }

  float getLiteracyRate() { return literacyRate; }
  void setLiteracyRate(float newRate) { literacyRate = newRate; }

  float getPrimaryFemale() { return primaryCompletionFemale; }
  void setPrimaryFemale(float newPrimaryFemale) { primaryCompletionFemale = newPrimaryFemale; }

  float getPrimaryMale() { return primaryCompletionMale; }
  void setPrimaryMale(float newPrimaryMale) { primaryCompletionMale = newPrimaryMale; }

  float getPrimaryTotal() { return primaryCompletionTotal; }
  void setPrimaryTotal(float newPrimaryTotal) { primaryCompletionTotal = newPrimaryTotal; }

  float getEducationGDP() { return educationGDPSpent; }
  void setEducationGDP(float newGDP) { educationGDPSpent = newGDP; }

  float getYouthLitRateFem() { return youthLitRateFem; }
  void setYouthLitRateFem(float newYouthLitRateFem) { youthLitRateFem = newYouthLitRateFem; }

  float getYouthLitRateMale() { return youthLitRateMale; }
  void setYouthLitRateMale(float newYouthLitRateMale) { youthLitRateMale = newYouthLitRateMale; }
};
