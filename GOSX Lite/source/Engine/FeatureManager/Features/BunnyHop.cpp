#include "BunnyHop.h"

CBunnyHop::CBunnyHop() {}

void CBunnyHop::run(CUserCmd* pCmd) {
    C_CSPlayer* localPlayer = C_CSPlayer::GetLocalPlayer();
    if (!localPlayer || !localPlayer->IsValidLivePlayer()) {
        return;
    }

    if(pCmd && pCmd->command_number) {
        if(
            localPlayer->GetMoveType() == MoveType_t::MOVETYPE_LADDER ||
            localPlayer->GetMoveType() == MoveType_t::MOVETYPE_NOCLIP
        ) {
            return;
        }

        if (
            pCmd->buttons & IN_JUMP &&
            !localPlayer->IsOnGround()
        ) {
            pCmd->buttons &= ~IN_JUMP;
        }
    }
}
