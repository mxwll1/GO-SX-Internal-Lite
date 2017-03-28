#include "CreateMove.h"
#include "SDK/Utils.h"

namespace FeatureManager {
    CBunnyHop* g_cBunnyHop = nullptr;
    CTriggerBot* g_cTriggerBot = nullptr;

    bool CreateMove(void* thisptr, float sample_input_frametime, CUserCmd* pCmd) {
        bool bRet = true;

        if(INIGET_BOOL("Improvements", "bunnyhop")) {
            if (!g_cBunnyHop) {
                g_cBunnyHop = new CBunnyHop();
            }
            g_cBunnyHop->run(pCmd);
        }

        if(INIGET_BOOL("Improvements", "triggerbot")) {
            if(!g_cTriggerBot) {
                g_cTriggerBot = new CTriggerBot();
            }
            g_cTriggerBot->apply(pCmd);
        }

        if(INIGET_BOOL("Improvements", "rankreveal")) {
            if(pCmd->buttons & IN_SCORE) {
                float input[3] = { 0.f };
                Utils::RankRevealAll(input);
            }
        }

        return bRet;
    }
}
