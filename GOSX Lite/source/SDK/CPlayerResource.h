//
//  CPlayerResource.h
//  GOSX Pro
//
//  Created by Andre Kalisch on 25.02.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef CPlayerResource_h
#define CPlayerResource_h

class CPlayerResource {};
struct Clan {
    char name[32];
};

class C_CSPlayerResource : public CPlayerResource
{
public:
    int GetPing(int index)
    {
        return *(int*)((uintptr_t)this + GET_NETVAR("DT_PlayerResource", "m_iPing") + index * 0x4);
    }

    int GetKills(int index)
    {
        return *(int*)((uintptr_t)this + GET_NETVAR("DT_PlayerResource", "m_iKills") + index * 0x4);
    }

    int GetAssists(int index)
    {
        return *(int*)((uintptr_t)this + GET_NETVAR("DT_PlayerResource", "m_iAssists") + index * 0x4);
    }

    int GetDeaths(int index)
    {
        return *(int*)((uintptr_t)this + GET_NETVAR("DT_PlayerResource", "m_iDeaths") + index * 0x4);
    }

    bool GetConnected(int index)
    {
        return *(bool*)((uintptr_t)this + GET_NETVAR("DT_PlayerResource", "m_bConnected") + index);
    }

    EntityTeam GetTeam(int index)
    {
        return *(EntityTeam*)((uintptr_t)this + GET_NETVAR("DT_PlayerResource", "m_iTeam") + index * 0x4);
    }

    int GetPendingTeam(int index)
    {
        return *(int*)((uintptr_t)this + GET_NETVAR("DT_PlayerResource", "m_iPendingTeam") + index * 0x4);
    }

    bool GetAlive(int index)
    {
        return *(bool*)((uintptr_t)this + GET_NETVAR("DT_PlayerResource", "m_bAlive") + index);
    }

    int GetHealth(int index)
    {
        return *(int*)((uintptr_t)this + GET_NETVAR("DT_PlayerResource", "m_iHealth") + index * 0x4);
    }

    int GetPlayerC4()
    {
        return *(int*)((uintptr_t)this + GET_NETVAR("DT_CSPlayerResource", "m_iPlayerC4"));
    }

    int GetMVPs(int index)
    {
        return *(int*)((uintptr_t)this + GET_NETVAR("DT_CSPlayerResource", "m_iMVPs") + index * 0x4);
    }

    int GetArmor(int index)
    {
        return *(int*)((uintptr_t)this + GET_NETVAR("DT_CSPlayerResource", "m_iArmor") + index * 0x4);
    }

    int GetScore(int index)
    {
        return *(int*)((uintptr_t)this + GET_NETVAR("DT_CSPlayerResource", "m_iScore") + index * 0x4);
    }

    int* GetCompetitiveRanking(int index)
    {
        return (int*)((uintptr_t)this + GET_NETVAR("DT_CSPlayerResource", "m_iCompetitiveRanking") + index * 0x4);
    }

    int* GetCompetitiveWins(int index)
    {
        return (int*)((uintptr_t)this + GET_NETVAR("DT_CSPlayerResource", "m_iCompetitiveWins") + index * 0x4);
    }

    int GetCompTeammateColor(int index)
    {
        return *(int*)((uintptr_t)this + GET_NETVAR("DT_CSPlayerResource", "m_iCompTeammateColor") + index * 0x4);
    }

    const char* GetClan(int index)
    {
        return (const char*)((uintptr_t)this + GET_NETVAR("DT_CSPlayerResource", "m_szClan") + index * 0x10);
    }

    int* GetActiveCoinRank(int index)
    {
        return (int*)((uintptr_t)this + GET_NETVAR("DT_CSPlayerResource", "m_nActiveCoinRank") + index * 0x4);
    }

    int* GetMusicID(int index)
    {
        return (int*)((uintptr_t)this + GET_NETVAR("DT_CSPlayerResource", "m_nMusicID") + index * 0x4);
    }

    int* GetPersonaDataPublicCommendsLeader(int index)
    {
        return (int*)((uintptr_t)this + GET_NETVAR("DT_CSPlayerResource", "m_nPersonaDataPublicCommendsLeader") + index * 0x4);
    }
    
    int* GetPersonaDataPublicCommendsTeacher(int index)
    {
        return (int*)((uintptr_t)this + GET_NETVAR("DT_CSPlayerResource", "m_nPersonaDataPublicCommendsTeacher") + index * 0x4);
    }
    
    int* GetPersonaDataPublicCommendsFriendly(int index)
    {
        return (int*)((uintptr_t)this + GET_NETVAR("DT_CSPlayerResource", "m_nPersonaDataPublicCommendsFriendly") + index * 0x4);
    }
};

#endif /* CPlayerResource_h */
