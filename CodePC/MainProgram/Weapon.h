#pragma once
#include <iostream>
#include <cstring>

class Weapon
{
private:
	std::string gunType;
	int dmg;
	int reloadTime;
	int spreadMultiplier;
	int ammo;
	float speed;
	bool multiShot;

public:
	//Weapon(GunType gunType = GunType::pistol);
	Weapon(int dmg, int reloadTime, int spreadMultiplier, int ammo, float speed, std::string gunType);
	~Weapon();
	int getMaxAmmo()const;
	std::string getGunType()const;
	int getDmg()const;
	int getReloadTime()const;
	int getSpreadMultiplier()const;
	float getSpeed()const;
	bool getMultiShot()const;
};