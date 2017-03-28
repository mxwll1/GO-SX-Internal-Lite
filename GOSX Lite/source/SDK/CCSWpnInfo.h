//
//  CCSWpnInfo.h
//  GOSX Pro
//
//  Created by Andre Kalisch on 27.03.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef CCSWpnInfo_h
#define CCSWpnInfo_h

#define MAX_SHOOT_SOUNDS 16
#define MAX_WEAPON_STRING 80
#define MAX_WEAPON_PREFIX 16
#define MAX_WEAPON_AMMO_NAME 32

enum WeaponSound_t
{
    EMPTY,
    SINGLE,
    SINGLE_NPC,
    WPN_DOUBLE, // Can't be "DOUBLE" because windows.h uses it.
    DOUBLE_NPC,
    BURST,
    RELOAD,
    RELOAD_NPC,
    MELEE_MISS,
    MELEE_HIT,
    MELEE_HIT_WORLD,
    SPECIAL1,
    SPECIAL2,
    SPECIAL3,
    TAUNT,
    FAST_RELOAD,

    // Add new shoot sound types here
    REVERSE_THE_NEW_SOUND,
    
    NUM_SHOOT_SOUND_TYPES,
};


class CHudTexture;

class FileWeaponInfo_t
{
public:
    FileWeaponInfo_t();

    // Each game can override this to get whatever values it wants from the script.
    virtual void Parse(KeyValues *pKeyValuesData, const char *szWeaponName);

    bool bParsedScript;
    bool bLoadedHudElements;

    char szClassName[MAX_WEAPON_STRING];
    char szPrintName[MAX_WEAPON_STRING];

    char szViewModel[MAX_WEAPON_STRING];
    char szWorldModel[MAX_WEAPON_STRING];
    char szAmmo1[MAX_WEAPON_AMMO_NAME];
    char szWorldDroppedModel[MAX_WEAPON_STRING];
    char szAnimationPrefix[MAX_WEAPON_PREFIX];
    int iSlot;
    int iPosition;
    int iMaxClip1;
    int iMaxClip2;
    int iDefaultClip1;
    int iDefaultClip2;
    int iWeight;
    int iRumbleEffect;
    bool bAutoSwitchTo;
    bool bAutoSwitchFrom;
    int iFlags;
    char szAmmo2[MAX_WEAPON_AMMO_NAME];
    char szAIAddOn[MAX_WEAPON_STRING];

    // Sound blocks
    char aShootSounds[NUM_SHOOT_SOUND_TYPES][MAX_WEAPON_STRING];

    int iAmmoType;
    int iAmmo2Type;
    bool m_bMeleeWeapon;

    // This tells if the weapon was built right-handed (defaults to true).
    // This helps cl_righthand make the decision about whether to flip the model or not.
    bool m_bBuiltRightHanded;
    bool m_bAllowFlipping;

    // Sprite data, read from the data file
    int iSpriteCount;
    CHudTexture* iconActive;
    CHudTexture* iconInactive;
    CHudTexture* iconAmmo;
    CHudTexture* iconAmmo2;
    CHudTexture* iconCrosshair;
    CHudTexture* iconAutoaim;
    CHudTexture* iconZoomedCrosshair;
    CHudTexture* iconZoomedAutoaim;
    CHudTexture* iconSmall;
};

enum class CSWeaponType : int
{
    WEAPONTYPE_KNIFE = 0,
    WEAPONTYPE_PISTOL,
    WEAPONTYPE_SUBMACHINEGUN,
    WEAPONTYPE_RIFLE,
    WEAPONTYPE_SHOTGUN,
    WEAPONTYPE_SNIPER_RIFLE,
    WEAPONTYPE_MACHINEGUN,
    WEAPONTYPE_C4,
    WEAPONTYPE_GRENADE,
    WEAPONTYPE_UNKNOWN
};

class CCSWeaponInfo : public FileWeaponInfo_t
{
public:
    CSWeaponType GetWeaponType()
    {
        return *(CSWeaponType*)((uintptr_t)this + 0x864);
    }

    bool IsFullAuto()
    {
        return *(bool*)((uintptr_t)this + 0x870);
    }

    float GetWeaponArmorRatio()
    {
        return *(float*)((uintptr_t)this + 0x87C);
    }

    float GetMaxPlayerSpeed()
    {
        return *(float*)((uintptr_t)this + 0x880);
    }

    float GetMaxPlayerSpeedAlt()
    {
        return *(float*)((uintptr_t)this + 0x884);
    }

    float GetPenetration()
    {
        return *(float*)((uintptr_t)this + 0x890);
    }

    int GetDamage()
    {
        return *(int*)((uintptr_t)this + 0x894);
    }
    
    float GetRange()
    {
        return *(float*)((uintptr_t)this + 0x898);
    }
    
    float GetRangeModifier()
    {
        return *(float*)((uintptr_t)this + 0x89C);
    }
    
    float GetSpread()
    {
        return *(float*)((uintptr_t)this + 0xA4C);
    }
    
    int GetZoomLevels()
    {
        return *(int*)((uintptr_t)this + 0xEE0);
    }
};

#endif /* CCSWpnInfo_h */
