#include "NPC.h"

NPC::NPC(std::string name, int health, float speed)
	:Soldier("character.png", name, health)
{
	this->sprite.setPosition(600, 600);
}

NPC::~NPC()
{
}

void NPC::update(const float deltaTime)
{
	this->move();
}

void NPC::move()
{
	this->sprite.move((rand() % 3 - 1) * 5, (rand()%3 - 1)* 5);
	this->sprite.setRotation(((rand() % 360) / 180.f) * 3.141592);
}
