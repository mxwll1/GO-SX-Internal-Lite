#pragma once
#ifndef sdk_func_h
#define sdk_func_h

#include "SDK.h"

namespace Func {
    IMaterial* CreateMaterial(bool bShouldIgnoreZ, bool bShouldFlat);
    std::string GetWorkingPath();
    std::string DirName(std::string source);
    bool IsFileExists(const std::string& name);
}

#endif // !sdk_func_h
