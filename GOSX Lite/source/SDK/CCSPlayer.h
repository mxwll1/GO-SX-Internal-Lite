#pragma once

#ifndef ccsplayer_h
#define ccsplayer_h

#include "SDK.h"
#include "Engine/NetvarManager/nvmngr.h"
#include "CCSWpnInfo.h"

enum MoveType_t
{
    MOVETYPE_NONE = 0,
    MOVETYPE_ISOMETRIC,
    MOVETYPE_WALK,
    MOVETYPE_STEP,
    MOVETYPE_FLY,
    MOVETYPE_FLYGRAVITY,
    MOVETYPE_VPHYSICS,
    MOVETYPE_PUSH,
    MOVETYPE_NOCLIP,
    MOVETYPE_LADDER,
    MOVETYPE_OBSERVER,
    MOVETYPE_CUSTOM,
    MOVETYPE_LAST = MOVETYPE_CUSTOM,
    MOVETYPE_MAX_BITS = 4
};

class C_CSPlayer;

class C_BaseCombatWeapon : public C_BaseEntity
{
    template<class T>
    inline T GetFieldValue(uint64_t offset)
    {
        return *(T*)((uintptr_t)this + offset);
    }

public:
    C_CSPlayer* GetOwner()
    {
        return (C_CSPlayer*)Interfaces::EntityList()->GetClientEntityFromHandle(
            GetFieldValue<CHandle<C_CSPlayer>>(
                GET_NETVAR("DT_BaseCombatCharacter", "m_hActiveWeapon")
            )
        );
    }
    float NextPrimaryAttack()
    {
        uint64_t m_flNextPrimaryAttack = GET_NETVAR("DT_BaseCombatWeapon", "LocalActiveWeaponData", "m_flNextPrimaryAttack");
        return GetFieldValue<float>(m_flNextPrimaryAttack);
    }

    int GetWeaponEntityID()
    {
        uint64_t m_iItemDefinitionIndex = GET_NETVAR("DT_BaseAttributableItem", "m_AttributeManager", "m_Item", "m_iItemDefinitionIndex");
        return GetFieldValue<int>(m_iItemDefinitionIndex);
    }
    
    int GetAmmo() {
        uint64_t m_Clip1 = GET_NETVAR("DT_BaseCombatWeapon", "m_iClip1");
        return GetFieldValue<int>(m_Clip1);
    }

    int* GetViewModelIndex() {
        uint64_t m_iViewModelIndex = GET_NETVAR("DT_BaseCombatWeapon", "m_iViewModelIndex");
        return GetFieldValue<int*>(m_iViewModelIndex);
    }

    CCSWeaponInfo* GetCSWpnData()
    {
        typedef CCSWeaponInfo* (* oGetCSWpnData)(void*);
        return Internal::getvfunc<oGetCSWpnData>(this, 524)(this);
    }
};


class C_CSPlayer : public C_BaseEntity
{
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
    static C_CSPlayer* GetLocalPlayer()
    {
        if(!LocalPlayerInstance) {
            LocalPlayerInstance = (C_CSPlayer*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());
        }

        return LocalPlayerInstance;
    }

    static void ResetLocalPlayer() {
        LocalPlayerInstance = nullptr;
    }

    static C_CSPlayer* GetEntity(int index)
    {
        return (C_CSPlayer*)Interfaces::EntityList()->GetClientEntity(index);
    }

    bool IsValidLivePlayer()
    {
        return !IsDormant() && IsAlive();
    }

    C_BaseCombatWeapon* GetActiveWeapon()
    {
        return (C_BaseCombatWeapon*)Interfaces::EntityList()->GetClientEntityFromHandle(GetFieldValue<CHandle<IClientEntity>>(GET_NETVAR("DT_BaseCombatCharacter", "m_hActiveWeapon")));
    }

