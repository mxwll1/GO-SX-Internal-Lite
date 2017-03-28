#pragma once

#ifndef iclientmode_h
#define iclientmode_h

#include "Definitions.h"
#include "VMatrix.h"

class IPanel;

enum class ClearFlags_t
{
    VIEW_CLEAR_COLOR = 0x1,
    VIEW_CLEAR_DEPTH = 0x2,
    VIEW_CLEAR_FULL_TARGET = 0x4,
    VIEW_NO_DRAW = 0x8,
    VIEW_CLEAR_OBEY_STENCIL = 0x10,
    VIEW_CLEAR_STENCIL = 0x20,
};


enum class MotionBlurMode_t
{
    MOTION_BLUR_DISABLE = 1,
    MOTION_BLUR_GAME = 2,
    MOTION_BLUR_SFM = 3
};

struct CViewSetup
{
    int x;
    int m_nUnscaledX;
    int y;
    int m_nUnscaledY;
    int width;
    int m_nUnscaledWidth;
    int height;
    char pad_0x0020[0x9C];
    float fov;
    float fovViewmodel;
};

class IClientMode
{
public:
    virtual             ~IClientMode() {}
    virtual int         ClientModeCSNormal(void *) = 0;
    virtual void        Init() = 0;
    virtual void        InitViewport() = 0;
    virtual void        Shutdown() = 0;
    virtual void        Enable() = 0;
    virtual void        Disable() = 0;
    virtual void        Layout() = 0;
    virtual IPanel*     GetViewport() = 0;
    virtual void*       GetViewportAnimationController() = 0;
    virtual void        ProcessInput(bool bActive) = 0;
    virtual bool        ShouldDrawDetailObjects() = 0;
    virtual bool        ShouldDrawEntity(IClientEntity *pEnt) = 0;
    virtual bool        ShouldDrawLocalPlayer(IClientEntity *pPlayer) = 0;
    virtual bool        ShouldDrawParticles() = 0;
    virtual bool        ShouldDrawFog(void) = 0;
    virtual void        OverrideView(CViewSetup *pSetup) = 0; // 16
    virtual int         KeyInput(int down, int keynum, const char *pszCurrentBinding) = 0; // 17
    virtual void        StartMessageMode(int iMessageModeType) = 0; //18
    virtual IPanel*     GetMessagePanel() = 0; //19
    virtual void        OverrideMouseInput(float *x, float *y) = 0; //20
    virtual bool        CreateMove(float flInputSampleTime, void* usercmd) = 0; // 21
    virtual void        LevelInit(const char *newmap) = 0;
    virtual void        LevelShutdown(void) = 0;
};

#endif // !iclientmode_h
