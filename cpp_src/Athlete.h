#pragma once
#include "Player.h"
#include "Competitor.h"

class Athlete : public Competitor
{
	int id;
public:
	int numberOfPlayers() const override;

	Athlete(Games* games, Country* country, Sport* sport, string discipline, string type, string medal, int id);

	vector<int> getPlayerIds() override;
};

