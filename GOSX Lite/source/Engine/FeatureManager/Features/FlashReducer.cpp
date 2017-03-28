//
//  FlashReducer.cpp
//  GOSX Pro
//
//  Created by Andre Kalisch on 22.02.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#include "FlashReducer.h"

CFlashReducer::CFlashReducer() {}

void CFlashReducer::apply() {
    C_CSPlayer* LocalPlayer = C_CSPlayer::GetLocalPlayer();
    if(!LocalPlayer || !LocalPlayer->IsValidLivePlayer()) {
        return;
    }

    float maxFlashAlpha = INIGET_FLOAT("Improvements", "maxflashalpha");
    if(*LocalPlayer->GetMaxFlashAlpha() > maxFlashAlpha) {
        *LocalPlayer->GetMaxFlashAlpha() = maxFlashAlpha;
    }
}
