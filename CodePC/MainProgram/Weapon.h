#include <iostream>
#include <cstring>

using namespace std;

enum class GunType
{
	pistol, 
	shotgun,
	sniper
};

class Weapon
{
private:
	string gunType;
	int dmg;
	int reloadTime;
	int spreadMultiplier;
	float speed;
	bool multiShot;

public:
	Weapon(GunType gunType);
	~Weapon();

	string getGunType()const;
	int getDmg()const;
	int getReloadTime()const;
	int getSpreadMultiplier()const;
	float getSpeed()const;
	bool getMultiShot()const;
};