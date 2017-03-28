//
//  weapons.hpp
//  GO:SX v3
//
//  Created by Andre Kalisch on 25.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef weapons_hpp
#define weapons_hpp

#include "Common.h"

class CWeaponManager
{
public:
    static int getDelay(int weaponID);
    static std::string getName(int weaponID);
    static bool isKnife(int weaponID);
    static bool isGrenade(int weaponID);
    static bool isC4(int weaponID);
    static bool isPistol(int weaponID);
    static bool isShotgun(int weaponID);
    static bool isSniper(int weaponID);
    static bool needsSmooth(int weaponID);
    static bool isRCSWeapon(int weaponID);
    static bool isNonAimWeapon(int weaponID);
    static bool IsValidWeapon(int weaponID);
    static bool IsScopeWeapon(int weaponID);
};

#endif /* weapons_hpp */
