#ifndef ienginetrace_h
#define ienginetrace_h

#define   DISPSURF_FLAG_SURFACE           (1<<0)
#define   DISPSURF_FLAG_WALKABLE          (1<<1)
#define   DISPSURF_FLAG_BUILDABLE         (1<<2)
#define   DISPSURF_FLAG_SURFPROP1         (1<<3)
#define   DISPSURF_FLAG_SURFPROP2         (1<<4)

#define   CONTENTS_EMPTY                0

#define   CONTENTS_SOLID                0x1
#define   CONTENTS_WINDOW               0x2
#define   CONTENTS_AUX                  0x4
#define   CONTENTS_GRATE                0x8
#define   CONTENTS_SLIME                0x10
#define   CONTENTS_WATER                0x20
#define   CONTENTS_BLOCKLOS             0x40
#define   CONTENTS_OPAQUE               0x80
#define   LAST_VISIBLE_CONTENTS         CONTENTS_OPAQUE

#define   ALL_VISIBLE_CONTENTS            (LAST_VISIBLE_CONTENTS | (LAST_VISIBLE_CONTENTS-1))

#define   CONTENTS_TESTFOGVOLUME        0x100
#define   CONTENTS_UNUSED               0x200
#define   CONTENTS_BLOCKLIGHT           0x400
#define   CONTENTS_TEAM1                0x800
#define   CONTENTS_TEAM2                0x1000
#define   CONTENTS_IGNORE_NODRAW_OPAQUE 0x2000
#define   CONTENTS_MOVEABLE             0x4000
#define   CONTENTS_AREAPORTAL           0x8000
#define   CONTENTS_PLAYERCLIP           0x10000
#define   CONTENTS_MONSTERCLIP          0x20000
#define   CONTENTS_CURRENT_0            0x40000
#define   CONTENTS_CURRENT_90           0x80000
#define   CONTENTS_CURRENT_180          0x100000
#define   CONTENTS_CURRENT_270          0x200000
#define   CONTENTS_CURRENT_UP           0x400000
#define   CONTENTS_CURRENT_DOWN         0x800000

#define   CONTENTS_ORIGIN               0x1000000

#define   CONTENTS_MONSTER              0x2000000
#define   CONTENTS_DEBRIS               0x4000000
#define   CONTENTS_DETAIL               0x8000000
#define   CONTENTS_TRANSLUCENT          0x10000000
#define   CONTENTS_LADDER               0x20000000
#define   CONTENTS_HITBOX               0x40000000

#define   SURF_LIGHT                    0x0001
#define   SURF_SKY2D                    0x0002
#define   SURF_SKY                      0x0004
#define   SURF_WARP                     0x0008
#define   SURF_TRANS                    0x0010
#define   SURF_NOPORTAL                 0x0020
#define   SURF_TRIGGER                  0x0040
#define   SURF_NODRAW                   0x0080

#define   SURF_HINT                     0x0100

#define   SURF_SKIP                     0x0200
#define   SURF_NOLIGHT                  0x0400
#define   SURF_BUMPLIGHT                0x0800
#define   SURF_NOSHADOWS                0x1000
#define   SURF_NODECALS                 0x2000
#define   SURF_NOPAINT                  SURF_NODECALS
#define   SURF_NOCHOP                   0x4000
#define   SURF_HITBOX                   0x8000

