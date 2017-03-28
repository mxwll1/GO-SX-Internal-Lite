//
//  Esp.hpp
//  GOSX Pro
//
//  Created by Andre Kalisch on 20.02.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef Esp_h
#define Esp_h

#include "SDK/SDK.h"
#include "Engine/DrawManager/draw.h"

class CEsp {
public:
    CEsp(CDrawings* drawMngr);
    void DrawESP();
    void DrawCrossHair();
    void DrawFOVCircle();
    void DrawSilentFOVCircle();
    void DrawScope();
    void DrawBomb();
private:
    CDrawings* DrawManager;
};

#endif /* Esp_h */
