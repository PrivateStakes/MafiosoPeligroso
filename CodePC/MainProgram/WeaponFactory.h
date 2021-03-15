#pragma once
#include "Weapon.h"
class WeaponType;

enum class GunType
{
	pistol,
	minigun,
	sniper
};

class WeaponFactory
{	
private:
	Weapon pistolParent = Weapon(2, 30, 1, 30, 35);
	Weapon minigunParent = Weapon(1, 1, 3, 150, 35);
	Weapon sniperParent = Weapon(5, 120, 0, 4, 50);

public:
	WeaponType* buildWeapon(GunType gunType);
};