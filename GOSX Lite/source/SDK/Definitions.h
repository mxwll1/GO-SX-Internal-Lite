#pragma once

#ifndef definitions_h
#define definitions_h

#include <assert.h>
#include "Engine/common.h"

#define Assert( _exp ) ((void)0)

typedef void* (*CreateInterfaceFn)(const char *pName, int *pReturnCode);
typedef void* (*InstantiateInterfaceFn)();

typedef void(*pfnDemoCustomDataCallback)(unsigned char *pData, size_t iSize);

typedef unsigned long long VPANEL;
typedef unsigned long long HFONT;
typedef unsigned long long ULONG;

// These are given to FindMaterial to reference the texture groups that show up on the
#define TEXTURE_GROUP_LIGHTMAP						"Lightmaps"
#define TEXTURE_GROUP_WORLD							"World textures"
#define TEXTURE_GROUP_MODEL							"Model textures"
#define TEXTURE_GROUP_VGUI							"VGUI textures"
#define TEXTURE_GROUP_PARTICLE						"Particle textures"
#define TEXTURE_GROUP_DECAL							"Decal textures"
#define TEXTURE_GROUP_SKYBOX						"SkyBox textures"
#define TEXTURE_GROUP_CLIENT_EFFECTS				"ClientEffect textures"
#define TEXTURE_GROUP_OTHER							"Other textures"
#define TEXTURE_GROUP_PRECACHED						"Precached"				// TODO: assign texture groups to the precached materials
#define TEXTURE_GROUP_CUBE_MAP						"CubeMap textures"
#define TEXTURE_GROUP_RENDER_TARGET					"RenderTargets"
#define TEXTURE_GROUP_UNACCOUNTED					"Unaccounted textures"	// Textures that weren't assigned a texture group.
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER          "Static Vertex"
#define TEXTURE_GROUP_STATIC_INDEX_BUFFER			"Static Indices"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_DISP		"Displacement Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_COLOR	"Lighting Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_WORLD	"World Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_MODELS	"Model Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_OTHER	"Other Verts"
#define TEXTURE_GROUP_DYNAMIC_INDEX_BUFFER			"Dynamic Indices"
#define TEXTURE_GROUP_DYNAMIC_VERTEX_BUFFER			"Dynamic Verts"
#define TEXTURE_GROUP_DEPTH_BUFFER					"DepthBuffer"
#define TEXTURE_GROUP_VIEW_MODEL					"ViewModel"
#define TEXTURE_GROUP_PIXEL_SHADERS					"Pixel Shaders"
#define TEXTURE_GROUP_VERTEX_SHADERS				"Vertex Shaders"
#define TEXTURE_GROUP_RENDER_TARGET_SURFACE			"RenderTarget Surfaces"
#define TEXTURE_GROUP_MORPH_TARGETS					"Morph Targets"

#define BONE_USED_MASK				0x0007FF00
#define BONE_USED_BY_ANYTHING		0x0007FF00
#define BONE_USED_BY_HITBOX			0x00000100	// bone (or child) is used by a hit box
#define BONE_USED_BY_ATTACHMENT		0x00000200	// bone (or child) is used by an attachment point
#define BONE_USED_BY_VERTEX_MASK	0x0003FC00
#define BONE_USED_BY_VERTEX_LOD0	0x00000400	// bone (or child) is used by the toplevel model via skinned vertex
#define BONE_USED_BY_VERTEX_LOD1	0x00000800
#define BONE_USED_BY_VERTEX_LOD2	0x00001000
#define BONE_USED_BY_VERTEX_LOD3	0x00002000
#define BONE_USED_BY_VERTEX_LOD4	0x00004000
#define BONE_USED_BY_VERTEX_LOD5	0x00008000
#define BONE_USED_BY_VERTEX_LOD6	0x00010000
#define BONE_USED_BY_VERTEX_LOD7	0x00020000
#define BONE_USED_BY_BONE_MERGE		0x00040000


enum class FontFeature
{
    FONT_FEATURE_ANTIALIASED_FONTS = 1,
    FONT_FEATURE_DROPSHADOW_FONTS = 2,
    FONT_FEATURE_OUTLINE_FONTS = 6,
};

enum class FontDrawType
{
    FONT_DRAW_DEFAULT = 0,
    FONT_DRAW_NONADDITIVE,
    FONT_DRAW_ADDITIVE,
    FONT_DRAW_TYPE_COUNT = 2,
};

