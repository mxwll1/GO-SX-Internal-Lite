//
//  SkinChanger.cpp
//  GOSX Pro
//
//  Created by Andre Kalisch on 23.03.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#include "SkinChanger.h"

CSkinChanger::CSkinChanger() {}

void CSkinChanger::apply(ClientFrameStage_t stage) {
    int localplayer_index = Interfaces::Engine()->GetLocalPlayer();
    C_CSPlayer* localplayer = C_CSPlayer::GetLocalPlayer();

    if (!localplayer || !localplayer->IsValidLivePlayer()) {
        return;
    }

    player_info_t localplayer_info;

    if (!Interfaces::Engine()->GetPlayerInfo(localplayer_index, &localplayer_info)) {
        return;
    }

    int* pWeapons = localplayer->GetWeapons();

    if(pWeapons) {
        auto config = CSettingsManager::Instance("weapons.ini");
        for(int i = 0; pWeapons[i]; i++){
            C_BaseAttributableItem* weapon = (C_BaseAttributableItem*)Interfaces::EntityList()->GetClientEntityFromHandle(pWeapons[i]);

            if (!weapon) {
                continue;
            }

            int* item_definition_index = weapon->GetItemDefinitionIndex();

            const char* weaponConfigName = ItemDefinitionIndex.at(*item_definition_index).entity_name;
            if (config->HasWeaponConfiguration(weaponConfigName)) {
                const EconomyItem_t& weapon_config = config->GetWeaponConfiguration(weaponConfigName);
                *weapon->GetItemIDHigh() = -1;
                *weapon->GetAccountID() = localplayer_info.xuid_low;

                if (weapon_config.item_definition_index != -1) {
                    if (ItemDefinitionIndex.find(weapon_config.item_definition_index) != ItemDefinitionIndex.end()) {
                        *reinterpret_cast<int*>(weapon->GetModelIndex()) = Interfaces::ModelInfoClient()->GetModelIndex(ItemDefinitionIndex.at(weapon_config.item_definition_index).model);

                        if (ItemDefinitionIndex.find(*item_definition_index) != ItemDefinitionIndex.end()) {
                            const Item_t& original_item = ItemDefinitionIndex.at(*item_definition_index);
                            const Item_t& replacement_item = ItemDefinitionIndex.at(weapon_config.item_definition_index);
                            if (original_item.killicon && replacement_item.killicon) {
                                // config.SetKillIconOverride(original_item.killicon, replacement_item.killicon);
                            }
                            *item_definition_index = weapon_config.item_definition_index;
                        }
                    }
                }

                if (weapon_config.entity_quality != -1) {
                    *weapon->GetEntityQuality() = weapon_config.entity_quality;
                }
                if (weapon_config.fallback_paint_kit != -1) {
                    *weapon->GetFallbackPaintKit() = weapon_config.fallback_paint_kit;
                }
                if (weapon_config.fallback_seed != -1) {
                    *weapon->GetFallbackSeed() = weapon_config.fallback_seed;
                }
                if (weapon_config.fallback_wear != -1) {
                    *weapon->GetFallbackWear() = weapon_config.fallback_wear;
                }
                if (weapon_config.fallback_stattrak != -1) {
                    *weapon->GetFallbackStatTrak() = weapon_config.fallback_stattrak;
                }
            }
        }

        CBaseHandle viewmodel_handle = localplayer->GetViewModel();
        if (viewmodel_handle == INVALID_EHANDLE_INDEX) {
            return;
        }

        C_BaseViewModel* viewmodel = (C_BaseViewModel*)Interfaces::EntityList()->GetClientEntityFromHandle(viewmodel_handle);
        if (!viewmodel) {
            return;
        }

        CBaseHandle viewmodel_weapon_handle = viewmodel->GetWeapon();
        if (viewmodel_weapon_handle == INVALID_EHANDLE_INDEX) {
            return;
        }

        C_BaseAttributableItem* viewmodel_weapon = (C_BaseAttributableItem*)Interfaces::EntityList()->GetClientEntityFromHandle(viewmodel_weapon_handle);
        if (!viewmodel_weapon) {
            return;
        }

        if (ItemDefinitionIndex.find(*viewmodel_weapon->GetItemDefinitionIndex()) != ItemDefinitionIndex.end()) {
            const Item_t& override_weapon = ItemDefinitionIndex.at(*viewmodel_weapon->GetItemDefinitionIndex());
            *viewmodel->GetModelIndex() = Interfaces::ModelInfo()->GetModelIndex(override_weapon.model);
        }
    }
    
    return;
}