    int* GetWeapons()
    {
        return (int*)((uintptr_t)this + GET_NETVAR("DT_BaseCombatCharacter", "m_hMyWeapons"));
    }

    CBaseHandle GetViewModel() {
        uintptr_t m_hViewModel = GET_NETVAR("DT_BasePlayer", "m_hViewModel[0]");
        return GetFieldValue<CBaseHandle>(m_hViewModel);
    }

    int GetHealth()
    {
        return GetFieldValue<int>(GET_NETVAR("DT_BasePlayer", "m_iHealth"));
    }
    bool IsAlive()
    {
        return GetFieldValue<int>(GET_NETVAR("DT_BasePlayer", "m_lifeState")) == 0;
    }
    int GetTeamNum()
    {
        return GetFieldValue<int>(GET_NETVAR("DT_BaseEntity", "m_iTeamNum"));
    }
    int GetFlags()
    {
        return GetFieldValue<int>(GET_NETVAR("DT_BasePlayer", "m_fFlags"));
    }
    bool IsScoped() {
        return GetFieldValue<bool>(GET_NETVAR("DT_CSPlayer", "m_bIsScoped"));
    }
    
    Vector GetViewOffset()
    {
        uint64_t m_vecViewOffset = GET_NETVAR("DT_BasePlayer", "localdata", "m_vecViewOffset[0]");
        return GetFieldValue<Vector>(m_vecViewOffset);
    }

    Vector GetEyePos()
    {
        return GetViewOffset() + GetOrigin();
    }

    Vector GetViewAngle()
    {
        return GetFieldValue<Vector>(GET_NETVAR("DT_BaseEntity", "m_angRotation"));
    }

    Vector ViewPunch()
    {
        uint64_t m_viewPunchAngle = GET_NETVAR("DT_BasePlayer", "localdata", "m_Local", "m_viewPunchAngle");
        return GetFieldValue<Vector>(m_viewPunchAngle);
    }

    Vector AimPunch()
    {
        uint64_t m_aimPunchAngle = GET_NETVAR("DT_BasePlayer", "localdata", "m_Local", "m_aimPunchAngle");
        return GetFieldValue<Vector>(m_aimPunchAngle);
    }
    Vector GetVelocity()
    {
        return GetFieldValue<Vector>(GET_NETVAR("DT_BasePlayer", "localdata", "m_vecVelocity[0]"));
    }
    Vector GetPredictedPosition(int Hitbox)
    {
        return CMath::ExtrapolateTick(this->GetHitboxPosition(Hitbox), this->GetVelocity());
    }
    Vector GetPredictedPosition(Vector HitboxPosition)
    {
        return CMath::ExtrapolateTick(HitboxPosition, this->GetVelocity());
    }
    int GetShotsFired()
    {
        uint64_t m_iShotsFired = GET_NETVAR("DT_CSPlayer", "cslocaldata", "m_iShotsFired");
        return GetFieldValue<int>(m_iShotsFired);
    }
    int GetGlowIndex()
    {
        uint64_t m_iGlowIndex = GET_NETVAR("DT_CSPlayer", "m_flFlashDuration") + 0x18;
        return GetFieldValue<int>(m_iGlowIndex);
    }
    bool GetImmune()
    {
        return GetFieldValue<bool>(GET_NETVAR("DT_CSPlayer", "m_bGunGameImmunity"));
    }

    MoveType_t GetMoveType()
    {
        uint64_t m_MoveType = GET_NETVAR("DT_BaseEntity", "m_nRenderMode") + 0x1;
        return GetFieldValue<MoveType_t>(m_MoveType);
    }

    float* GetMaxFlashAlpha()
    {
        uint64_t m_flMaxFlashAlpha = GET_NETVAR("DT_CSPlayer", "m_flFlashMaxAlpha");
        return GetFieldPointer<float>(m_flMaxFlashAlpha);
    }

