//
//  Esp.cpp
//  GOSX Pro
//
//  Created by Andre Kalisch on 20.02.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#include "Esp.h"
bool showCrosshair = true;

CEsp::CEsp(CDrawings* drawMngr) {
    DrawManager = drawMngr;
}

void CEsp::DrawESP()
{
    C_CSPlayer* LocalPlayer = C_CSPlayer::GetLocalPlayer();
    if (!LocalPlayer || !LocalPlayer->IsValidLivePlayer()) {
        return;
    }
    
    for (int i = 1; i <= Interfaces::Engine()->GetMaxClients(); i++)
    {
        C_CSPlayer* pPlayer = C_CSPlayer::GetEntity(i);
        if (!pPlayer || !pPlayer->IsValidLivePlayer()) {
            continue;
        }
        
        Color clrTeam = Color(255, 255, 255, 255);
        if (pPlayer->IsVisible(LocalPlayer))
        {
            if (pPlayer->GetTeamNum() == EntityTeam::TEAM_T) {
                clrTeam = INIGET_COLOR("Colors", "color_t_visible");
            } else if (pPlayer->GetTeamNum() == EntityTeam::TEAM_CT) {
                clrTeam = INIGET_COLOR("Colors", "color_ct_visible");
            }
        }
        else
        {
            if (pPlayer->GetTeamNum() == EntityTeam::TEAM_T) {
                clrTeam = INIGET_COLOR("Colors", "color_t");
            } else if (pPlayer->GetTeamNum() == EntityTeam::TEAM_CT) {
                clrTeam = INIGET_COLOR("Colors", "color_ct");
            }
        }
        
        player_info_t info;
        if (!Interfaces::Engine()->GetPlayerInfo(i, &info)) {
            continue;
        }
        
        DrawManager->DynamicBox(pPlayer, info.name, clrTeam);
    }
}
