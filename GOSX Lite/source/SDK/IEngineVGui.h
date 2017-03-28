//
//  IEngineVGui.h
//  GOSX Pro
//
//  Created by Andre Kalisch on 22.02.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef IEngineVGui_h
#define IEngineVGui_h

#pragma once

enum VGuiPanel_t
{
    PANEL_ROOT = 0,
    PANEL_GAMEUIDLL,
    PANEL_CLIENTDLL,
    PANEL_TOOLS,
    PANEL_INGAMESCREENS,
    PANEL_GAMEDLL,
    PANEL_CLIENTDLL_TOOLS
};

enum PaintMode_t
{
    PAINT_UIPANELS = (1 << 0),
    PAINT_INGAMEPANELS = (1 << 1),
    PAINT_CURSOR = (1 << 2)
};

class IEngineVGui
{
public:
    virtual ~IEngineVGui(void) {}
    virtual VPANEL GetPanel(VGuiPanel_t type) = 0;
    virtual bool IsGameUIVisible() = 0;
};

#endif /* IEngineVGui_h */
