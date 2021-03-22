#pragma once
#include <iostream>
#include <string.h>
#include <SFML/Graphics.hpp>
#include "GameEntity.h"

class Bullet;

class BulletType : public GameEntity
{
private:
	const Bullet* copiedBullet;

	int ID;
	float xDir;
	float yDir;
	float rotation;

public:
	BulletType(const Bullet* source, sf::Vector2f direction, sf::Vector2f position, float rotation, int ID);
	~BulletType();

	//Functions
	int getID()const;
	float getRotation()const;
	int getDmg()const;

	// Inherited via GameEntity
	virtual void update(const float deltaTime) override;

};