#include "Sport.h"
#include <iostream>

Sport::Sport(string name)
{
	this->name = name;
}

vector<Competitor*>& Sport::getCompetitors()
{
	return competitors;
}

ostream& operator<<(ostream& os, const Sport& s)
{
	return os << s.name;
}
