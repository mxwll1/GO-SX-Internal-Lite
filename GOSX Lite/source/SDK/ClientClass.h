#pragma once

#ifndef clientclass_h
#define clientclass_h

#include "Definitions.h"

#include "Recv.h"
#include "IClientNetworkable.h"

class ClientClass;

typedef IClientNetworkable*   (*CreateClientClassFn)(int entnum, int serialNum);
typedef IClientNetworkable*   (*CreateEventFn)();

class ClientClass
{
public:
    CreateClientClassFn      m_pCreateFn;
    CreateEventFn            m_pCreateEventFn;
    char*                    m_pNetworkName;
    RecvTable*               m_pRecvTable;
    ClientClass*             m_pNext;
    int                      m_ClassID;
};

#endif // !clientclass_h