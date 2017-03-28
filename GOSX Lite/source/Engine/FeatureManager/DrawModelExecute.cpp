#include "DrawModelExecute.h"

namespace FeatureManager
{
    CChams* g_pChams = nullptr;

    void DrawModelExecute(IMatRenderContext* context, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld) {
        if (!g_pChams) {
            g_pChams = new CChams();
        }
        g_pChams->apply(context, state, pInfo, pCustomBoneToWorld);
    }
}
