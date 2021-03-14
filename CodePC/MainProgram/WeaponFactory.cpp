#include "WeaponFactory.h"
#include "Weapon.h"
#include "WeaponType.h"

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
