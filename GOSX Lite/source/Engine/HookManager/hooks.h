#ifndef hooks_h
#define hooks_h

#include "Engine/common.h"
#include "Engine/PatternManager/pattern.h"
#include "Engine/NetvarManager/nvmngr.h"
#include "SDK/SDK.h"
#include "SDK/CCSPlayer.h"
#include "SDK/Utils.h"

#include "Engine/FeatureManager/PaintTraverse.h"
#include "Engine/FeatureManager/DrawModelExecute.h"
#include "Engine/FeatureManager/CreateMove.h"
#include "Engine/FeatureManager/FrameStageNotify.h"

#include "VMT.h"
#include "indexes.h"

namespace HookManager
{
    void Initialize();
    void Restore();

    //---------------------------------------------------
    // Function definitions
    //---------------------------------------------------
    typedef void(*PaintTraverseFn)          (void*, VPANEL, bool, bool);
    typedef void(*FrameStageNotifyFn)       (void*, ClientFrameStage_t);
    typedef void(*DrawModelExecuteFn)       (void*, IMatRenderContext*, const DrawModelState_t&, const ModelRenderInfo_t, matrix3x4_t);
    typedef bool(*CreateMoveFn)             (void*, float, CUserCmd*);
    typedef  int(*KeyEventFn)               (void*, int, int, const char*);
    typedef bool(*FireEventClientSideFn)    (IGameEventManager2*, IGameEvent*);
    
    //---------------------------------------------------
    // Hooked functions
    //---------------------------------------------------
    void HPaintTraverse (void* thisptr, VPANEL vguiPanel, bool forceRepaint, bool allowForce);
    void HFrameStageNotify (void* thisptr, ClientFrameStage_t curStage);
    void HDrawModelExecute (void* thisptr, IMatRenderContext* context, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld);
    bool HCreateMove (void* thisptr, float sample_input_frametime, CUserCmd* pCmd);
     int HINKeyEvent (void* thisptr, int eventcode, int keynum, const char* currentbinding);
    bool HFireEventClientSide(IGameEventManager2* thisptr, IGameEvent* event);
};

#endif // !hooks_h
