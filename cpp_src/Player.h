#pragma once
#include <string>

using namespace std;

class Player
{
	int id;
	string name;
	string gender;
	int years;
	double height;
	double weight;
public:
	Player(int id, string name, string gender, int years, double height, double weight);
	
	double getHeight() const;

	double getWeight() const;

	int getYears() const;

	friend ostream& operator<<(ostream& os, const Player& p);

};

