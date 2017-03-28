//
//  nvmngr.hpp
//  GOSX Pro
//
//  Created by Andre Kalisch on 15.02.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef nvmngr_h
#define nvmngr_h

#include <memory>
#include <iostream>
#include <unordered_map>
#include "SDK/Recv.h"
class NetvarTable;

typedef std::unordered_map<std::string, std::unique_ptr<NetvarTable>>      TableMap;
typedef std::unordered_map<std::string, uint32_t>                          PropMap;
typedef std::unordered_map<std::string, std::unique_ptr<NetvarTable>>::iterator Iter;

struct NetvarTable
{
    TableMap  m_ChildTables;
    PropMap   m_ChildProps;
    uint32_t  m_uOffset = 0;
    
    bool is_empty()
    {
        return m_ChildTables.size() == 0 && m_ChildProps.size() == 0;
    }
    void insert_table(std::string&& name, std::unique_ptr<NetvarTable>&& pTable)
    {
        m_ChildTables.emplace(name, std::move(pTable));
    }
    void insert_prop(std::string&& name, uint32_t offset)
    {
        m_ChildProps.emplace(name, offset);
    }
};

class NetvarDatabase
{
public:
    TableMap m_Tables;
    void insert(std::string&& name, std::unique_ptr<NetvarTable>&& pTable)
    {
        m_Tables.emplace(name, std::move(pTable));
    }
    Iter find(const std::string& key) { return m_Tables.find(key); }
    Iter begin() { return m_Tables.begin(); }
    Iter end() { return m_Tables.end(); }
    
};

class NetvarManager
{
private:
    static NetvarManager* instance;
    NetvarManager();
    ~NetvarManager();
    NetvarManager(const NetvarManager&) = delete;
    
public:
    static NetvarManager* Instance()
    {
        if (!instance) instance = new NetvarManager;
        return instance;
    }
    void CreateDatabase();
    void Dump(std::ostream& stream);
    void Dump(const std::string& file);
    int GetNetvarCount() { return m_netvarCount; }
    int GetTableCount() { return m_tableCount; }
    uint64_t GetNetvarOffset(const std::string szTableName, const std::string szPropName);
    template<typename ...Args>
    uint64_t GetOffset(const std::string& szTableName, Args&&... args)
    {
        return GetOffset(szTableName, { std::forward<Args>(args)... });
    }
    uint64_t GetOffset(const std::string& szTableName, const std::initializer_list<std::string>& props);
private:
    std::unique_ptr<NetvarTable>  InternalLoadTable(RecvTable* pRecvTable, uint32_t offset);
    void                          Dump(std::ostream& output, NetvarTable& table, int level);
    void						  Dump(std::ostream& output, NetvarTable& table, int level, const std::string& tableName);
private:
    std::unique_ptr<NetvarDatabase>    m_pDatabase = nullptr;
    uint32_t                           m_tableCount = 0;
    uint32_t                           m_netvarCount = 0;
};

#define GET_NETVAR(table, ...) NetvarManager::Instance()->GetOffset(table, __VA_ARGS__)

#endif /* nvmngr_h */
