#pragma once

#ifndef icliententity_h
#define icliententity_h

#include "Definitions.h"
#include "Engine/NetvarManager/nvmngr.h"

#include "IClientNetworkable.h"
#include "IClientRenderable.h"
#include "IClientUnknown.h"
#include "IClientThinkable.h"
#include "SDK.h"

struct SpatializationInfo_t;

class IClientEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable, public IClientThinkable
{
public:
    virtual void             Release(void) = 0;
    virtual const Vector     GetAbsOrigin(void) const = 0;
    virtual const QAngle     GetAbsAngles(void) const = 0;
    virtual void*            GetMouth(void) = 0;
    virtual bool             GetSoundSpatialization(SpatializationInfo_t info) = 0;
    virtual bool             IsBlurred(void) = 0;
};

#endif // !icliententity_h
