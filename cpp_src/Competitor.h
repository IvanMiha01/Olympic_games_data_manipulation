#pragma once
#include <string>
#include <vector>
#include "Games.h"
#include "Country.h"
#include "Sport.h"
#include <iostream>

using namespace std;

class Competitor
{
	Games* games;
	Country* country;
	//Discipline* discipline;
	Sport* sport;
	string discipline;
	string medal;
	string type;
public:
	Competitor(Games* games, Country* country, Sport* sport, string discipline, string type, string medal);

	virtual int numberOfPlayers() const = 0;

	string getDiscipline();

	virtual vector<int> getPlayerIds() = 0;

	string getType() const;

	string getMedal() const;

	Games* getGames() const;

	Country* getCountry() const;

	Sport* getSport() const;
};

