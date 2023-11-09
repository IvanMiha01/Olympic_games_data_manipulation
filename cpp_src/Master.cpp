#include "Master.h"
#include <algorithm>

Master* Master::instance = nullptr;

bool comp(pair<string, pair<int, pair<int, int>>>& p1, pair<string, pair<int, pair<int, int>>>& p2) {
	return p1.second.first > p2.second.first ||
		p1.second.first == p2.second.first && p1.second.second.first > p2.second.second.first ||
		p1.second.first == p2.second.first && p1.second.second.first == p2.second.second.first && p1.second.second.second > p2.second.second.second;
}

void Master::deleteInstance()
{
	Master& master = *instance;
	for (auto& i : master.competitors) delete(i);
	for (auto& i : master.players) delete(i.second);
	for (auto& i : master.games) delete(i.second);
	for (auto& i : master.countries) delete(i.second);
	for (auto& i : master.sports) delete(i.second);
}

int Master::parse(int mode, int selectedYear)
{
	cout << "Path to events.txt file: ";
	string path1;
	cin >> path1;
	ifstream fileE(path1);
	if (!fileE.is_open()) {
		cout << "Invalid path\n";
		return 1;
	}
	string textLineE;
	regex rxe("^([0-9]*) ([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)$");
	while (getline(fileE, textLineE)) {
		smatch result;
		if (regex_match(textLineE, result, rxe)) {
			int year = atoi(result.str(1).c_str());
			if (mode == 2 && year != selectedYear) continue;
			string period = result.str(2);
			string city = result.str(3);
			string sport = result.str(4);
			string discipline = result.str(5);
			string type = result.str(6);
			string country = result.str(7);
			string tmp = result.str(8);
			string medal = result.str(9);

			vector<int> playerIds;
			regex rxi("[0-9]+");
			sregex_iterator tbegin(tmp.begin(), tmp.end(), rxi);
			sregex_iterator tend;
			while (tbegin != tend) {
				smatch sm = *tbegin;
				int id = atoi(sm.str(0).c_str());
				playerIds.push_back(id);
				ids.insert(id);
				tbegin++;
			}

			auto keyg = pair<int, string>(year, period);
			if (games.find(keyg) == games.end()) {
				games[keyg] = new Games(year, period, city);
			}

			string keyc = country;
			if (countries.find(keyc) == countries.end()) {
				countries[keyc] = new Country(country);
			}

			string keys = sport;
			if (sports.find(keys) == sports.end()) {
				sports[keys] = new Sport(sport);
			}

			Competitor* c;
			if (type == "Individual") {
				c = new Athlete(games[keyg], countries[keyc], sports[keys], discipline, type, medal, playerIds[0]);
			}
			else {
				c = new Team(games[keyg], countries[keyc], sports[keys], discipline, type, medal, playerIds);
			}
			competitors.push_back(c);
			games[keyg]->getCompetitors().push_back(c);
			countries[keyc]->getCompetitors().push_back(c);
			sports[keys]->getCompetitors().push_back(c);
		}
		else {
			cout << "\nBad format in line: " << textLineE << endl;
		}
	}

	cout << "Path to athletes.txt file: ";
	string path2;
	cin >> path2;
	ifstream fileA(path2);
	if (!fileA.is_open()) {
		cout << "Invalid path 2\n";
		return 2;
	}
	string textLineA;
	regex rxa("^([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)$");
	while (getline(fileA, textLineA)) {
		smatch result;
		if (regex_match(textLineA, result, rxa)) {
			int id = atoi(result.str(1).c_str());
			if (ids.find(id) == ids.end()) continue;
			string name = result.str(2);
			string gender = result.str(3).c_str();
			int years = atoi(result.str(4).c_str());
			years = years ? years : 999;
			double height = atof(result.str(5).c_str());
			double weight = atof(result.str(6).c_str());
			players[id] = new Player(id, name, gender, years, height, weight);
		}
		else {
			cout << "\nBad format in line: " << textLineA << endl;
		}
	}
	for (auto i : ids) {
		if (players.find(i) == players.end()) {
			cout << "Player with id = " << i << " does not exist in input file, creating default player." << endl;
			players[i] = new Player(i, "NA", "M", 999, 0, 0);
		}
	}
	return 0;
}

