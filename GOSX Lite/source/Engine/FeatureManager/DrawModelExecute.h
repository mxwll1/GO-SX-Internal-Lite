#pragma once

#include "Engine/FeatureManager/Features/Chams.h"

namespace FeatureManager {
    void DrawModelExecute(
        IMatRenderContext* context,
        const DrawModelState_t &state,
        const ModelRenderInfo_t &pInfo,
        matrix3x4_t *pCustomBoneToWorld
    );
}
