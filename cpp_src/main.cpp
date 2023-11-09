#include <iostream>
#include <iomanip>
#include "Master.h"

using namespace std;

int main() {
	Master& m = Master::getInstance();
	string tmp;
	int mode;
	while (true) {
		cout << "Select mode(1 - group, 2 - individual): ";
		cin >> tmp;
		mode = atoi(tmp.c_str());
		if (mode == 1 || mode == 2) break;
		cout << "INVALID OPTION!\n";
	}
	int year = 0;
	if (mode == 2) {
		cout << "Year: ";
		cin >> year;
	}
	if (m.parse(mode, year)) {
		cout << "Critical error";
		m.deleteInstance();
		return 0;
	}

	int option = 0;
	bool status = true;

	string country;
	string period;
	int year2;
	string period2;

	while (status) {
		cout << "MENU:" <<
			"\n 1. Number of participants" <<
			"\n 2. Number of disciplines"<<
			"\n 3. Average height"<<
			"\n 4. Average weight"<<
			"\n 5. Number of sports with medal for given country" <<
			"\n 6. Top three countries for games" <<
			"\n 7. Best countries" <<
			"\n 8. Ten youngest players with medal" <<
			"\n 9. Country - Player with both medals" <<
			"\n10. Players for pair of games" <<
			"\n11. Teams for country and games" <<
			"\n12. All cities" <<
			"\n-1. End" <<
			"\n\nChoose option: ";
		cin >> tmp;
		option = atoi(tmp.c_str());
		switch (option) {
		case 1:
			m.filter();
			cout << "Number of participants: " << m.numberOfParticipants() << endl;
			break;
		case 2:
			m.filter();
			cout << "Number of disciplines: " << m.numberOfDisciplines() << endl;
			break;
		case 3:
			m.filter();
			cout << "Average height: " << m.averageHeight() << endl;
			break;
		case 4:
			m.filter();
			cout << "Average weight: " << m.averageWeight() << endl;
			break;
		case 5:
			cout << "Country: ";
			getchar();
			getline(cin, country);
			m.sportsWithMedalsForCountry(country);
			break;
		case 6:
			cout << "Year: ";
			cin >> tmp;
			year = atoi(tmp.c_str());
			cout << "Summer/Winter: ";
			cin >> period;
			for (auto& i : m.topThreeCountriesForGames(year, period)) {
				cout << i.first << ": " << i.second.first << " " << i.second.second.first << " " << i.second.second.second << endl;
			}
			break;
		case 7:
			m.bestCountries();
			break;
		case 8:
			m.tenYoungestWinthMedalFirstTime();
			break;
		case 9:
			for (auto& i : m.getCountryPlayersWithBothMedals()) {
				cout << left << setw(25) << i.first->getName() << " <-> " << *i.second;
			}
			cout << m.getCountryPlayersWithBothMedals().size() << endl;
			break;
		case 10:
			cout << "Year 1: ";
			cin >> tmp;
			year = atoi(tmp.c_str());
			cout << "Summer/Winter: ";
			cin >> period;
			cout << "Year 2: ";
			cin >> tmp;
			year2 = atoi(tmp.c_str());
			cout << "Summer/Winter: ";
			cin >> period2;
			m.playersForPairOfGames(year, period, year2, period2);
			break;
		case 11:
			cout << "Country: ";
			getchar();
			getline(cin, country);
			cout << "Year: ";
			cin >> tmp;
			year = atoi(tmp.c_str());
			cout << "Summer/Winter: ";
			cin >> period;
			for (auto i : m.getTeamsForCountryGame(country, year, period)) {
				cout << i->numberOfPlayers() << " " << i->getDiscipline() << ": ";
				for (auto j : i->getPlayerIds()) {
					cout << j << " ";
				}
				cout << endl;
			}
			break;
		case 12:
			cout << "Cities: \n";
			m.cities();
			break;
		case -1:
			Master::deleteInstance();
			status = false;
			break;
		default:
			cout << "INVALID OPTION!\n";
			break;
		}
	}
	return 0;
}