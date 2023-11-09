#include "Athlete.h"

int Athlete::numberOfPlayers() const
{
	return 1;
}

Athlete::Athlete(Games* games, Country* country, Sport* sport, string discipline, string type, string medal, int id) : Competitor(games,country,sport,discipline,type,medal)
{
	this->id = id;
}

vector<int> Athlete::getPlayerIds()
{
	vector<int> result;
	result.push_back(id);
	return result;
}

