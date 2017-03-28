#pragma once
#ifndef feature_chams_h
#define feature_chams_h

#include "SDK/SDK.h"
#include "SDK/Func.h"
#include "SDK/CCSPlayer.h"
#include "Engine/HookManager/hooks.h"

class CChams {
public:
    CChams();
    void apply(
        IMatRenderContext* oriContext,
        const DrawModelState_t &oriState,
        const ModelRenderInfo_t &oriPInfo,
        matrix3x4_t *oriPCustomBoneToWorld
    );
private:
    void ForceMaterial(IMaterial* material, Color color, bool immune);
    void AddMaterial(std::string filename, std::string type, std::string texture, bool ignorez, bool nofog, bool model, bool nocull, bool halflambert, bool gluelook);
    IMaterial* CreateMaterial(bool ignorez, bool flat, bool nofog, bool model, bool nocull, bool halflambert, bool gluelook);
    void* oriContext;
    void* oriState;
    ModelRenderInfo_t oriPInfo;
    matrix3x4_t *oriPCustomBoneToWorld;
    IMaterial* visible_flat = nullptr;
    IMaterial* visible_tex = nullptr;
    IMaterial* hidden_flat = nullptr;
    IMaterial* hidden_tex = nullptr;
    IMaterial* arms = nullptr;
};

#endif // !feature_chams_h

