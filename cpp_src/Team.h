#pragma once
#include <vector>
#include "Competitor.h"
#include "Player.h"

class Team : public Competitor
{
	vector<int> ids;
public:
	int numberOfPlayers() const override;
	
	Team(Games* games, Country* country, Sport* sport, string discipline, string type, string medal, vector<int> ids);

	vector<int> getPlayerIds() override;
};

