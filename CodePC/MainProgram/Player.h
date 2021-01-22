#pragma once
#include "Soldier.h"

class Player : public Soldier
{
public:
	Player(string name = "Joe", int health = 3, float speed = 5.0);
	~Player();
	void rotateSprite(sf::Vector2f pos);

	// Inherited via Soldier
	virtual void update(const float deltaTime) override;

	virtual void move() override;

};