#include <iostream>
#include <cstring>

enum class GunType
{
	pistol, 
	shotgun,
	sniper
};

class Weapon
{
private:
	std::string gunType;
	int dmg;
	int reloadTime;
	int spreadMultiplier;
	float speed;
	bool multiShot;

public:
	Weapon(GunType gunType = GunType::pistol);
	~Weapon();

	std::string getGunType()const;
	int getDmg()const;
	int getReloadTime()const;
	int getSpreadMultiplier()const;
	float getSpeed()const;
	bool getMultiShot()const;
};