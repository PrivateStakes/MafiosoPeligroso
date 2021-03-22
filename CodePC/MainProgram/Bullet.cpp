#include "Bullet.h"

Bullet::Bullet(std::string gunName)
{
	if (gunName == "Pistol")
	{
		dmg = 2;
		speed = 20*60;
	}
	else if (gunName == "Minigun")
	{
		dmg = 1;
		speed = 20*60;
	}
	else if (gunName == "Sniper")
	{
		dmg = 5;
		speed = 35*60;
	}
}

Bullet::~Bullet()
{
}

int Bullet::getDamage() const
{
	return this->dmg;
}

float Bullet::getSpeed() const
{
	return this->speed;
}


