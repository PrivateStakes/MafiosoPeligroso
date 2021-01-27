#pragma once
#include "GameEntity.h"
class Bullet : public GameEntity
{
private:
	float speed;
	float xDir;
	float yDir;

	int dmg;

	void move();
public:
	Bullet(float rotation, sf::Vector2f direction, sf::Vector2f position, int dmg = 1, float speed = 35.0f);
	~Bullet();

	// Inherited via GameEntity
	virtual void update(const float deltaTime) override;
};