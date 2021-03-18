#pragma once
#include <iostream>
#include <string.h>
class Weapon;

class WeaponType
{
private:
	const Weapon* copiedWeapon;
	int ammo;

public:
	WeaponType(const Weapon* source);
	~WeaponType();
	void loseAmmo();
	int getAmmo();
	std::string getGunType()const;
	int getDmg()const;
	int getReloadTime()const;
	int getSpreadMultiplier()const;
	float getSpeed()const;
};