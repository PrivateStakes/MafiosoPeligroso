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
	Weapon pistolParent = Weapon(2, 30, 1, 30, 20);
	Weapon minigunParent = Weapon(1, 1, 3, 150, 20);
	Weapon sniperParent = Weapon(5, 120, 0, 4, 35);

public:
	WeaponType* buildWeapon(GunType gunType);
};