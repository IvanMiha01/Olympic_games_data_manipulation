#pragma once
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class Competitor;

class Games
{
	int year;
	string period;
	string city;
	vector<Competitor*> competitors;
public:
	Games(int year, string period, string city);
	friend ostream& operator<<(ostream& os, const Games& g);
	vector<Competitor*>& getCompetitors();
	string getCity();
	int getYear() const;
};

