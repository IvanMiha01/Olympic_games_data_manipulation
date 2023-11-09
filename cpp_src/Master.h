#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <regex>
#include <algorithm>
#include <string>

#include "Competitor.h"
#include "Player.h"
#include "Athlete.h"
#include "Team.h"
#include "Sport.h"

using namespace std;

class Master
{
	vector<Competitor*> competitors;
	set<int> ids;
	map<int, Player*> players;
	map<pair<int, string>, Games*> games;
	map<string, Country*> countries;
	map<string, Sport*> sports;
	vector<Competitor*> filteredCompetitors;
	Master() {}
	static Master* instance;

public:
	static Master& getInstance() {
		if (instance == nullptr) {
			instance = new Master();
		}
		return *instance;
	}

	static void deleteInstance();

	int parse(int mode, int year);

	void filter();


	int numberOfParticipants();
	int numberOfDisciplines();
	double averageHeight();
	double averageWeight();


	void sportsWithMedalsForCountry(string country);

	vector<pair<string, pair<int, pair<int, int>>>> topThreeCountriesForGames(int year, string period);

	void bestCountries();

	void tenYoungestWinthMedalFirstTime();

	vector<pair<Country*, Player*>> getCountryPlayersWithBothMedals();

	void playersForPairOfGames(int year1, string period1, int year2, string period2);

	vector<Competitor*> getTeamsForCountryGame(string country, int year, string period);

	void cities();

};

