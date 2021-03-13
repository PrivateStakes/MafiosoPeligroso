#include "WeaponFactory.h"
#include "Weapon.h"
#include "WeaponType.h"

WeaponType WeaponFactory::buildWeapon(GunType gunType)
{
    switch (gunType)
    {
        case GunType::pistol:
            return WeaponType(&pistolParent);
            break;
        
        case GunType::minigun:
            return WeaponType(&minigunParent);
        	break;
        
        case GunType::sniper:
            return WeaponType(&sniperParent);
            break;
    }
}
