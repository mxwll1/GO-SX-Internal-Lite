#include "hooks.h"

namespace HookManager
{
    VMT* g_pPanel       = nullptr;
    VMT* g_pClient      = nullptr;
    VMT* g_pModelRender = nullptr;
    VMT* g_pClientMode  = nullptr;
    VMT* g_pGameEvent   = nullptr;

    CDrawings* drawManager = nullptr;

    void Initialize()
    {
        Functions::MessageBox("GO:SX Lite", "Injected!\n", IDOK);
        Interfaces::Cvar()->ConsolePrintf("GO:SX Lite injected!\n");

        while(!Interfaces::Client()) { usleep(500000); }
        g_pClient       = new VMT(Interfaces::Client());
        while(!Interfaces::Panel()) { usleep(500000); }
        g_pPanel        = new VMT(Interfaces::Panel());
        while(!Interfaces::ModelRender()) { usleep(500000); }
        g_pModelRender  = new VMT(Interfaces::ModelRender());
        while(!Interfaces::ClientMode()) { usleep(500000); }
        g_pClientMode   = new VMT(Interfaces::ClientMode());
        while(!Interfaces::GameEventManager()) { usleep(500000); }
        g_pGameEvent    = new VMT(Interfaces::GameEventManager());

        NetvarManager::Instance()->CreateDatabase();

        g_pPanel->HookVM((void*)HPaintTraverse, INDEX_PAINTTRAVERSE);
        g_pPanel->ApplyVMT();

        while(!Interfaces::Engine()->IsInGame()) {
            usleep(200000);
        }

        g_pClient->HookVM((void*)HFrameStageNotify, INDEX_FRAMESTAGENOTIFY);
        g_pClient->HookVM((void*)HINKeyEvent, INDEX_INKEYEVENT);
        g_pClient->ApplyVMT();

        g_pModelRender->HookVM((void*)HDrawModelExecute, INDEX_DRAWMODELEXECUTE);
        g_pModelRender->ApplyVMT();

        g_pClientMode->HookVM((void*)HCreateMove, INDEX_CREATEMOVE);
        g_pClientMode->ApplyVMT();

        g_pGameEvent->HookVM((void*)HFireEventClientSide, INDEX_FIREEVENTCLIENTSIDE);
        g_pGameEvent->ApplyVMT();


    }

    int HINKeyEvent(void* thisptr, int eventcode, int keynum, const char* currentbinding) {
        if(INIGET_BOOL("Main", "menu")) {
            if(CHackMenu::Instance()->IsMenuOpen()) {
                if(eventcode == InputEventType_t::IE_ButtonReleased) {
                    if(keynum == ButtonCode_t::KEY_DELETE) {
                        CHackMenu::Instance()->CloseMenu();
                        return g_pClient->GetOriginalMethod<KeyEventFn>(20)(thisptr, eventcode, keynum, currentbinding);
                    }

                    if(keynum == ButtonCode_t::MOUSE_LEFT) {
                        CHackMenu::Instance()->SetMouseState(true);
                    } else {
                        CHackMenu::Instance()->HandleInput(keynum);
                    }
                } else if (eventcode == InputEventType_t::IE_ButtonPressed) {
                    if(keynum == ButtonCode_t::MOUSE_LEFT) {
                        CHackMenu::Instance()->SetMousePressed(true);
                    }
                }
                return 0;

            } else if(!CHackMenu::Instance()->IsMenuOpen()) {
                if(eventcode == InputEventType_t::IE_ButtonReleased) {
                    if(keynum == ButtonCode_t::KEY_DELETE) {
                        CHackMenu::Instance()->OpenMenu();
                    }
                }
            }
        }
        return g_pClient->GetOriginalMethod<KeyEventFn>(20)(thisptr, eventcode, keynum, currentbinding);
    }

    void HFrameStageNotify(void* thisptr, ClientFrameStage_t stage) {
        g_pClient->GetOriginalMethod<FrameStageNotifyFn>(36)(thisptr, stage);

        if(stage == ClientFrameStage_t::FRAME_START) {
            if(!CHackMenu::Instance()->IsMenuOpen()) {
                CSettingsManager::Instance("settings.ini")->ReloadSettings();
                CSettingsManager::Instance("menu.ini")->ReloadSettings();
                CSettingsManager::Instance("weapons.ini")->ReloadSettings();
            }
        }

        if(INIGET_BOOL("Main", "enabled")) {
            FeatureManager::FrameStageNotify(stage);
        }
    }
    
    void HPaintTraverse(void* thisptr, VPANEL vguiPanel, bool forceRepaint, bool allowForce) {
        g_pPanel->GetOriginalMethod<PaintTraverseFn>(42)(thisptr, vguiPanel, forceRepaint, allowForce);
        if(INIGET_BOOL("Main", "enabled")) {
            FeatureManager::PaintTraverse(thisptr, vguiPanel, forceRepaint, allowForce);
        }

        if(INIGET_BOOL("Main", "menu")) {
            std::string szPanelName = Interfaces::Panel()->GetName(vguiPanel);
            if (szPanelName.find("FocusOverlayPanel") != std::string::npos) {
                if(CHackMenu::Instance()->IsMenuOpen()) {
                    CHackMenu::Instance()->DrawMenu();
                }
            }
        }
    }

    void HDrawModelExecute(void* thisptr, IMatRenderContext* context, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld) {
        g_pModelRender->ReleaseVMT();

        FeatureManager::DrawModelExecute(context, state, pInfo, pCustomBoneToWorld);

        g_pModelRender->ApplyVMT();
    }
    
    bool HCreateMove(void* thisptr, float sample_input_frametime, CUserCmd* pCmd) {
        g_pClientMode->GetOriginalMethod<CreateMoveFn>(25)(thisptr, sample_input_frametime, pCmd);
        if(INIGET_BOOL("Main", "enabled")) {
            FeatureManager::CreateMove(thisptr, sample_input_frametime, pCmd);
        }
        
        return false;
    }

    bool HFireEventClientSide(IGameEventManager2* thisptr, IGameEvent* event) {
        if(INIGET_BOOL("Main", "enabled")) {
            if(!strcmp(event->GetName(), "cs_game_disconnected")) {
                C_CSPlayer::ResetLocalPlayer();
                return g_pGameEvent->GetOriginalMethod<FireEventClientSideFn>(10)(thisptr, event);
            }
        }

        return g_pGameEvent->GetOriginalMethod<FireEventClientSideFn>(10)(thisptr, event);
    }
}

