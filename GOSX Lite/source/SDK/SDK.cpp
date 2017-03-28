//
//  SDK.cpp
//  GOSX Pro
//
//  Created by Andre Kalisch on 15.02.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#include "SDK.h"

ISurface*           Interfaces::m_pSurface              = nullptr;
IPanel*             Interfaces::m_pPanel                = nullptr;
ICvar*              Interfaces::m_pCvar                 = nullptr;
IBaseClientDLL*     Interfaces::m_pClient               = nullptr;
IVEngineClient*     Interfaces::m_pEngine               = nullptr;
IClientEntityList*  Interfaces::m_pEntList              = nullptr;
IEngineTrace*       Interfaces::m_pEngineTrace          = nullptr;
IVModelInfo*        Interfaces::m_pModelInfo            = nullptr;
IVModelRender*      Interfaces::m_pModelRender          = nullptr;
IMaterialSystem*    Interfaces::m_pMaterialSystem       = nullptr;
IClientMode*        Interfaces::m_pClientMode           = nullptr;
CGlobalVarsBase*    Interfaces::m_pGlobalVars           = nullptr;
CGlowObjectManager* Interfaces::m_pGlowObjectManager    = nullptr;
IViewRender*        Interfaces::m_pViewRender           = nullptr;
IInputSystem*       Interfaces::m_pInputSystem          = nullptr;
C_CSPlayerResource* Interfaces::m_pPlayerResource       = nullptr;
IVDebugOverlay*     Interfaces::m_pOverlay              = nullptr;
IGameEventManager2* Interfaces::m_pGameEventManager     = nullptr;
IVModelInfoClient*  Interfaces::m_pModelInfoClient      = nullptr;
CBaseClientState*   Interfaces::m_pBaseClientState      = nullptr;
C_CSGameRules*      Interfaces::m_pGameRules            = nullptr;

typedef IClientMode* (*GetClientModeFn) (void);

ISurface* Interfaces::Surface() {
    if(!m_pSurface) {
        m_pSurface = Internal::GetInterface<ISurface>("./bin/osx64/vguimatsurface.dylib", "VGUI_Surface");
    }
    
    return m_pSurface;
}

IPanel* Interfaces::Panel() {
    if(!m_pPanel) {
        m_pPanel = Internal::GetInterface<IPanel>("./bin/osx64/vgui2.dylib", "VGUI_Panel");
    }
    
    return m_pPanel;
}

ICvar* Interfaces::Cvar() {
    if(!m_pCvar) {
        m_pCvar = Internal::GetInterface<ICvar>("./bin/osx64/materialsystem.dylib", "VEngineCvar");
    }
    
    return m_pCvar;
}

CGlobalVarsBase* Interfaces::GlobalVars() {
    if(!m_pGlobalVars) {
        uintptr_t globalVarsPointer = CLIENT_POINTER(
            (Byte*)"\x48\x8D\x05\x00\x00\x00\x00\x48\x8B\x00\xF3\x0F\x10\x00\x00\xF3\x0F\x11\x83\x00\x00\x00\x00",
            "xxx????xxxxxx??xxxx????",
            0x3
        ) + 0x4;
        m_pGlobalVars = *(CGlobalVarsBase**)(globalVarsPointer);
    }
    
    return m_pGlobalVars;
}

IInputSystem* Interfaces::InputSystem() {
    if(!m_pInputSystem) {
        m_pInputSystem = Internal::GetInterface<IInputSystem>("./bin/osx64/inputsystem.dylib", "InputSystemVersion");
    }
    return m_pInputSystem;
}

CGlowObjectManager* Interfaces::GlowObjectManager() {
    if(!m_pGlowObjectManager) {
        uintptr_t glowObjectManagerPointer = CLIENT_POINTER(
            (Byte*)"\x48\x8D\x3D\x00\x00\x00\x05\xE8\x00\x00\x00\x00\x85\xC0\x0F\x84\x00\x00\x00\x00\x48\xC7\x00\x00\x00\x00\x00\x00\x00\x00\x00\x48\x8D\x00\x00\x00\x00\x00",
            "xxx???xx????xxxx????xx?????????xx?????",
            0x22
        ) + 0x4;
        m_pGlowObjectManager = (CGlowObjectManager*)(glowObjectManagerPointer);
    }

    return m_pGlowObjectManager;
}

IBaseClientDLL* Interfaces::Client() {
    if(!m_pClient) {
        m_pClient = Internal::GetInterface<IBaseClientDLL>("./csgo/bin/osx64/client.dylib", "VClient");
    }
    
    return m_pClient;
}