    Vector GetHitboxPosition(int Hitbox)
    {
        matrix3x4_t matrix[MAX_STUDIO_BONES];
        if (!this->SetupBones(matrix, MAX_STUDIO_BONES, BONE_USED_BY_HITBOX, Interfaces::GlobalVars()->curtime)) {
            return Vector(0, 0, 0);
        }

        studiohdr_t* hdr = Interfaces::ModelInfo()->GetStudioModel(this->GetModel());
        mstudiohitboxset_t* set = hdr->pHitboxSet(0);
        mstudiobbox_t* hitbox = set->pHitbox(Hitbox);
        if (!hitbox) {
            return Vector(0, 0, 0);
        }

        Vector vMin, vMax, vCenter, sCenter;
        CMath::VectorTransform(hitbox->bbmin, matrix[hitbox->bone], vMin);
        CMath::VectorTransform(hitbox->bbmax, matrix[hitbox->bone], vMax);

        vCenter = (vMin + vMax) * 0.50f;

        return vCenter;
    }

    Vector GetBonePosition(int BoneID)
    {
        matrix3x4_t matrix[MAX_STUDIO_BONES];
        if (!this->SetupBones(matrix, MAX_STUDIO_BONES, BONE_USED_BY_HITBOX, Interfaces::GlobalVars()->curtime)) {
            return Vector(0, 0, 0);
        }

        Vector matrixBone = Vector(
            matrix[BoneID].m_flMatVal[0][3],
            matrix[BoneID].m_flMatVal[1][3],
            matrix[BoneID].m_flMatVal[2][3]
        );

        return matrixBone;
    }
    
    bool IsVisible(C_CSPlayer* localPlayer, Vector position, bool exact = false)
    {
        if(!IsValidLivePlayer()) {
            return false;
        }
        
        trace_t tr;
        Ray_t ray;
        CTraceFilter filter;
        filter.pSkip = localPlayer;
        
        ray.Init(localPlayer->GetEyePos(), position);
        uint32_t RayMask = MASK_SHOT;
        Interfaces::EngineTrace()->TraceRay(ray, RayMask, &filter, &tr);
        
        if (tr.allsolid || tr.startsolid) {
            return false;
        }
        float maxFraction = tr.fraction > 0.99f;
        if(exact) {
            maxFraction = tr.fraction >= 1.f;
        }
        if (tr.m_pEnt)
        {
            if (tr.m_pEnt == this || maxFraction)
            {
                return true;
            }
        }
        
        if (tr.fraction >= 1.0f)
        {
            return true;
        }
        
        return false;
    }
    
    bool IsVisible(C_CSPlayer* localPlayer)
    {
        if(!IsValidLivePlayer()) {
            return false;
        }
        
        Vector Hitbox = GetHitboxPosition(HITBOX_BODY);
        return IsVisible(localPlayer, Hitbox);
    }
    
    bool CanHit(C_CSPlayer* LocalPlayer, int hitbox) {
        if(!IsValidLivePlayer())
        {
            return false;
        }

        Vector traceStart, traceEnd;

        QAngle viewAngles;
        Interfaces::Engine()->GetViewAngles(viewAngles);
        QAngle viewAngles_rcs = viewAngles + LocalPlayer->AimPunch() * 2.0f;

        CMath::AngleVectors(viewAngles_rcs, &traceEnd);

        traceStart = LocalPlayer->GetEyePos();
        traceEnd = traceStart + (traceEnd * 8192.0f);
        
        Ray_t ray;
        trace_t trace;
        CTraceFilter filter;
        filter.pSkip = LocalPlayer;
        
        ray.Init(traceStart, traceEnd);
        Interfaces::EngineTrace()->TraceRay(ray, MASK_SHOT, &filter, &trace);
        
        if (trace.allsolid || trace.startsolid) {
            return false;
        }
        
        if (trace.m_pEnt)
        {
            if (
                trace.m_pEnt == this &&
                trace.hitbox == hitbox &&
                trace.DidHitNonWorldEntity() &&
                this->EntIndex() == trace.GetEntityIndex()
            )
            {
                return true;
            }
        }
        
        return false;
    }
    
