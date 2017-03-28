//
//  TriggerBot.cpp
//  GOSX Pro
//
//  Created by Andre Kalisch on 19.02.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#include "TriggerBot.h"

CTriggerBot::CTriggerBot() {}

void CTriggerBot::apply(CUserCmd *pCmd) {
    if(Interfaces::InputSystem()->IsButtonDown(MOUSE_MIDDLE)) {
        C_CSPlayer* LocalPlayer = C_CSPlayer::GetLocalPlayer();
        if (!LocalPlayer || !LocalPlayer->IsValidLivePlayer()) {
            return;
        }
        
        C_BaseCombatWeapon* active_weapon = LocalPlayer->GetActiveWeapon();
        if (!active_weapon || active_weapon->GetAmmo() == 0 || !CWeaponManager::IsValidWeapon(active_weapon->GetWeaponEntityID())) {
            return;
        }
        
        for(int index = 1; index < Interfaces::Engine()->GetMaxClients(); index++) {
            if (index == Interfaces::Engine()->GetLocalPlayer()) {
                continue;
            }
            
            C_CSPlayer* entity = C_CSPlayer::GetEntity(index);
            if (!entity || !entity->IsValidLivePlayer() || entity->GetImmune()) {
                continue;
            }
            
            for (int hb = 0; hb < HITBOX_RIGHT_THIGH; hb++) {
                if (entity->CanHit(LocalPlayer, hb)) {
                    if (active_weapon->NextPrimaryAttack() > Interfaces::GlobalVars()->curtime)
                    {
                        if (active_weapon->GetWeaponEntityID() == weapon_revolver) {
                            pCmd->buttons &= ~IN_ATTACK2;
                        } else {
                            pCmd->buttons &= ~IN_ATTACK;
                        }
                    }
                    else
                    {
                        if (active_weapon->GetWeaponEntityID() == weapon_revolver) {
                            pCmd->buttons |= IN_ATTACK2;
                        } else {
                            pCmd->buttons |= IN_ATTACK;
                        }
                    }
                }
            }
        }
    }
}