void Master::filter()
{
	filteredCompetitors = competitors;
	string option;
	cout << "Filter?(yes/no) ";
	cin >> option;
	if (option != "yes") return;
	cout << "Filter by year(yes/no)? ";
	cin >> option;
	if (option=="yes") {
		int year;
		cout << "Year: ";
		cin >> year;
		if (games.find(make_pair(year, "Summer")) == games.end() && games.find(make_pair(year, "Winter")) == games.end()) {
			filteredCompetitors.erase(filteredCompetitors.begin(), filteredCompetitors.end());
		}
		else {
			auto endy = remove_if(filteredCompetitors.begin(), filteredCompetitors.end(),
				[&](Competitor* c) {
					bool summer = true;
					bool winter = true;
					if (games.find(make_pair(year, "Summer")) != games.end()) {
						if (c->getGames() == games[make_pair(year, "Summer")]) summer = false;
					}
					if (games.find(make_pair(year, "Winter")) != games.end()) {
						if (c->getGames() == games[make_pair(year, "Winter")]) winter = false;
					}
					return summer && winter;
				});
			filteredCompetitors.erase(endy, filteredCompetitors.end());
		}
	}
	cout << "Filter by country(yes/no)? ";
	cin >> option;
	if (option == "yes") {
		string country;
		cout << "Country: ";
		getchar();
		getline(cin, country);
		if (countries.find(country) == countries.end()) {
			filteredCompetitors.erase(filteredCompetitors.begin(), filteredCompetitors.end());
		}
		else {
			auto endc = remove_if(filteredCompetitors.begin(), filteredCompetitors.end(),
				[&](Competitor* c) {return (c->getCountry() != countries[country]);});
			filteredCompetitors.erase(endc, filteredCompetitors.end());
		}
	}
	cout << "Filter by sport(yes/no)? ";
	cin >> option;
	if (option == "yes") {
		string sport;
		cout << "Sport: ";
		cin >> sport;
		if (sports.find(sport) == sports.end()) {
			filteredCompetitors.erase(filteredCompetitors.begin(), filteredCompetitors.end());
		}
		else {
			auto ends = remove_if(filteredCompetitors.begin(), filteredCompetitors.end(),
				[&](Competitor* c) {return (c->getSport() != sports[sport]);});
			filteredCompetitors.erase(ends, filteredCompetitors.end());
		}
	}
	cout << "Filter by type(yes/no)? ";
	cin >> option;
	if (option == "yes") {
		string type;
		cout << "Type: ";
		cin >> type;
		auto endt = remove_if(filteredCompetitors.begin(), filteredCompetitors.end(),
			[&](Competitor* c) {return strcmp(c->getType().c_str(),type.c_str());});
		filteredCompetitors.erase(endt, filteredCompetitors.end());
	}
	cout << "Filter by medal(yes/no)? ";
	cin >> option;
	if (option == "yes") {
		string medal;
		cout << "Medal: ";
		cin >> medal;
		auto endm = remove_if(filteredCompetitors.begin(), filteredCompetitors.end(),
			[&](Competitor* c) {return strcmp(c->getMedal().c_str(), medal.c_str());});
		filteredCompetitors.erase(endm, filteredCompetitors.end());
	}
}


int Master::numberOfParticipants()
{
	int result = 0;
	for_each(filteredCompetitors.begin(), filteredCompetitors.end(), [&result](Competitor* c) {result += c->numberOfPlayers();});
	return result;
}

int Master::numberOfDisciplines()
{
	set<string> disciplines;
	for (auto c : filteredCompetitors) {
		disciplines.insert(c->getDiscipline());
	}
	return disciplines.size();
}

double Master::averageHeight()
{
	double num = 0.0;
	double height = 0;
	for (auto& c : filteredCompetitors) {
		for (auto& i : c->getPlayerIds()) {
			if (players[i]->getHeight() != 0) {
				height += players[i]->getHeight();
				num++;
			}
		}
	}
	return height / num;
}

double Master::averageWeight()
{
	int num = 0;
	double weight = 0;
	for (auto& c : filteredCompetitors) {
		for (auto& i : c->getPlayerIds()) {
			if (players[i]->getWeight() != 0) {
				weight += players[i]->getWeight();
				num++;
			}
		}
	}
	return weight / num;
}


