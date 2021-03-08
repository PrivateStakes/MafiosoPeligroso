#include "Weapon.h"

Weapon::Weapon(GunType gunType)
{
	switch (gunType)
	{
	case GunType::pistol:
		this->gunType = "Pistol";
		this->dmg = 3;
		this->reloadTime = 1;
		this->spreadMultiplier = 1;
		this->speed = 35.f;
		this->multiShot = false;
		break;

	case GunType::shotgun:
		this->gunType = "Shotgun";
		this->dmg = 1;
		this->reloadTime = 60;
		this->spreadMultiplier = 0;
		this->speed = 25.f;
		this->multiShot = true;
		break;

	case GunType::sniper:
		this->gunType = "Sniper";
		this->dmg = 5;
		this->reloadTime = 120;
		this->spreadMultiplier = 0;
		this->speed = 60.f;
		this->multiShot = false;
		break;
	}
}

Weapon::~Weapon()
{
}

std::string Weapon::getGunType() const
{
	return this->gunType;
}

int Weapon::getDmg() const
{
	return this->dmg;
}

int Weapon::getReloadTime() const
{
	return this->reloadTime;
}

int Weapon::getSpreadMultiplier() const
{
	return this->spreadMultiplier;
}

float Weapon::getSpeed() const
{
	return this->speed;
}

bool Weapon::getMultiShot() const
{
	return this->multiShot;
}

