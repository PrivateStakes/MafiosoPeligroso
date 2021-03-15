#pragma once
#include "GameEntity.h"
class Bullet : public GameEntity
{
private:
	float speed;
	float xDir;
	float yDir;

	int dmg;
	int ID;

	void move();
public:
	Bullet(float rotation, sf::Vector2f direction, sf::Vector2f position, int dmg = 1, float speed = 35.0f, int ID = 0);
	~Bullet();
	int getID()const;
	int getDamage()const;
	sf::FloatRect getBounds()const;

	// Inherited via GameEntity
	virtual void update(const float deltaTime) override;
};