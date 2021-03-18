#include "WeaponType.h"
#include "Weapon.h"

WeaponType::WeaponType(const Weapon* source)
	:copiedWeapon(source)
{
	this->ammo = source->getMaxAmmo();
}

WeaponType::~WeaponType()
{
	copiedWeapon = nullptr;
}

void WeaponType::loseAmmo()
{
	this->ammo--;
}

int WeaponType::getAmmo()
{
	return this->ammo;
}

std::string WeaponType::getGunType() const
{
	return copiedWeapon->getGunType();
}

int WeaponType::getDmg() const
{
	return  copiedWeapon->getDmg();
}

int WeaponType::getReloadTime() const
{
	return  copiedWeapon->getReloadTime();
}

int WeaponType::getSpreadMultiplier() const
{
	return  copiedWeapon->getSpreadMultiplier();
}

float WeaponType::getSpeed() const
{
	return copiedWeapon->getSpeed();
}



