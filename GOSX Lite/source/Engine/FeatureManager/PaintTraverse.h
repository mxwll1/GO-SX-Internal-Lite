//
//  PaintTraverse.hpp
//  GOSX Pro
//
//  Created by Andre Kalisch on 15.02.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef PaintTraverse_h
#define PaintTraverse_h

#include "Engine/MenuManager/menu.h"
#include "SDK/SDK.h"
#include "Engine/DrawManager/draw.h"
#include "Engine/FeatureManager/Features/Esp.h"

namespace FeatureManager
{
    void PaintTraverse(
        void* thisptr,
        VPANEL vguiPanel,
        bool forceRepaint,
        bool allowForce
    );
}

#endif /* PaintTraverse_h */
