#pragma once
#include <string>
#include <vector>
#include "Discipline.h"

using namespace std;

class Competitor;

class Sport
{
	string name;
	vector<Discipline*> disciplines;
	vector<Competitor*> competitors;
public:
	Sport(string name);
	vector<Competitor*>& getCompetitors();
	friend ostream& operator<<(ostream& os, const Sport& s);
};

