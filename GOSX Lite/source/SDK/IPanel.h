#pragma once

#include "Engine/common.h"

#include "Definitions.h"
#include "internal.h"

class IPanel
{
public:
    const char *GetName(VPANEL vguiPanel)
    {
        typedef const char* (* oGetName)(void*, VPANEL);
        return Internal::getvfunc<oGetName>(this, 37)(this, vguiPanel);
    }
#ifdef GetClassName
#undef GetClassName
#endif
    const char *GetClassName(unsigned int vguiPanel)
    {
        typedef const char* (* oGetClassName)(void*, VPANEL);
        return Internal::getvfunc<oGetClassName>(this, 38)(this, vguiPanel);
    }
};
