#include "Games.h"

Games::Games(int year, string period, string city)
{
	this->year = year;
	this->period = period;
	this->city = city;
}

vector<Competitor*>& Games::getCompetitors()
{
	return competitors;
}

string Games::getCity()
{
	return city;
}

int Games::getYear() const
{
	return year;
}

ostream& operator<<(ostream& os, const Games& g)
{
	os << g.year << " " << g.period << " " << left << setw(20) << g.city;
	return os;
}