void Master::sportsWithMedalsForCountry(string country)
{
	set<Sport*> result;
	if (countries.find(country) == countries.end()) {
		cout << "Invalid country: " << country << endl;
		return;
	}
	for_each(countries[country]->getCompetitors().begin(), countries[country]->getCompetitors().end(),
		[&](Competitor* c) {
			if (c->getMedal() != "") {
				result.insert(c->getSport());
			}
		});
	cout << "Number of sports with medal for " << country << ": " << result.size() << endl;
}

vector<pair<string, pair<int, pair<int, int>>>> Master::topThreeCountriesForGames(int year, string period)
{
	vector<pair<string, pair<int, pair<int, int>>>> result;
	if (games.find(make_pair(year, period)) == games.end()) {
		cout << "Invalid games\n";
		for (int i = 0;i < 3;i++) {
			result.push_back(make_pair("No country", (make_pair(-1, make_pair(-1, -1)))));
		}
		return result;
	}
	map<string, pair<int, pair<int, int>>> medals;
	string country;
	for (auto c : games[make_pair(year, period)]->getCompetitors()) {
		country = c->getCountry()->getName();
		if (c->getMedal() == "Gold") {
			medals[country].first++;
		}
		if (c->getMedal() == "Silver") {
			medals[country].second.first++;
		}
		if (c->getMedal() == "Bronze") {
			medals[country].second.second++;
		}
	}
	vector<pair<string, pair<int, pair<int, int>>>> tmp;
	for (auto& m : medals) {
		tmp.push_back(m);
	}
	sort(tmp.begin(), tmp.end(), comp);
	/*for (auto& m : tmp) {
		cout << m.first << ": " << m.second.first << " " << m.second.second.first << " " << m.second.second.second << endl;
		if (++i >= 3) break;
	}*/
	
	for (int i = 0;i < 3;i++) {
		if(i <= tmp.size()) {
			result.push_back(tmp[i]);
		}
		else {
			result.push_back(make_pair("No country", (make_pair(0, make_pair(0, 0)))));
		}
	}
	return result;
}

void Master::bestCountries() 
{
	for (auto& i : games) {
		cout << i.second->getYear() << " " << i.second->getCity() << endl;
		auto tmp = topThreeCountriesForGames(i.first.first, i.first.second);
		cout << tmp[0].first<<" "<< tmp[0].second.first << " " << tmp[0].second.second.first << " " << tmp[0].second.second.second << endl;
		cout << tmp[1].first << " " << tmp[1].second.first << " " << tmp[1].second.second.first << " " << tmp[1].second.second.second << endl;
		cout << tmp[2].first << " " << tmp[2].second.first << " " << tmp[2].second.second.first << " " << tmp[2].second.second.second << endl << endl;
	}

	set<string> result;
	for (auto& i : games) {
		result.insert(topThreeCountriesForGames(i.first.first, i.first.second)[0].first);
		if(!comp(topThreeCountriesForGames(i.first.first, i.first.second)[0], topThreeCountriesForGames(i.first.first, i.first.second)[1])) result.insert(topThreeCountriesForGames(i.first.first, i.first.second)[1].first);
		if (!comp(topThreeCountriesForGames(i.first.first, i.first.second)[0], topThreeCountriesForGames(i.first.first, i.first.second)[2])) result.insert(topThreeCountriesForGames(i.first.first, i.first.second)[2].first);
	}
	for (auto& i : result) {
		cout << i << endl;
	}
}

void Master::tenYoungestWinthMedalFirstTime()
{
	map<int, pair<int, bool>> playerFirstYearMedal;

	for (auto i : competitors) {
		for (auto j : i->getPlayerIds()) {
			if (playerFirstYearMedal.find(j) == playerFirstYearMedal.end()) {
				playerFirstYearMedal[j] = make_pair(i->getGames()->getYear(), i->getMedal() != "");
			}
			else{
				if (playerFirstYearMedal[j].first > i->getGames()->getYear() || playerFirstYearMedal[j].first == i->getGames()->getYear() && playerFirstYearMedal[j].first == false) {
					playerFirstYearMedal[j] = make_pair(i->getGames()->getYear(), i->getMedal() != "");
				}
			}
		}
	}

	/*for (auto& i : playerFirstYearMedal) {
		cout << "MEDAL: " << i.second.second << " " << * players[i.first];
	}*/

	vector<int> result;
	for (auto& i : playerFirstYearMedal) {
		if (i.second.second) {
			result.push_back(i.first);
		}
	}
	sort(result.begin(), result.end(), [&](int i, int j) {return players[i]->getYears() < players[j]->getYears();});
	for (int i = 0;i < 10;i++) {
		if ((unsigned)i < result.size()) cout << *players[result[i]];
		else cout << "No player" << endl;
	}
}

