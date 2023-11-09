#pragma once
#include <string>
#include <vector>

using namespace std;

class Competitor;

class Country
{
	string name;
	vector<Competitor*> competitors;
public:
	Country(string country);
	vector<Competitor*>& getCompetitors();
	friend ostream& operator<<(ostream& os, const Country& c);
	string getName();
};

