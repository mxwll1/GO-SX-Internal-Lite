//
//  pattern.hpp
//  GOSX Pro
//
//  Created by Andre Kalisch on 16.02.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef pattern_hpp
#define pattern_hpp

#include "Engine/common.h"
#include <mach/mach_traps.h>
#include <mach/mach_init.h>
#include <mach/mach_error.h>
#include <mach/mach.h>
#include <mach-o/dyld_images.h>
#include <mach-o/loader.h>

struct MemoryModule
{
    off_t       length;
    uint64_t    address;
    char*       path;
    std::string fullpath;
    Byte*       buffer = nullptr;
};

struct MatchPathSeparator
{
    bool operator()( char ch ) const
    {
        return ch == '\\' || ch == '/';
    }
};

class CPatternScanner {
public:
    static CPatternScanner* Instance() {
        if(!instance) {
            instance = new CPatternScanner();
        }
        
        return instance;
    }
    CPatternScanner();
    std::string Basename(std::string const& pathname);
    bool Compare(const unsigned char* pData, const unsigned char* bMask, const char* szMask);
    uintptr_t FindPattern(uintptr_t dwAddress, off_t dwLen, unsigned char* bMask, const char* szMask, uintptr_t offset = 0x0);
    uintptr_t GetPointer(std::string imageName, unsigned char* bMask, const char* szMask, uint32_t start);
    uintptr_t GetProcedure(std::string imageName, unsigned char* bMask, const char* szMask, uintptr_t offset = 0x0);
    std::string GetModulePath(std::string imageName);
    uintptr_t GetBaseAddress(std::string imageName);
private:
    void LoadModules();
    std::map<std::string, MemoryModule> loaded_modules;
    static CPatternScanner* instance;
};

#define CLIENT_POINTER(bMask, szMask, start) CPatternScanner::Instance()->GetPointer("client.dylib", bMask, szMask, start)
#define CLIENT_PROCEDURE(bMask, szMask) CPatternScanner::Instance()->GetProcedure("client.dylib", bMask, szMask)
#define ENGINE_POINTER(bMask, szMask, start) CPatternScanner::Instance()->GetPointer("engine.dylib", bMask, szMask, start)
#define ENGINE_PROCEDURE(bMask, szMask) CPatternScanner::Instance()->GetProcedure("engine.dylib", bMask, szMask)

#endif /* pattern_hpp */
