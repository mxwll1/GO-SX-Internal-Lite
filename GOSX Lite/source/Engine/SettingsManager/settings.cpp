//
//  settings.cpp
//  GO:SX v3
//
//  Created by Andre Kalisch on 25.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#include "settings.h"
#include "Engine/MenuManager/menu.h"

std::map<std::string, CSettingsManager*> CSettingsManager::instances = {};

CSettingsManager::CSettingsManager(std::string file) {
    std::string iniPath = Functions::DirName(Functions::GetModulePath("gosx.dylib"));
    std::string settingsFile = iniPath.append(file);

    if (Functions::FileExist(settingsFile)) {
        iniFile = strdup(settingsFile.c_str());

        ini.SetUnicode();
        ini.LoadFile(iniFile);
    }
}

void CSettingsManager::ReloadSettings() {
    ini.Reset();
    ini.LoadFile(iniFile);
}

void CSettingsManager::SetBoolValue(const char* section, const char* key, bool value) {
    if (CHackMenu::Instance()->IsMenuOpen()) {
        ini.SetBoolValue(section, key, (bool)value);
        SaveSettings();
    }
}

void CSettingsManager::SetDoubleValue(const char* section, const char* key, double value, bool instantSave) {
    if (CHackMenu::Instance()->IsMenuOpen()) {
        ini.SetDoubleValue(section, key, (double)value);
        if (instantSave) {
            SaveSettings();
        }
    }
}

void CSettingsManager::SetIntValue(const char* section, const char* key, int value, bool fromGameEvent) {
    if (CHackMenu::Instance()->IsMenuOpen() || fromGameEvent) {
        ini.SetLongValue(section, key, (long)value);
        SaveSettings(fromGameEvent);
    }
}

void CSettingsManager::SetValue(const char* section, const char* key, const char* value) {
    if (CHackMenu::Instance()->IsMenuOpen()) {
        ini.SetValue(section, key, value);
        SaveSettings();
    }
}

void CSettingsManager::SetColorValue(const char* section, const char* key, Color value) {
    char color[30];
    sprintf(color, "%i,%i,%i,%i", value.r(), value.g(), value.b(), value.a());

    SetValue(section, key, color);
}

void CSettingsManager::SaveSettings(bool fromGameEvent, bool buttonClicked) {
    if(CHackMenu::Instance()->IsMenuOpen() || fromGameEvent) {
        ini.SaveFile(iniFile);
    }
}

const char* CSettingsManager::GetStringSetting(const char* section, const char* key) {
    return ini.GetValue(section, key);
}

Color CSettingsManager::GetColorSetting(const char* section, const char* key) {
    std::string value = GetStringSetting(section, key);

    std::vector<std::string> colors = Functions::split<std::string>(value, ",");
    return Color(
        atof(colors[0].c_str()),
        atof(colors[1].c_str()),
        atof(colors[2].c_str()),
        atof(colors[3].c_str())
    );
}

bool CSettingsManager::HasWeaponConfiguration(const char* section) {
    CSimpleIniA::TNamesDepend sections;
    CSettingsManager::Instance("weapons.ini")->GetAllSections(sections);
    sections.sort(CSimpleIniA::Entry::LoadOrder());

    for (auto sect : sections) {
        if(!strcmp(section, sect.pItem)) {
            return true;
        }
    }

    return false;
}

EconomyItem_t CSettingsManager::GetWeaponConfiguration(const char *section) {
    EconomyItem_t weapon_config;

    weapon_config.entity_quality = (int)ini.GetLongValue(section, "entity_quality");
    weapon_config.fallback_paint_kit = (int)ini.GetLongValue(section, "fallback_paint_kit");
    weapon_config.fallback_seed = (int)ini.GetLongValue(section, "fallback_seed");
    weapon_config.fallback_wear = (float)ini.GetDoubleValue(section, "fallback_wear");
    weapon_config.fallback_stattrak = (int)ini.GetLongValue(section, "fallback_stattrak");
    weapon_config.item_definition_index = (int)ini.GetLongValue(section, "item_definition_index");

    return weapon_config;
}
