//
//  Aim.hpp
//  GOSX Lite
//
//  Created by Andre Kalisch on 30.03.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef Aim_hpp
#define Aim_hpp

#include "SDK/SDK.h"
#include "SDK/CCSPlayer.h"
#include "Engine/WeaponManager/weapons.h"

class CAim {
public:
    CAim();
    C_CSPlayer* FindTarget(C_CSPlayer* LocalPlayer);
    void StartAim(C_CSPlayer* LocalPlayer, C_CSPlayer* AimTarget, CUserCmd* pCmd);
    void CreateMove(CUserCmd* pCmd);
    static std::map<int, const char*> GetBoneList();
    static std::map<int, const char*> GetBoneValues();
protected:
    void Smooth(QAngle& angle);
    void RCS(QAngle& angle, C_CSPlayer* LocalPlayer, C_CSPlayer* TargetEntity, CUserCmd* pCmd);
    void Reset();
private:
    C_CSPlayer* LockedTargetEntity = nullptr;
};

#endif /* Aim_hpp */
