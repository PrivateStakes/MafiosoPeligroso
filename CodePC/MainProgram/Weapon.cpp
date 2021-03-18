#include "Weapon.h"

Weapon::Weapon(int dmg, int reloadTime, int spreadMultiplier, int ammo, float speed, std::string gunType)
	:dmg(dmg), reloadTime(reloadTime), spreadMultiplier(spreadMultiplier), ammo(ammo), speed(speed), gunType(gunType)
{
}

Weapon::~Weapon()
{
}

std::string Weapon::getGunType() const
{
	return this->gunType;
}

int Weapon::getMaxAmmo() const
{
	return this->ammo;
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

