#pragma once
#include "Weapon.h"
#include "Bullet.h"
#include <SFML/Graphics.hpp>
class WeaponType;
class BulletType;

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

	Bullet pistolBulletParent = Bullet("Pistol");
	Bullet minigunBulletParent = Bullet("Minigun");
	Bullet sniperBulletParent = Bullet("Sniper");

public:
	WeaponType* buildWeapon(GunType gunType);
	BulletType* buildBulet(std::string gunType, sf::Vector2f direction, sf::Vector2f position ,float rotation, int ID);
};