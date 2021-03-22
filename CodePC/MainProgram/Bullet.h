#pragma once
#include <iostream>
class Bullet
{
private:
	float speed;
	int dmg;

public:
	Bullet(std::string gunName);
	~Bullet();
	int getDamage()const;
	float getSpeed()const;
};