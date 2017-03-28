#pragma once

#ifndef bunnyhop_h
#define bunnyhop_h

#include "SDK/SDK.h"
#include "SDK/CCSPlayer.h"

class CBunnyHop {
public:
    CBunnyHop();
    void run(CUserCmd* pCmd);
private:
    CUserCmd* cmd;
};

#endif // !bunnyhop_h
