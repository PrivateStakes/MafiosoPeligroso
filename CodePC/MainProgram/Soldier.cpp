#include "Soldier.h"

Soldier::Soldier(string fileName, string name, int health) : 
	GameEntity(fileName),
	health(health),
	speed(5)
{	

}

Soldier::~Soldier()
{

}