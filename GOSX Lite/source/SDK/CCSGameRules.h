//
//  CCSGameRules.h
//  GOSX Pro
//
//  Created by Andre Kalisch on 27.03.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef CCSGameRules_h
#define CCSGameRules_h

class C_CSGameRules
{
    template<class T>
    inline T GetFieldValue(uint64_t offset)
    {
        return *(T*)((uintptr_t)this + offset);
    }

    template<class T>
    T* GetFieldPointer(uint64_t offset)
    {
        return (T*)((uintptr_t)this + offset);
    }
public:
    bool IsValveDS()
    {
        uintptr_t m_bIsValidValveDS = GET_NETVAR("DT_CSGameRulesProxy", "cs_gamerules_data", "m_bIsValveDS");
        return GetFieldValue<bool>(m_bIsValidValveDS);
    }

    bool IsBombDropped()
    {
        uintptr_t m_bBombDropped = GET_NETVAR("DT_CSGameRulesProxy", "cs_gamerules_data", "m_bBombDropped");
        return GetFieldValue<bool>(m_bBombDropped);
    }

    bool IsBombPlanted()
    {
        uintptr_t m_bBombPlanted = GET_NETVAR("DT_CSGameRulesProxy", "cs_gamerules_data", "m_bBombPlanted");
        return GetFieldValue<bool>(m_bBombPlanted);
    }

    bool IsFreezeTime()
    {
        uintptr_t m_bFreezePeriod = GET_NETVAR("DT_CSGameRulesProxy", "cs_gamerules_data", "m_bFreezePeriod");
        return GetFieldValue<bool>(m_bFreezePeriod);
    }
};

#endif /* CCSGameRules_h */