enum FontFlags
{
    FONTFLAG_NONE,
    FONTFLAG_ITALIC = 0x001,
    FONTFLAG_UNDERLINE = 0x002,
    FONTFLAG_STRIKEOUT = 0x004,
    FONTFLAG_SYMBOL = 0x008,
    FONTFLAG_ANTIALIAS = 0x010,
    FONTFLAG_GAUSSIANBLUR = 0x020,
    FONTFLAG_ROTARY = 0x040,
    FONTFLAG_DROPSHADOW = 0x080,
    FONTFLAG_ADDITIVE = 0x100,
    FONTFLAG_OUTLINE = 0x200,
    FONTFLAG_CUSTOM = 0x400,
    FONTFLAG_BITMAP = 0x800,
};

enum class EntityFlags
{
    FL_ONGROUND = (1 << 0),
    FL_DUCKING = (1 << 1),
    FL_WATERJUMP = (1 << 2),
    FL_ONTRAIN = (1 << 3),
    FL_INRAIN = (1 << 4),
    FL_FROZEN = (1 << 5),
    FL_ATCONTROLS = (1 << 6),
    FL_CLIENT = (1 << 7),
    FL_FAKECLIENT = (1 << 8)
};

enum EntityTeam
{
    TEAM_NONE   = 0,
    TEAM_SPEC   = 1,
    TEAM_T      = 2,
    TEAM_CT     = 3
};

enum class ClientFrameStage_t
{
    FRAME_UNDEFINED = -1,
    FRAME_START,
    FRAME_NET_UPDATE_START,
    FRAME_NET_UPDATE_POSTDATAUPDATE_START,
    FRAME_NET_UPDATE_POSTDATAUPDATE_END,
    FRAME_NET_UPDATE_END,
    FRAME_RENDER_START,
    FRAME_RENDER_END
};

enum class LifeState
{
    LIFE_ALIVE = 0,// alive
    LIFE_DYING = 1, // playing death animation or still falling off of a ledge waiting to hit ground
    LIFE_DEAD = 2 // dead. lying still.
};

struct WeaponInfo_t {
    float m_flWeaponArmorRatio;
    float m_flPenetration;
    int m_iDamage;
    float m_flRange;
    float m_flRangeModifier;
};

enum EItemDefinitionIndex
{
    weapon_deagle = 1,
    weapon_elite = 2,
    weapon_fiveseven = 3,
    weapon_glock = 4,
    weapon_ak47 = 7,
    weapon_aug = 8,
    weapon_awp = 9,
    weapon_famas = 10,
    weapon_g3sg1 = 11,
    weapon_galilar = 13,
    weapon_m249 = 14,
    weapon_m4a1 = 16,
    weapon_mac10 = 17,
    weapon_p90 = 19,
    weapon_ump45 = 24,
    weapon_xm1014 = 25,
    weapon_bizon = 26,
    weapon_mag7 = 27,
    weapon_negev = 28,
    weapon_sawedoff = 29,
    weapon_tec9 = 30,
    weapon_taser = 31,
    weapon_hkp2000 = 32,
    weapon_mp7 = 33,
    weapon_mp9 = 34,
    weapon_nova = 35,
    weapon_p250 = 36,
    weapon_scar20 = 38,
    weapon_sg556 = 39,
    weapon_ssg08 = 40,
    weapon_knife = 42,
    weapon_flashbang = 43,
    weapon_hegrenade = 44,
    weapon_smokegrenade = 45,
    weapon_molotov = 46,
    weapon_decoy = 47,
    weapon_incgrenade = 48,
    weapon_c4 = 49,
    weapon_knife_t = 59,
    weapon_m4a1_silencer = 60,
    weapon_usp_silencer = 61,
    weapon_cz75a = 63,
    weapon_revolver = 64,
    weapon_bayonet = 500,
    weapon_knife_flip = 505,
    weapon_knife_gut = 506,
    weapon_knife_karambit = 507,
    weapon_knife_m9_bayonet = 508,
    weapon_knife_tactical = 509,
    weapon_knife_falchion = 512,
    weapon_knife_survival_bowie = 514,
    weapon_knife_butterfly = 515,
    weapon_knife_push = 516,
    weapon_max = 517
};

