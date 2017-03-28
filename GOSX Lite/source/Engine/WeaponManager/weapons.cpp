//
//  weapons.cpp
//  GO:SX v3
//
//  Created by Andre Kalisch on 25.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#include "weapons.h"

int CWeaponManager::getDelay(int weaponID) {
    if (isPistol(weaponID) && weaponID != EItemDefinitionIndex::weapon_tec9) {
        return 70;
    }
    
    if (isShotgun(weaponID)) {
        return 30;
    }
    
    if (isSniper(weaponID)) {
        return 100;
    }
    
    return 3;
}

bool CWeaponManager::isKnife(int weaponID) {
    if (
       weaponID == EItemDefinitionIndex::weapon_knife ||
       weaponID == EItemDefinitionIndex::weapon_knife_t ||
       weaponID == EItemDefinitionIndex::weapon_bayonet ||
       weaponID == EItemDefinitionIndex::weapon_knife_flip ||
       weaponID == EItemDefinitionIndex::weapon_knife_gut ||
       weaponID == EItemDefinitionIndex::weapon_knife_karambit ||
       weaponID == EItemDefinitionIndex::weapon_knife_m9_bayonet ||
       weaponID == EItemDefinitionIndex::weapon_knife_tactical ||
       weaponID == EItemDefinitionIndex::weapon_knife_falchion ||
       weaponID == EItemDefinitionIndex::weapon_knife_survival_bowie ||
       weaponID == EItemDefinitionIndex::weapon_knife_butterfly ||
       weaponID == EItemDefinitionIndex::weapon_knife_push
    ) {
        return true;
    }
    
    return false;
}

bool CWeaponManager::IsValidWeapon(int weaponID) {
    return (!isGrenade(weaponID) && !isKnife(weaponID) && !isC4(weaponID));
}

bool CWeaponManager::isGrenade(int weaponID) {
    if (
       weaponID == EItemDefinitionIndex::weapon_flashbang ||
       weaponID == EItemDefinitionIndex::weapon_hegrenade ||
       weaponID == EItemDefinitionIndex::weapon_smokegrenade ||
       weaponID == EItemDefinitionIndex::weapon_molotov ||
       weaponID == EItemDefinitionIndex::weapon_decoy ||
       weaponID == EItemDefinitionIndex::weapon_incgrenade
    ) {
        return true;
    }
    
    return false;
}

bool CWeaponManager::isC4(int weaponID) {
    if (weaponID == EItemDefinitionIndex::weapon_c4) {
        return true;
    }
    
    return false;
}

bool CWeaponManager::isPistol(int weaponID) {
    if (
       weaponID == EItemDefinitionIndex::weapon_deagle ||
       weaponID == EItemDefinitionIndex::weapon_elite ||
       weaponID == EItemDefinitionIndex::weapon_fiveseven ||
       weaponID == EItemDefinitionIndex::weapon_glock ||
       weaponID == EItemDefinitionIndex::weapon_tec9 ||
       weaponID == EItemDefinitionIndex::weapon_taser ||
       weaponID == EItemDefinitionIndex::weapon_hkp2000 ||
       weaponID == EItemDefinitionIndex::weapon_p250 ||
       weaponID == EItemDefinitionIndex::weapon_usp_silencer ||
       weaponID == EItemDefinitionIndex::weapon_cz75a ||
       weaponID == EItemDefinitionIndex::weapon_revolver
    ) {
        return true;
    }
    
    return false;
}

bool CWeaponManager::isShotgun(int weaponID) {
    if(
       weaponID == EItemDefinitionIndex::weapon_xm1014 ||
       weaponID == EItemDefinitionIndex::weapon_mag7 ||
       weaponID == EItemDefinitionIndex::weapon_nova ||
       weaponID == EItemDefinitionIndex::weapon_sawedoff
    ) {
        return true;
    }
    
    return false;
}


bool CWeaponManager::isSniper(int weaponID) {
    if (
       weaponID == EItemDefinitionIndex::weapon_g3sg1 ||
       weaponID == EItemDefinitionIndex::weapon_scar20 ||
       weaponID == EItemDefinitionIndex::weapon_ssg08 ||
       weaponID == EItemDefinitionIndex::weapon_awp
    ) {
        return true;
    }
    
    return false;
}

bool CWeaponManager::needsSmooth(int weaponID) {
    bool ret = true;
    if (isSniper(weaponID)) {
        ret = false;
    }
    
    if (isShotgun(weaponID)) {
        ret = false;
    }
    
    return ret;
}

bool CWeaponManager::isRCSWeapon(int weaponID) {
    bool ret = true;

    if (isSniper(weaponID)) {
        ret = false;
    }
    
    if (isPistol(weaponID) && weaponID != EItemDefinitionIndex::weapon_cz75a) {
        ret = false;
    }
    
    if (isShotgun(weaponID)) {
        ret = false;
    }
    
    return ret;
}

bool CWeaponManager::IsScopeWeapon(int weaponID) {
    if (
        weaponID == EItemDefinitionIndex::weapon_aug ||
        weaponID == EItemDefinitionIndex::weapon_ssg08 ||
        weaponID == EItemDefinitionIndex::weapon_sg556 ||
        weaponID == EItemDefinitionIndex::weapon_g3sg1 ||
        weaponID == EItemDefinitionIndex::weapon_scar20 ||
        weaponID == EItemDefinitionIndex::weapon_awp
    ) {
        return true;
    }

    return false;
}

bool CWeaponManager::isNonAimWeapon(int weaponID) {
    if (
       weaponID == EItemDefinitionIndex::weapon_scar20 ||
       weaponID == EItemDefinitionIndex::weapon_g3sg1
    ) {
        return true;
    }
    
    return false;
}
