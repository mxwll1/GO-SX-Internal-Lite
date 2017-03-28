//
//  CGlowObjectManager.h
//  GOSX Pro
//
//  Created by Andre Kalisch on 18.02.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef CGlowObjectManager_h
#define CGlowObjectManager_h

#include "SDK.h"

#define END_OF_FREE_LIST -1
#define ENTRY_IN_USE -2

struct GlowObjectDefinition_t
{
    C_BaseEntity* m_pEntity;
    Vector m_flGlowColor;
    float m_flGlowAlpha;
    char unknown[4];
    float flUnk;
    float m_flBloomAmount;
    float localplayeriszeropoint3;
    bool m_bRenderWhenOccluded;
    bool m_bRenderWhenUnoccluded;
    bool m_bFullBloomRender;
    char unknown1[1];
    int m_nFullBloomStencilTestValue;
    int iUnk;
    int m_nSplitScreenSlot;
    int m_nNextFreeSlot;
    
    bool IsUnused() const {
        return m_nNextFreeSlot != ENTRY_IN_USE;
    }
};

class CGlowObjectManager
{
public:
    int RegisterGlowObject(C_BaseEntity* entity)
    {
        if (m_nFirstFreeSlot == END_OF_FREE_LIST) {
            return -1;
        }
        
        int index = m_nFirstFreeSlot;
        m_nFirstFreeSlot = m_entries[index].m_nNextFreeSlot;
        
        m_entries[index].m_pEntity = entity;
        m_entries[index].flUnk = 0.0f;
        m_entries[index].localplayeriszeropoint3 = 0.0f;
        m_entries[index].m_bFullBloomRender = false;
        m_entries[index].m_nFullBloomStencilTestValue = 0;
        m_entries[index].m_nSplitScreenSlot = -1;
        m_entries[index].m_nNextFreeSlot = ENTRY_IN_USE;
        
        return index;
    }
    
    void UnregisterGlowObject(int index)
    {
        m_entries[index].m_nNextFreeSlot = m_nFirstFreeSlot;
        m_entries[index].m_pEntity = NULL;
        m_nFirstFreeSlot = index;
    }
    
    bool HasGlowEffect(IClientEntity* entity)
    {
        for (int i = 0; i < m_entries.Count(); ++i) {
            if (!m_entries[i].IsUnused() && m_entries[i].m_pEntity == entity) {
                return true;
            }
        }
        
        return false;
    };
    
    CUtlVector<GlowObjectDefinition_t> m_entries;
    int m_nFirstFreeSlot;
};

#endif /* CGlowObjectManager_h */
