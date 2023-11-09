#include "Player.h"
#include <iomanip>

Player::Player(int id, string name, string gender, int years, double height, double weight)
{
	this->id = id;
	this->name = name;
	this->gender = gender;
	this->years = years;
	this->height = height;
	this->weight = weight;
}

double Player::getHeight() const
{
    return height;
}

double Player::getWeight() const
{
	return weight;
}

int Player::getYears() const
{
	return years;
}

ostream& operator<<(ostream& os, const Player& p)
{
	os << right << setw(6) << p.id << " "
		<< left << setw(80) << p.name << "   "
		<< p.gender << "   "
		<< right << setw(3) << p.years << "   "
		<< right << setw(3) << p.height << "   "
		<< right << setw(3) << p.weight << endl;
	return os;
}