// -----------------------------------------------------
// spatial content masks - used for spatial queries (traceline,etc.)
// -----------------------------------------------------
#define   MASK_ALL                      (0xFFFFFFFF)
#define   MASK_SOLID                    (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
#define   MASK_PLAYERSOLID              (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
#define   MASK_NPCSOLID                 (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
#define   MASK_NPCFLUID                 (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER)
#define   MASK_WATER                    (CONTENTS_WATER|CONTENTS_MOVEABLE|CONTENTS_SLIME)
#define   MASK_OPAQUE                   (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_OPAQUE)
#define   MASK_OPAQUE_AND_NPCS          (MASK_OPAQUE|CONTENTS_MONSTER)
#define   MASK_BLOCKLOS                 (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_BLOCKLOS)
#define   MASK_BLOCKLOS_AND_NPCS        (MASK_BLOCKLOS|CONTENTS_MONSTER)
#define   MASK_VISIBLE                  (MASK_OPAQUE|CONTENTS_IGNORE_NODRAW_OPAQUE)
#define   MASK_VISIBLE_AND_NPCS         (MASK_OPAQUE_AND_NPCS|CONTENTS_IGNORE_NODRAW_OPAQUE)
#define   MASK_SHOT                     (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)
#define   MASK_SHOT_BRUSHONLY           (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_DEBRIS)
#define   MASK_SHOT_HULL                (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_GRATE)
#define   MASK_SHOT_PORTAL              (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER)
#define   MASK_SOLID_BRUSHONLY          (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_GRATE)
#define   MASK_PLAYERSOLID_BRUSHONLY    (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_PLAYERCLIP|CONTENTS_GRATE)
#define   MASK_NPCSOLID_BRUSHONLY       (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
#define   MASK_NPCWORLDSTATIC           (CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
#define   MASK_NPCWORLDSTATIC_FLUID     (CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP)
#define   MASK_SPLITAREAPORTAL          (CONTENTS_WATER|CONTENTS_SLIME)
#define   MASK_CURRENT                  (CONTENTS_CURRENT_0|CONTENTS_CURRENT_90|CONTENTS_CURRENT_180|CONTENTS_CURRENT_270|CONTENTS_CURRENT_UP|CONTENTS_CURRENT_DOWN)
#define   MASK_DEADSOLID                (CONTENTS_SOLID|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_GRATE)

enum TraceType_t /* Taken from GamerFood's TraceEngine. Credits to him! */
{
    TRACE_EVERYTHING = 0,
    TRACE_WORLD_ONLY,				// NOTE: This does *not* test static props!!!
    TRACE_ENTITIES_ONLY,			// NOTE: This version will *not* test static props
    TRACE_EVERYTHING_FILTER_PROPS,	// NOTE: This version will pass the IHandleEntity for props through the filter, unlike all other filters
};

struct Ray_t
{
    Ray_t( ) { }
    
    VectorAligned		m_Start;
    VectorAligned		m_Delta;
    VectorAligned		m_StartOffset;
    VectorAligned		m_Extents;
    const matrix3x4_t	*m_pWorldAxisTransform;
    bool				m_IsRay;
    bool				m_IsSwept;
    
    void Init( Vector vecStart, Vector vecEnd )
    {
        m_Delta = VectorAligned( vecEnd - vecStart );
        m_IsSwept = ( m_Delta.LengthSqr( ) != 0 );
        m_Extents.Zero( );
        m_pWorldAxisTransform = NULL;
        m_IsRay = true;
        m_StartOffset.Zero( );
        m_Start = vecStart;
    }
};

class ITraceFilter
{
public:
    virtual bool ShouldHitEntity( IClientEntity* pEntityHandle, int contentsMask )
    {
        return !( pEntityHandle == pSkip );
    }
    virtual TraceType_t	GetTraceType( )
    {
        return TRACE_EVERYTHING;
    }
    void* pSkip;
};

class CTraceFilter : public ITraceFilter
{
public:
    virtual bool ShouldHitEntity( IClientEntity* pEntityHandle, int contentsMask )
    {
        return !( pEntityHandle == pSkip );
    }
    
    virtual TraceType_t	GetTraceType( ) const
    {
        return TRACE_EVERYTHING;
    }
    void* pSkip;
};

class CTraceFilterSkipTwoEntities : public ITraceFilter
{
public:
    CTraceFilterSkipTwoEntities( void *pPassEnt1, void *pPassEnt2 )
    {
        pPassEntity1 = pPassEnt1;
        pPassEntity2 = pPassEnt2;
    }
    