enum EClassIds
{
    CAI_BaseNPC = 0,
    CAK47 = 1,
    CBaseAnimating = 2,
    CBaseAnimatingOverlay = 3,
    CBaseAttributableItem = 4,
    CBaseButton = 5,
    CBaseCSGrenade = 8,
    CBaseCSGrenadeProjectile = 9,
    CBaseCombatCharacter = 6,
    CBaseCombatWeapon = 7,
    CBaseDoor = 10,
    CBaseEntity = 11,
    CBaseFlex = 12,
    CBaseGrenade = 13,
    CBaseParticleEntity = 14,
    CBasePlayer = 15,
    CBasePropDoor = 16,
    CBaseTeamObjectiveResource = 17,
    CBaseTempEntity = 18,
    CBaseToggle = 19,
    CBaseTrigger = 20,
    CBaseVPhysicsTrigger = 22,
    CBaseViewModel = 21,
    CBaseWeaponWorldModel = 23,
    CBeam = 24,
    CBeamSpotlight = 25,
    CBoneFollower = 26,
    CBreakableProp = 27,
    CBreakableSurface = 28,
    CC4 = 29,
    CCSGameRulesProxy = 34,
    CCSPlayer = 35,
    CCSPlayerResource = 36,
    CCSRagdoll = 37,
    CCSTeam = 38,
    CCascadeLight = 30,
    CChicken = 31,
    CColorCorrection = 32,
    CColorCorrectionVolume = 33,
    CDEagle = 39,
    CDecoyGrenade = 40,
    CDecoyProjectile = 41,
    CDynamicLight = 42,
    CDynamicProp = 43,
    CEconEntity = 44,
    CEconWearable = 45,
    CEmbers = 46,
    CEntityDissolve = 47,
    CEntityFlame = 48,
    CEntityFreezing = 49,
    CEntityParticleTrail = 50,
    CEnvAmbientLight = 51,
    CEnvDOFController = 53,
    CEnvDetailController = 52,
    CEnvParticleScript = 54,
    CEnvProjectedTexture = 55,
    CEnvQuadraticBeam = 56,
    CEnvScreenEffect = 57,
    CEnvScreenOverlay = 58,
    CEnvTonemapController = 59,
    CEnvWind = 60,
    CFEPlayerDecal = 61,
    CFireCrackerBlast = 62,
    CFireSmoke = 63,
    CFireTrail = 64,
    CFish = 65,
    CFlashbang = 66,
    CFogController = 67,
    CFootstepControl = 68,
    CFuncAreaPortalWindow = 71,
    CFuncBrush = 72,
    CFuncConveyor = 73,
    CFuncLadder = 74,
    CFuncMonitor = 75,
    CFuncMoveLinear = 76,
    CFuncOccluder = 77,
    CFuncReflectiveGlass = 78,
    CFuncRotating = 79,
    CFuncSmokeVolume = 80,
    CFuncTrackTrain = 81,
    CFunc_Dust = 69,
    CFunc_LOD = 70,
    CGameRulesProxy = 82,
    CHEGrenade = 84,
    CHandleTest = 83,
    CHostage = 85,
    CHostageCarriableProp = 86,
    CIncendiaryGrenade = 87,
    CInferno = 88,
    CInfoLadderDismount = 89,
    CInfoOverlayAccessor = 90,
    CItem_Healthshot = 91,
    CKnife = 92,
    CKnifeGG = 93,
    CLightGlow = 94,
    CMaterialModifyControl = 95,
    CMolotovGrenade = 96,
    CMolotovProjectile = 97,
    CMovieDisplay = 98,
    CParticleFire = 99,
    CParticlePerformanceMonitor = 100,
    CParticleSystem = 101,
    CPhysBox = 102,
    CPhysBoxMultiplayer = 103,
    CPhysMagnet = 106,
    CPhysicsProp = 104,
    CPhysicsPropMultiplayer = 105,
    CPlantedC4 = 107,
    CPlasma = 108,
    CPlayerResource = 109,
    CPointCamera = 110,
    CPointCommentaryNode = 111,
    CPoseController = 112,
    CPostProcessController = 113,
    CPrecipitation = 114,
    CPrecipitationBlocker = 115,
    CPredictedViewModel = 116,
    CPropDoorRotating = 118,
    CPropJeep = 119,
    CPropVehicleChoreoGeneric = 0,
    CPropVehicleDriveable = 120,
    CProp_Hallucination = 117,
    CRagdollManager = 121,
    CRagdollProp = 122,
    CRagdollPropAttached = 123,
    CRopeKeyframe = 124,
    CSCAR17 = 125,
    CSceneEntity = 126,
    CSensorGrenade = 127,
    CSensorGrenadeProjectile = 128,
    CShadowControl = 129,
    CSlideshowDisplay = 130,
    CSmokeGrenade = 131,
    CSmokeGrenadeProjectile = 132,
    CSmokeStack = 133,
    CSpatialEntity = 134,
    CSpotlightEnd = 135,
    CSprite = 136,
    CSpriteOriented = 137,
    CSpriteTrail = 138,
    CStatueProp = 139,
    CSteamJet = 140,
    CSun = 141,
    CSunlightShadowControl = 142,
    CTEArmorRicochet = 145,
    CTEBSPDecal = 158,
    CTEBaseBeam = 146,
    CTEBeamEntPoint = 147,
    CTEBeamEnts = 148,
    CTEBeamFollow = 149,
    CTEBeamLaser = 150,
    CTEBeamPoints = 151,
    CTEBeamRing = 152,
    CTEBeamRingPoint = 153,
    CTEBeamSpline = 154,
    CTEBloodSprite = 155,
    CTEBloodStream = 156,
    CTEBreakModel = 157,
    CTEBubbleTrail = 160,
    CTEBubbles = 159,
    CTEClientProjectile = 161,
    CTEDecal = 162,
    CTEDust = 163,
    CTEDynamicLight = 164,
    CTEEffectDispatch = 165,
    CTEEnergySplash = 166,
    CTEExplosion = 167,
    CTEFireBullets = 168,
    CTEFizz = 169,
    CTEFootprintDecal = 170,
    CTEFoundryHelpers = 171,
    CTEGaussExplosion = 172,
    CTEGlowSprite = 173,
    CTEImpact = 174,
    CTEKillPlayerAttachments = 175,
    CTELargeFunnel = 176,
    CTEMetalSparks = 177,
    CTEMuzzleFlash = 178,
    CTEParticleSystem = 179,
    CTEPhysicsProp = 180,
    CTEPlantBomb = 181,
    CTEPlayerAnimEvent = 182,
    CTEPlayerDecal = 183,
    CTEProjectedDecal = 184,
    CTERadioIcon = 185,
    CTEShatterSurface = 186,
    CTEShowLine = 187,
    CTESmoke = 189,
    CTESparks = 190,
    CTESprite = 191,
    CTESpriteSpray = 192,
    CTEWorldDecal = 195,
    CTeam = 143,
    CTeamplayRoundBasedRulesProxy = 144,
    CTesla = 188,
    CTestTraceline = 194,
    CTest_ProxyToggle_Networkable = 193,
    CTriggerPlayerMovement = 196,
    CTriggerSoundOperator = 197,
    CVGuiScreen = 198,
    CVoteController = 199,
    CWaterBullet = 200,
    CWaterLODControl = 201,
    CWeaponAWP = 203,
    CWeaponAug = 202,
    CWeaponBaseItem = 204,
    CWeaponBizon = 205,
    CWeaponCSBase = 206,
    CWeaponCSBaseGun = 207,
    CWeaponCubemap = 0,
    CWeaponCycler = 208,
    CWeaponElite = 209,
    CWeaponFamas = 210,
    CWeaponFiveSeven = 211,
    CWeaponG3SG1 = 212,
    CWeaponGalil = 213,
    CWeaponGalilAR = 214,
    CWeaponGlock = 215,
    CWeaponHKP2000 = 216,
    CWeaponM249 = 217,
    CWeaponM3 = 218,
    CWeaponM4A1 = 219,
    CWeaponMAC10 = 220,
    CWeaponMP5Navy = 222,
    CWeaponMP7 = 223,
    CWeaponMP9 = 224,
    CWeaponMag7 = 221,
    CWeaponNOVA = 226,
    CWeaponNegev = 225,
    CWeaponP228 = 227,
    CWeaponP250 = 228,
    CWeaponP90 = 229,
    CWeaponSCAR20 = 231,
    CWeaponSG550 = 233,
    CWeaponSG552 = 234,
    CWeaponSG556 = 235,
    CWeaponSSG08 = 236,
    CWeaponSawedoff = 230,
    CWeaponScout = 232,
    CWeaponTMP = 239,
    CWeaponTaser = 237,
    CWeaponTec9 = 238,
    CWeaponUMP45 = 240,
    CWeaponUSP = 241,
    CWeaponXM1014 = 242,
    CWorld = 243,
    DustTrail = 244,
    MovieExplosion = 245,
    NextBotCombatCharacter = 0,
    ParticleSmokeGrenade = 246,
    RocketTrail = 247,
    SmokeTrail = 248,
    SporeExplosion = 249,
    SporeTrail = 250,
};

enum ECSPlayerBones
{
    pelvis = 0,
    spine_0,
    spine_1,
    spine_2,
    spine_3,
    neck_0,
    head_0,
    clavicle_L,
    arm_upper_L,
    arm_lower_L,
    hand_L
};

struct Item_t {
    Item_t(const char* display_name, const char* entity_name, const char* model, const char* killicon = nullptr) {
        this->display_name = display_name;
        this->entity_name = entity_name;
        this->model = model;
        this->killicon = killicon;
    }

    const char* display_name = nullptr;
    const char* entity_name = nullptr;
    const char* model = nullptr;
    const char* killicon = nullptr;
};

//typedef void(*InitKeyValuesFn) (KeyValues*, const char*);
//typedef void(*LoadFromBufferFn) (KeyValues*, const char*, const char*, void*, const char*, void*);

#define MAX_STUDIO_BONES 128
#define MAX_PLAYER_NAME_LENGTH 32
#define SIGNED_GUID_LEN 32

#endif // !definitions_h