IClientMode* Interfaces::ClientMode() {
    if(!m_pClientMode) {
        uintptr_t clientMode = CLIENT_POINTER(
            (Byte*)"\x48\x8B\xB7\x00\x00\x00\x00\x48\x8D\x3D\x00\x00\x00\x00\x5D\xE9\x23\x29\x00\x00",
            "xxx????xxx????xxxxxx",
            0xA
        ) + 0x4;
        m_pClientMode = (IClientMode*)(clientMode);
    }

    return m_pClientMode;
}

IVEngineClient* Interfaces::Engine() {
    if(!m_pEngine) {
        m_pEngine = Internal::GetInterface<IVEngineClient>("./bin/osx64/engine.dylib", "VEngineClient");
    }
    
    return m_pEngine;
}

IClientEntityList* Interfaces::EntityList() {
    if(!m_pEntList) {
        m_pEntList = Internal::GetInterface<IClientEntityList>("./csgo/bin/osx64/client.dylib", "VClientEntityList");
    }
    
    return m_pEntList;
}

IVDebugOverlay* Interfaces::DebugOverlay() {
    if(!m_pOverlay) {
        m_pOverlay = Internal::GetInterface<IVDebugOverlay>("./bin/osx64/engine.dylib", "VDebugOverlay");
    }
    
    return m_pOverlay;
}

IEngineTrace* Interfaces::EngineTrace() {
    if(!m_pEngineTrace) {
        m_pEngineTrace = Internal::GetInterface<IEngineTrace>("./bin/osx64/engine.dylib", "EngineTraceClient004", true);
    }
    
    return m_pEngineTrace;
}

IVModelInfo* Interfaces::ModelInfo() {
    if(!m_pModelInfo) {
        m_pModelInfo = Internal::GetInterface<IVModelInfo>("./bin/osx64/engine.dylib", "VModelInfoClient");
    }
    
    return m_pModelInfo;
}

IVModelRender* Interfaces::ModelRender() {
    if (!m_pModelRender) {
        m_pModelRender = Internal::GetInterface<IVModelRender>("./bin/osx64/engine.dylib", "VEngineModel");
    }
    return m_pModelRender;
}

IMaterialSystem* Interfaces::MaterialSystem() {
    if (!m_pMaterialSystem) {
        m_pMaterialSystem = Internal::GetInterface<IMaterialSystem>("./bin/osx64/materialsystem.dylib", "VMaterialSystem");
    }
    return m_pMaterialSystem;
}

IViewRender* Interfaces::ViewRender() {
    if(!m_pViewRender) {
        m_pViewRender = Internal::GetInterface<IViewRender>("./bin/osx64/engine.dylib", "VEngineRenderView");
    }
    
    return m_pViewRender;
}

C_CSPlayerResource* Interfaces::PlayerResource() {
    if(!m_pPlayerResource) {
        uintptr_t playerResource = CLIENT_POINTER(
            (Byte*)"\x48\x8D\x05\x00\x00\x00\x00\x48\x8B\x38\x48\x85\xFF\x74\x74",
            "xxx????xxxxxxxx",
            0x3
        ) + 0x4;
        m_pPlayerResource = *(C_CSPlayerResource**)(playerResource);
    }

    return m_pPlayerResource;
}

IGameEventManager2* Interfaces::GameEventManager() {
    if(!m_pGameEventManager) {
        m_pGameEventManager = Internal::GetInterface<IGameEventManager2>("./bin/osx64/engine.dylib", "GAMEEVENTSMANAGER002", true);
    }

    return m_pGameEventManager;
}

IVModelInfoClient* Interfaces::ModelInfoClient() {
    if(!m_pModelInfoClient) {
        m_pModelInfoClient = Internal::GetInterface<IVModelInfoClient>("./bin/osx64/engine.dylib", "VModelInfoClient");
    }

    return m_pModelInfoClient;
}

CBaseClientState* Interfaces::ClientState() {
    if(!m_pBaseClientState) {
        uintptr_t ClientStatePtr = ENGINE_POINTER(
            (Byte*)"\x55\x48\x89\xE5\x48\x8B\x00\x00\x00\x00\x00\x48\x83\x00\x00\x5D\xC3\x66\x66\x66\x66\x66\x66\x2E\x0F\x1F\x84\x00\x00\x00\x00\x00",
            "xxxxxx?????xx??xxxxxxxxxxxxxxxxx",
            0x7
        ) + 0x4;
        m_pBaseClientState = *(CBaseClientState**)(ClientStatePtr);
    }

    return m_pBaseClientState;
}

C_CSGameRules* Interfaces::GameRules() {
    if(!m_pGameRules) {
        uintptr_t CCSGameRulesPointer = CLIENT_POINTER(
            (Byte*)"\x49\x89\xFE\x48\x8D\x05\x00\x00\x00\x00\x48\x8B\x38\x48\x8B\x07",
            "xxxxxx????xxxxxx",
            0x6
        ) + 0x4;
        m_pGameRules = *(C_CSGameRules**)(CCSGameRulesPointer);
    }

    return m_pGameRules;
}
