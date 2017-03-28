//
//  TriggerBot.hpp
//  GOSX Pro
//
//  Created by Andre Kalisch on 19.02.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef TriggerBot_h
#define TriggerBot_h

#include "SDK/SDK.h"
#include "SDK/CCSPlayer.h"
#include "Engine/WeaponManager/weapons.h"

class CTriggerBot {
public:
    CTriggerBot();
    void apply(CUserCmd* pCmd);
};

#endif /* TriggerBot_h */
