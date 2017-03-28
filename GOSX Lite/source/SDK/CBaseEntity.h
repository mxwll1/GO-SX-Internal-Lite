//
//  CBaseEntity.h
//  GOSX Pro
//
//  Created by Andre Kalisch on 20.03.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef CBaseEntity_h
#define CBaseEntity_h

#include "IClientEntity.h"

class C_BaseEntity : public IClientEntity {
    template<class T>
    inline T GetFieldValue(uint64_t offset)
    {
        return *(T*)((uintptr_t)this + offset);
    }

    template<class T>
    T* GetFieldPointer(uint64_t offset)
    {
        return (T*)((uintptr_t)this + offset);
    }
public:
    int* GetModelIndex() {
        uintptr_t m_nModelIndex = GET_NETVAR("DT_BaseEntity", "m_nModelIndex");
        return GetFieldPointer<int>(m_nModelIndex);
    }

    bool IsPlayer() {
        return (GetClientClass()->m_ClassID == EClassIds::CCSPlayer);
    }

    bool IsChicken() {
        return (GetClientClass()->m_ClassID == EClassIds::CChicken);
    }

    bool IsWeapon() {
        switch(GetClientClass()->m_ClassID) {
            case EClassIds::CAK47:
            case EClassIds::CDEagle:
            case EClassIds::CKnife:
            case EClassIds::CKnifeGG:
            case EClassIds::CSCAR17:
            case EClassIds::CWeaponAug:
            case EClassIds::CWeaponAWP:
            case EClassIds::CWeaponBizon:
            case EClassIds::CWeaponElite:
            case EClassIds::CWeaponFamas:
            case EClassIds::CWeaponFiveSeven:
            case EClassIds::CWeaponG3SG1:
            case EClassIds::CWeaponGalil:
            case EClassIds::CWeaponGalilAR:
            case EClassIds::CWeaponGlock:
            case EClassIds::CWeaponHKP2000:
            case EClassIds::CWeaponM249:
            case EClassIds::CWeaponM3:
            case EClassIds::CWeaponM4A1:
            case EClassIds::CWeaponMAC10:
            case EClassIds::CWeaponMag7:
            case EClassIds::CWeaponMP5Navy:
            case EClassIds::CWeaponMP7:
            case EClassIds::CWeaponMP9:
            case EClassIds::CWeaponNegev:
            case EClassIds::CWeaponNOVA:
            case EClassIds::CWeaponP228:
            case EClassIds::CWeaponP250:
            case EClassIds::CWeaponP90:
            case EClassIds::CWeaponSawedoff:
            case EClassIds::CWeaponSCAR20:
            case EClassIds::CWeaponScout:
            case EClassIds::CWeaponSG550:
            case EClassIds::CWeaponSG552:
            case EClassIds::CWeaponSG556:
            case EClassIds::CWeaponSSG08:
            case EClassIds::CWeaponTaser:
            case EClassIds::CWeaponTec9:
            case EClassIds::CWeaponTMP:
            case EClassIds::CWeaponUMP45:
            case EClassIds::CWeaponUSP:
            case EClassIds::CWeaponXM1014:
                return true;
                break;
            default:
                return false;
                break;
        }
    }

    bool IsBomb() {
        return (GetClientClass()->m_ClassID == EClassIds::CC4);
    }

    bool IsPlantedBomb() {
        return (GetClientClass()->m_ClassID == EClassIds::CPlantedC4);
    }

    bool IsGrenade() {
        switch(GetClientClass()->m_ClassID) {
            case EClassIds::CDecoyGrenade:
            case EClassIds::CFlashbang:
            case EClassIds::CHEGrenade:
            case EClassIds::CMolotovGrenade:
            case EClassIds::CSmokeGrenade:
                return true;
                break;
            default:
                return false;
                break;
        }
    }

    bool IsHostage() {
        return (GetClientClass()->m_ClassID == EClassIds::CHostage);
    }

    bool IsGlowEntity() {
        return (
            IsPlantedBomb()
        );
    }

    Vector GetOrigin()
    {
        uint64_t m_vecOrigin = GET_NETVAR("DT_BaseEntity", "m_vecOrigin");
        return GetFieldValue<Vector>(m_vecOrigin);
    }

    Vector GetVecMins()
    {
        uint64_t m_vecMins = GET_NETVAR("DT_BaseEntity", "m_Collision", "m_vecMins");
        return GetFieldValue<Vector>(m_vecMins);
    }
    Vector GetVecMaxs()
    {
        uint64_t m_vecMaxs = GET_NETVAR("DT_BaseEntity", "m_Collision", "m_vecMaxs");
        return GetFieldValue<Vector>(m_vecMaxs);
    }
    matrix3x4_t GetRgflCoordinateFrame()
    {
        uint64_t m_rgflCoordinateFrame = GET_NETVAR("DT_BaseEntity", "m_CollisionGroup") - 0x30;
        return GetFieldValue<matrix3x4_t>(m_rgflCoordinateFrame);
    }

    bool* GetShouldGlow() {
        uintptr_t m_bShouldGlow = GET_NETVAR("DT_DynamicProp", "m_bShouldGlow");
        return GetFieldPointer<bool>(m_bShouldGlow);
    }
};

#endif /* CBaseEntity_h */
