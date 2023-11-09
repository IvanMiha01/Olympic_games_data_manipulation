#include "Competitor.h"

Competitor::Competitor(Games* games, Country* country, Sport* sport, string discipline, string type, string medal)
{
	this->games = games;
	this->country = country;
	this->sport = sport;
	this->discipline = discipline;
	this->type = type;
	this->medal = medal;
}

string Competitor::getDiscipline()
{
	return discipline;
}

string Competitor::getType() const
{
	return type;
}

string Competitor::getMedal() const
{
	return medal;
}

Games* Competitor::getGames() const
{
	return games;
}

Country* Competitor::getCountry() const
{
	return country;
}

Sport* Competitor::getSport() const
{
	return sport;
}
