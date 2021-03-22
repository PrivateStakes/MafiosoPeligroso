#include "WeaponFactory.h"
#include "Weapon.h"
#include "WeaponType.h"
#include "BulletType.h"

WeaponType* WeaponFactory::buildWeapon(GunType gunType)
{
    switch (gunType)
    {
        case GunType::pistol:
            return new WeaponType(&pistolParent);
            break;
        
        case GunType::minigun:
            return new WeaponType(&minigunParent);
        	break;
        
        case GunType::sniper:
            return new WeaponType(&sniperParent);
            break;
    }
}

BulletType* WeaponFactory::buildBulet(std::string gunName, sf::Vector2f direction, sf::Vector2f position, float rotation, int ID)
{
    if (gunName == "Pistol")
    {
        return new BulletType(&pistolBulletParent, direction, position, rotation, ID);
    }
    else  if (gunName == "Minigun")
    {
        return new BulletType(&minigunBulletParent, direction, position, rotation, ID);
    }
    else  if (gunName == "Sniper")
    {
        return new BulletType(&sniperBulletParent, direction, position, rotation, ID);
    }
}

