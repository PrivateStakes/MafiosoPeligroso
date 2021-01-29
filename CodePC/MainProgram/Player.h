#pragma once
#include "Soldier.h"
#include "Bullet.h"
#include "Weapon.h"

class Player : public Soldier
{
private:
	int biggerOrNot(int firstValue, int secondValue);
	Weapon* currentWeapon;
	sf::Vector2f inputDirection;

	int counter;
	bool reloading;

public:
	Player(std::string name = "Joe", int health = 3, float speed = 5.0);
	~Player();

	void rotateSprite(sf::Vector2f pos);
	Bullet shoot(sf::Vector2f pos);
	sf::Vector2f getInputDirection()const;
	bool ableToShoot()const;
	float getRotation()const;

	// Inherited via Soldier
	virtual void update(const float deltaTime) override;

	virtual void move() override;

};