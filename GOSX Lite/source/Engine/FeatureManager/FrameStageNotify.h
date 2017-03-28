//
//  FrameStageNotify.hpp
//  GOSX Pro
//
//  Created by Andre Kalisch on 19.02.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef FrameStageNotify_h
#define FrameStageNotify_h

#include "SDK/SDK.h"
#include "Engine/FeatureManager/Features/FlashReducer.h"
#include "Engine/FeatureManager/Features/SkinChanger.h"
#include "SDK/CCSPlayer.h"

namespace FeatureManager {
    void FrameStageNotify(ClientFrameStage_t stage);
}

#endif /* FrameStageNotify_h */
