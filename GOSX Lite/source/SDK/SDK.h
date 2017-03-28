//
//  SDK.hpp
//  GOSX Pro
//
//  Created by Andre Kalisch on 15.02.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef SDK_h
#define SDK_h

#include "Engine/common.h"

#include "Definitions.h"
#include "Vector.h"
#include "Vector2D.h"
#include "Vector4D.h"
#include "QAngle.h"
#include "CHandle.h"
#include "CGlobalVarsBase.h"
#include "ClientClass.h"
#include "Color.h"
#include "IBaseClientDll.h"
#include "IClientEntity.h"
#include "IClientEntityList.h"
#include "IClientNetworkable.h"
#include "IClientRenderable.h"
#include "IClientThinkable.h"
#include "IClientUnknown.h"
#include "internal.h"
#include "IMaterial.h"
#include "VMatrix.h"
#include "CBaseEntity.h"
#include "IVModelInfo.h"
#include "IVModelInfoClient.h"
#include "IVModelRender.h"
#include "IPanel.h"
#include "ISurface.h"
#include "IVEngineClient.h"
#include "IEngineTrace.h"
#include "IEngineVGui.h"
#include "PlayerInfo.h"
#include "Recv.h"
#include "IClientMode.h"
#include "IVDebugOverlay.h"
#include "CInput.h"
#include "ICvar.h"
#include "CMath.h"
#include "IRenderView.h"
#include "VPlane.h"
#include "IViewRender.h"
#include "CUtlMemory.h"
#include "CUtlVector.h"
#include "CGlowObjectManager.h"
#include "IInputSystem.h"
#include "IGameEvent.h"
#include "IGameEventManager2.h"
#include "CPlayerResource.h"
#include "KeyValues.h"
#include "IGameUI.h"
#include "CBaseClientState.h"
#include "CCSGameRules.h"
#include "Engine/PatternManager/pattern.h"

class Interfaces {
public:
    static ISurface* Surface();
    static IPanel* Panel();
    static ICvar* Cvar();
    static IBaseClientDLL* Client();
    static IVEngineClient* Engine();
    static IClientEntityList* EntityList();
    static IEngineTrace* EngineTrace();
    static IVModelInfo* ModelInfo();
    static IVModelRender* ModelRender();
    static IMaterialSystem* MaterialSystem();
    static IClientMode* ClientMode();
    static CGlobalVarsBase* GlobalVars();
    static CGlowObjectManager* GlowObjectManager();
    static IViewRender* ViewRender();
    static IInputSystem* InputSystem();
    static IEngineVGui* EngineVGui();
    static C_CSPlayerResource* PlayerResource();
    static IVDebugOverlay* DebugOverlay();
    static IGameUI* GameUI();
    static IGameEventManager2* GameEventManager();
    static IVModelInfoClient* ModelInfoClient();
    static CBaseClientState* ClientState();
    static C_CSGameRules* GameRules();
protected:
    static ISurface* m_pSurface;
    static IPanel* m_pPanel;
    static ICvar* m_pCvar;
    static IBaseClientDLL* m_pClient;
    static IVEngineClient* m_pEngine;
    static IClientEntityList* m_pEntList;
    static IEngineTrace* m_pEngineTrace;
    static IVModelInfo* m_pModelInfo;
    static IVModelRender* m_pModelRender;
    static IMaterialSystem* m_pMaterialSystem;
    static IClientMode* m_pClientMode;
    static CGlobalVarsBase* m_pGlobalVars;
    static CGlowObjectManager* m_pGlowObjectManager;
    static IViewRender* m_pViewRender;
    static IInputSystem* m_pInputSystem;
    static IEngineVGui* m_pEngineVGui;
    static C_CSPlayerResource* m_pPlayerResource;
    static IVDebugOverlay* m_pOverlay;
    static IGameUI* m_pGameUi;
    static IGameEventManager2* m_pGameEventManager;
    static IVModelInfoClient* m_pModelInfoClient;
    static CBaseClientState* m_pBaseClientState;
    static C_CSGameRules* m_pGameRules;
};

#endif /* SDK_hpp */
