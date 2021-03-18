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
	Weapon pistolParent = Weapon(2, 30, 1, 30, 20, "Pistol");
	Weapon minigunParent = Weapon(1, 3, 3, 150, 20, "Minigun");
	Weapon sniperParent = Weapon(5, 120, 0, 4, 35, "Sniper");

public:
	WeaponType* buildWeapon(GunType gunType);
};