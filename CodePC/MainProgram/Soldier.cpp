#include "Soldier.h"

Soldier::Soldier(std::string fileName, std::string name, int health):
	GameEntity(fileName),
	health(health),
	speed(5)
{	

}

Soldier::~Soldier()
{

}

void Soldier::loseHealth(int dmg)
{
	this->health -= dmg;
}

int Soldier::getHealth() const
{
	return this->health;
}

int Soldier::getDmg() const
{
	return this->currentWeapon->getDmg();
}