    bool IsOnGround()
    {
        return GetFlags() & (int)EntityFlags::FL_ONGROUND;
    }

    const char* GetClan() {
        return Interfaces::PlayerResource()->GetClan(EntIndex());
    }
private:
    static C_CSPlayer* LocalPlayerInstance;
};

class C_PlantedC4 : public C_BaseEntity
{
    template<class T>
    inline T GetFieldValue(uint64_t offset)
    {
        return *(T*)((uintptr_t)this + offset);
    }
public:
    static C_PlantedC4* GetPlantedBomb() {
        for(int i = Interfaces::Engine()->GetMaxClients(); i < Interfaces::EntityList()->GetHighestEntityIndex(); i++) {
            C_BaseEntity* entity = (C_BaseEntity*)Interfaces::EntityList()->GetClientEntity(i);
            if(!entity || entity->IsDormant()) {
                continue;
            }

            if(entity->GetClientClass()->m_ClassID == EClassIds::CPlantedC4) {
                return (C_PlantedC4*)entity;
            }
        }

        return nullptr;
    }

    bool IsBombTicking() {
        uintptr_t m_bBombTicking = GET_NETVAR("DT_PlantedC4", "m_bBombTicking");
        return GetFieldValue<bool>(m_bBombTicking);
    }

    float GetC4Blow() {
        uintptr_t m_flC4Blow = GET_NETVAR("DT_PlantedC4", "m_flC4Blow");
        return GetFieldValue<float>(m_flC4Blow);
    }

    float GetTimerLength() {
        uintptr_t m_flTimerLength = GET_NETVAR("DT_PlantedC4", "m_flTimerLength");
        return GetFieldValue<float>(m_flTimerLength);
    }

    float GetDefuseLength() {
        uintptr_t m_flDefuseLength = GET_NETVAR("DT_PlantedC4", "m_flDefuseLength");
        return GetFieldValue<float>(m_flDefuseLength);
    }

    float GetDefuseCountDown() {
        uintptr_t m_flDefuseCountDown = GET_NETVAR("DT_PlantedC4", "m_flDefuseCountDown");
        return GetFieldValue<float>(m_flDefuseCountDown);
    }

    bool IsBombDefused() {
        uintptr_t m_bBombDefused = GET_NETVAR("DT_PlantedC4", "m_bBombDefused");
        return GetFieldValue<bool>(m_bBombDefused);
    }

    C_CSPlayer* GetBombDefuser() {
        return (C_CSPlayer*)Interfaces::EntityList()->GetClientEntityFromHandle(GetFieldValue<CHandle<IClientEntity>>(GET_NETVAR("DT_BaseCombatCharacter", "m_hBombDefuser")));
    }
};

class C_WeaponC4 : public C_BaseEntity {
    template<class T>
    inline T GetFieldValue(uint64_t offset)
    {
        return *(T*)((uintptr_t)this + offset);
    }
public:
    static C_WeaponC4* GetBomb() {
        for(int i = Interfaces::Engine()->GetMaxClients(); i < Interfaces::EntityList()->GetHighestEntityIndex(); i++) {
            C_BaseEntity* entity = (C_BaseEntity*)Interfaces::EntityList()->GetClientEntity(i);
            if(!entity || entity->IsDormant()) {
                continue;
            }

            if(entity->GetClientClass()->m_ClassID == EClassIds::CC4) {
                return (C_WeaponC4*)entity;
            }
        }

        return nullptr;
    }

    bool IsStartedArming() {
        uintptr_t m_bStartedArming = GET_NETVAR("DT_PlantedC4", "m_bStartedArming");
        return GetFieldValue<bool>(m_bStartedArming);
    }