    virtual bool ShouldHitEntity( IClientEntity *pEntityHandle, int contentsMask )
    {
        return !( pEntityHandle == pPassEntity1 || pEntityHandle == pPassEntity2 );
    }
    
    virtual TraceType_t GetTraceType( ) const
    {
        return TRACE_EVERYTHING;
    }
    
    void *pPassEntity1;
    void *pPassEntity2;
};

typedef bool( *ShouldHitFunc_t )( IHandleEntity *pHandleEntity, int contentsMask );

class CTraceFilterSimple : public CTraceFilter
{
public:
    // It does have a base, but we'll never network anything below here..
    CTraceFilterSimple( const IHandleEntity *passentity, int collisionGroup, ShouldHitFunc_t pExtraShouldHitCheckFn = NULL );
    virtual bool ShouldHitEntity( IHandleEntity *pHandleEntity, int contentsMask );
    virtual void SetPassEntity( const IHandleEntity *pPassEntity ) { m_pPassEnt = pPassEntity; }
    virtual void SetCollisionGroup( int iCollisionGroup ) { m_collisionGroup = iCollisionGroup; }
    const IHandleEntity *GetPassEntity( void ){ return m_pPassEnt; }
private:
    const IHandleEntity *m_pPassEnt;
    int m_collisionGroup;
    ShouldHitFunc_t m_pExtraShouldHitCheckFunction;
};

class CBaseTrace
{
public:
    Vector			startpos;
    Vector			endpos;
    cplane_t		plane;
    float			fraction;
    int				contents;
    unsigned short	dispFlags;
    bool			allsolid;
    bool			startsolid;
    CBaseTrace( ) {}
};

struct csurface_t
{
    const char*		name;
    short			surfaceProps;
    unsigned short	flags;
};

class CGameTrace : public CBaseTrace
{
public:
    bool                    DidHitWorld() const;
    bool                    DidHitNonWorldEntity() const;
    int                     GetEntityIndex() const;
    bool                    DidHit() const;
    bool					IsVisible() const;
    
public:
    
    float                   fractionleftsolid;
    csurface_t              surface;
    int                     hitgroup;
    short                   physicsbone;
    unsigned short          worldSurfaceIndex;
    IClientEntity*          m_pEnt;
    int                     hitbox;
    
    CGameTrace() { }
    
private:
    CGameTrace( const CGameTrace& vOther );
};

typedef CGameTrace trace_t;

class IEngineTrace {
public:
    // Returns the contents mask + entity at a particular world-space position
    virtual int GetPointContents(const Vector &vecAbsPosition, int contentsMask = MASK_ALL, IHandleEntity** ppEntity = NULL) = 0;
    
    // Returns the contents mask of the world only @ the world-space position (static props are ignored)
    virtual int GetPointContents_WorldOnly(const Vector &vecAbsPosition, int contentsMask = MASK_ALL) = 0;
    
    // Get the point contents, but only test the specific entity. This works
    // on static props and brush models.
    //
    // If the entity isn't a static prop or a brush model, it returns CONTENTS_EMPTY and sets
    // bFailed to true if bFailed is non-null.
    virtual int GetPointContents_Collideable(ICollideable *pCollide, const Vector &vecAbsPosition) = 0;
    
    // Traces a ray against a particular entity
    virtual void ClipRayToEntity(const Ray_t &ray, unsigned int fMask, IHandleEntity *pEnt, trace_t *pTrace) = 0;
    
    // Traces a ray against a particular entity
    virtual void ClipRayToCollideable(const Ray_t &ray, unsigned int fMask, ICollideable *pCollide, trace_t *pTrace) = 0;
    
    // A version that simply accepts a ray (can work as a traceline or tracehull)
    virtual void TraceRay(const Ray_t &ray, unsigned int fMask, ITraceFilter *pTraceFilter, trace_t *pTrace) = 0;
};

#endif // !ienginetrace_h
