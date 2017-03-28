//
//  settings.hpp
//  GO:SX v3
//
//  Created by Andre Kalisch on 25.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef settings_h
#define settings_h

#include "SimpleIni.h"
#include "SDK/Color.h"
#include "Engine/functions.h"
#include <vector>
#include <unistd.h>
#include <libproc.h>
#include <fstream>
#include "SDK/Logger.h"
#include "SDK/EconomyItem.h"

class CSettingsManager {
public:
    CSettingsManager(std::string file);
    void ReloadSettings();

    template<typename type>
    type GetSetting(const char* section, const char* key, bool menu = false) {
        type value;
        if (typeid(type) == typeid(float)) {
            value = (float)ini.GetDoubleValue(section, key);
        } else if (typeid(type) == typeid(bool)) {
            value = ini.GetBoolValue(section, key);
        } else if (typeid(type) == typeid(int)) {
            value = (int)ini.GetLongValue(section, key);
        }

        return value;
    }

    template<typename type>
    void SetSetting(const char* section, const char* key, type value, bool menu = false) {
        if (typeid(type) ==  typeid(float)) {
            ini.SetDoubleValue(section, key, value);
        } else if (typeid(type) ==  typeid(bool)) {
            ini.SetBoolValue(section, key, value);
        } else if (typeid(type) ==  typeid(int)) {
            ini.SetLongValue(section, key, value);
        }
    }

    void SetBoolValue(const char* section, const char* key, bool value);
    void SetDoubleValue(const char* section, const char* key, double value, bool instantSave = true);
    void SetIntValue(const char* section, const char* key, int value, bool fromGameEvent = false);
    void SetValue(const char* section, const char* key, const char* value);
    void SetColorValue(const char* section, const char* key, Color value);

    void SaveSettings(bool fromGameEvent = false, bool buttonClicked = false);

    static CSettingsManager* Instance(std::string file)
    {
        if(!instances[file]) {
            instances[file] = new CSettingsManager(file);
        }
        return instances[file];
    }

    void GetAllSections(CSimpleIniA::TNamesDepend &a_names) {
        ini.GetAllSections(a_names);
    }

    void GetAllKeys(const char *a_pSection, CSimpleIniA::TNamesDepend &a_names) {
        ini.GetAllKeys(a_pSection, a_names);
    }

    int getAimPosition(int weaponID);
    const char* GetStringSetting(const char* section, const char* key);
    Color GetColorSetting(const char* section, const char* key);

    bool HasWeaponConfiguration(const char* section);
    EconomyItem_t GetWeaponConfiguration(const char* section);
protected:
    static CSettingsManager*    instance;
    static CSettingsManager*    menu;
    static std::map<std::string, CSettingsManager*> instances;
    CSimpleIniA                 ini;
    char*                       iniFile;
};

#define INIGET_FLOAT(section, key) CSettingsManager::Instance("settings.ini")->GetSetting<float>(section, key)
#define INIGET_INT(section, key) CSettingsManager::Instance("settings.ini")->GetSetting<int>(section, key)
#define INIGET_BOOL(section, key) CSettingsManager::Instance("settings.ini")->GetSetting<bool>(section, key)
#define INIGET_STRING(section, key) CSettingsManager::Instance("settings.ini")->GetStringSetting(section, key)
#define INIGET_COLOR(section, key) CSettingsManager::Instance("settings.ini")->GetColorSetting(section, key)

#define MENUGET_FLOAT(section, key) CSettingsManager::Instance("menu.ini")->GetSetting<float>(section, key)
#define MENUGET_INT(section, key) CSettingsManager::Instance("menu.ini")->GetSetting<int>(section, key)
#define MENUGET_BOOL(section, key) CSettingsManager::Instance("menu.ini")->GetSetting<bool>(section, key)
#define MENUGET_STRING(section, key) CSettingsManager::Instance("menu.ini")->GetStringSetting(section, key)
#define MENUGET_COLOR(section, key) CSettingsManager::Instance("menu.ini")->GetColorSetting(section, key)

#endif /* settings_h */
