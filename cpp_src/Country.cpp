#include "Country.h"
#include <iomanip>

Country::Country(string name)
{
	this->name = name;
}

vector<Competitor*>& Country::getCompetitors()
{
	return competitors;
}

string Country::getName()
{
	return name;
}

ostream& operator<<(ostream& os, const Country& c)
{
	return os << left << setw(40) << c.name;
}