    bool IsBombPlacedAnimation() {
        uintptr_t m_bBombPlacedAnimation = GET_NETVAR("DT_PlantedC4", "m_bBombPlacedAnimation");
        return GetFieldValue<bool>(m_bBombPlacedAnimation);
    }

    float GetArmedTime() {
        uintptr_t m_fArmedTime = GET_NETVAR("DT_PlantedC4", "m_fArmedTime");
        return GetFieldValue<float>(m_fArmedTime);
    }

    bool IsShowC4Led() {
        uintptr_t m_bShowC4LED = GET_NETVAR("DT_PlantedC4", "m_bShowC4LED");
        return GetFieldValue<bool>(m_bShowC4LED);
    }

    bool IsPlanting() {
        uintptr_t m_bIsPlantingViaUse = GET_NETVAR("DT_PlantedC4", "m_bIsPlantingViaUse");
        return GetFieldValue<bool>(m_bIsPlantingViaUse);
    }
};

class C_BaseAttributableItem : public C_BaseCombatWeapon {
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
    int* GetAccountID() {
        uintptr_t m_iAccountID = GET_NETVAR("DT_BaseAttributableItem", "m_AttributeManager", "m_Item", "m_iAccountID");
        return GetFieldPointer<int>(m_iAccountID);
    }

    int* GetItemDefinitionIndex() {
        uintptr_t m_iItemDefinitionIndex = GET_NETVAR("DT_BaseAttributableItem", "m_AttributeManager", "m_Item", "m_iItemDefinitionIndex");
        return GetFieldPointer<int>(m_iItemDefinitionIndex);
    }

    int* GetItemIDHigh() {
        uintptr_t m_iItemIDHigh = GET_NETVAR("DT_BaseAttributableItem", "m_AttributeManager", "m_Item", "m_iItemIDHigh");
        return GetFieldPointer<int>(m_iItemIDHigh);
    }

    int* GetEntityQuality() {
        uintptr_t m_iEntityQuality = GET_NETVAR("DT_BaseAttributableItem", "m_AttributeManager", "m_Item", "m_iEntityQuality");
        return GetFieldPointer<int>(m_iEntityQuality);
    }

    char* GetCustomName() {
        uintptr_t m_szCustomName = GET_NETVAR("DT_BaseAttributableItem", "m_AttributeManager", "m_Item", "m_szCustomName");
        return GetFieldPointer<char>(m_szCustomName);
    }

    int* GetFallbackPaintKit() {
        uintptr_t m_nFallbackPaintKit = GET_NETVAR("DT_BaseAttributableItem", "m_nFallbackPaintKit");
        return GetFieldPointer<int>(m_nFallbackPaintKit);
    }

    int* GetFallbackSeed() {
        uintptr_t m_nFallbackSeed = GET_NETVAR("DT_BaseAttributableItem", "m_nFallbackSeed");
        return GetFieldPointer<int>(m_nFallbackSeed);
    }

    float* GetFallbackWear() {
        uintptr_t m_flFallbackWear = GET_NETVAR("DT_BaseAttributableItem", "m_flFallbackWear");
        return GetFieldPointer<float>(m_flFallbackWear);
    }

    int* GetFallbackStatTrak() {
        uintptr_t m_nFallbackStatTrak = GET_NETVAR("DT_BaseAttributableItem", "m_nFallbackStatTrak");
        return GetFieldPointer<int>(m_nFallbackStatTrak);
    }
};

class C_BaseViewModel: public C_BaseEntity {
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
    CBaseHandle GetOwner() {
        uintptr_t m_hOwner = GET_NETVAR("DT_BaseViewModel", "m_hOwner");
        return GetFieldValue<CBaseHandle>(m_hOwner);
    }

    int GetWeapon() {
        uintptr_t m_hWeapon = GET_NETVAR("DT_BaseViewModel", "m_hWeapon");
        return GetFieldValue<int>(m_hWeapon);
    }
};

#endif // !ccsplayer_h
