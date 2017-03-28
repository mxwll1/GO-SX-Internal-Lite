//
//  functions.hpp
//  GOSX Pro
//
//  Created by Andre Kalisch on 15.02.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef functions_h
#define functions_h

#include "common.h"
#include "Carbon/Carbon.h"
#include "Engine/PatternManager/pattern.h"
#include <ctime>
#include <cstdlib>

#define IDOK       1
#define IDCANCEL   2

namespace Functions {
    int MessageBox(const char* header, const char* message, unsigned long message_type);
    uintptr_t GetAbsoluteAddress(uintptr_t instruction_ptr, int offset, int size);
    std::string GetModulePath(std::string module);

    template<typename T>
    std::vector<T> split(const T & str, const T & delimiters)
    {
        std::vector<T> v;
        size_t start = 0;
        auto pos = str.find_first_of(delimiters, start);
        while (pos != T::npos)
        {
            if (pos != start)
            {
                v.emplace_back(str, start, pos - start);
            }
            start = pos + 1;
            pos = str.find_first_of(delimiters, start);
        }
        if (start < str.length())
        {
            v.emplace_back(str, start, str.length() - start);
        }
        return v;
    }

    float RandomFloat(float minVal, float maxVal);
    bool IsKeyPressed(unsigned short inKeyCode);

    template <typename T> inline T* GetAbsoluteAddress(uintptr_t instruction_ptr, int offset, int size) {
        return reinterpret_cast<T*>(instruction_ptr + *reinterpret_cast<uint32_t*>(instruction_ptr + offset) + size);
    };

    void SetMousePos(int x, int y);
    bool FileExist(std::string fileName);
    std::string DirName(std::string source);
}

#endif /* functions_h */