vector<pair<Country*, Player*>> Master::getCountryPlayersWithBothMedals()
{
	map<pair<Country*, Player*>, pair<bool, bool>> result;
	for (auto& i : competitors) {
		for (auto j : i->getPlayerIds()) {
			if (i->getType() == "Team") {
				result[make_pair(i->getCountry(), players[j])].first |= i->getMedal() != "";
			}
			else {
				result[make_pair(i->getCountry(), players[j])].second |= i->getMedal() != "";
			}
		}
	}

	vector<pair<Country*, Player*>> retval;
	for (auto& i : result) {
		//cout << "team: " << i.second.first << " individual: "  << i.second.second << " " << *i.first.second;
		if (i.second.first && i.second.second) retval.push_back(i.first);
	}

	return retval;
}

void Master::playersForPairOfGames(int year1, string period1, int year2, string period2)
{
	set<int> result1;
	if (games.find(make_pair(year1, period1)) != games.end()) {
		for (auto i:games[make_pair(year1, period1)]->getCompetitors()) {
			for (auto j : i->getPlayerIds()) {
				result1.insert(j);
			}
		}
	}
	else {
		cout << "Invalid games1\n";
		return;
	}
	set<int> result2;
	if (games.find(make_pair(year2, period2)) != games.end()) {
		for (auto i : games[make_pair(year2, period2)]->getCompetitors()) {
			for (auto j : i->getPlayerIds()) {
				result2.insert(j);
			}
		}
	}
	else {
		cout << "Invalid games2\n";
		return;
	}
	vector<int> result(result1.size(),-1);
	auto newEnd = set_intersection(result1.begin(), result1.end(), result2.begin(), result2.end(), result.begin());
	result.erase(newEnd, result.end());
	for (auto i : result) {
		cout << *players[i];
	}
	cout << "Number of players: " << result.size() << endl;
}

vector<Competitor*> Master::getTeamsForCountryGame(string country, int year, string period)
{
	vector<Competitor*> result;
	if (countries.find(country) == countries.end()) {
		cout << "None from country " << country << endl;
		return result;
	}
	if (games.find(make_pair(year, period)) == games.end()) {
		cout << "None from games " << year << " " << period << endl;
		return result;
	}
	vector<Competitor*> tmpc = countries[country]->getCompetitors();
	sort(tmpc.begin(), tmpc.end(), [](Competitor* c1, Competitor* c2) {return c1 < c2;});
	vector<Competitor*> tmpg = games[make_pair(year, period)]->getCompetitors();
	sort(tmpg.begin(), tmpg.end(), [](Competitor* c1, Competitor* c2) {return c1 < c2;});

	auto end1 = set_intersection(tmpc.begin(), tmpc.end(), tmpg.begin(), tmpg.end(), tmpc.begin(), [](Competitor* c1, Competitor* c2) {return c1 < c2;});
	tmpc.erase(end1, tmpc.end());
	auto end2 = remove_if(tmpc.begin(), tmpc.end(), [](Competitor* c) {return strcmp(c->getType().c_str(), "Team");});
	tmpc.erase(end2, tmpc.end());
	sort(tmpc.begin(), tmpc.end(), [](Competitor* c1, Competitor* c2)
		{
			return c1->numberOfPlayers() > c2->numberOfPlayers() || c1->numberOfPlayers() == c2->numberOfPlayers() && c1->getDiscipline() < c2->getDiscipline();
		});
	return tmpc;
}

void Master::cities()
{
	set<string> cities;
	for (auto& g : games) {
		cities.insert(g.second->getCity());
	}
	for (auto& c : cities) {
		cout << c << endl;
	}
}
