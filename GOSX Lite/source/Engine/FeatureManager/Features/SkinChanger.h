//
//  SkinChanger.hpp
//  GOSX Pro
//
//  Created by Andre Kalisch on 23.03.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef SkinChanger_h
#define SkinChanger_h

#include "SDK/SDK.h"
#include "SDK/CCSPlayer.h"
#include "SDK/EconomyItem.h"

const std::unordered_map<size_t, Item_t> ItemDefinitionIndex = {
    {EItemDefinitionIndex::weapon_deagle, {"Desert Eagle", "weapon_deagle", "models/weapons/v_pist_deagle.mdl", "deagle"}},
    {EItemDefinitionIndex::weapon_elite, {"Dual Berettas", "weapon_elite", "models/weapons/v_pist_elite.mdl", "elite"}},
    {EItemDefinitionIndex::weapon_fiveseven, {"Five-SeveN", "weapon_fiveseven", "models/weapons/v_pist_fiveseven.mdl", "fiveseven"}},
    {EItemDefinitionIndex::weapon_glock, {"Glock-18", "weapon_glock", "models/weapons/v_pist_glock18.mdl", "glock"}},
    {EItemDefinitionIndex::weapon_ak47, {"AK-47", "weapon_ak47", "models/weapons/v_rif_ak47.mdl", "ak47"}},
    {EItemDefinitionIndex::weapon_aug, {"AUG", "weapon_aug", "models/weapons/v_rif_aug.mdl", "aug"}},
    {EItemDefinitionIndex::weapon_awp, {"AWP", "weapon_awp", "models/weapons/v_snip_awp.mdl", "awp"}},
    {EItemDefinitionIndex::weapon_famas, {"FAMAS", "weapon_famas", "models/weapons/v_rif_famas.mdl", "famas"}},
    {EItemDefinitionIndex::weapon_g3sg1, {"G3SG1", "weapon_g3sg1", "models/weapons/v_snip_g3sg1.mdl", "g3sg1"}},
    {EItemDefinitionIndex::weapon_galilar, {"Galil AR", "weapon_galilar", "models/weapons/v_rif_galilar.mdl", "galilar"}},
    {EItemDefinitionIndex::weapon_m249, {"M249", "weapon_m249", "models/weapons/v_mach_m249para.mdl", "m249"}},
    {EItemDefinitionIndex::weapon_m4a1, {"M4A4", "weapon_m4a1", "models/weapons/v_rif_m4a1.mdl", "m4a1"}},
    {EItemDefinitionIndex::weapon_mac10, {"MAC-10", "weapon_mac10", "models/weapons/v_smg_mac10.mdl", "mac10"}},
    {EItemDefinitionIndex::weapon_p90, {"P90", "weapon_p90", "models/weapons/v_smg_p90.mdl", "p90"}},
    {EItemDefinitionIndex::weapon_ump45, {"UMP-45", "weapon_ump45", "models/weapons/v_smg_ump45.mdl", "ump45"}},
    {EItemDefinitionIndex::weapon_xm1014, {"XM1014", "weapon_xm1014", "models/weapons/v_shot_xm1014.mdl", "xm1014"}},
    {EItemDefinitionIndex::weapon_bizon, {"PP-Bizon", "weapon_bizon", "models/weapons/v_smg_bizon.mdl", "bizon"}},
    {EItemDefinitionIndex::weapon_mag7, {"MAG-7", "weapon_mag7", "models/weapons/v_shot_mag7.mdl", "mag7"}},
    {EItemDefinitionIndex::weapon_negev, {"Negev", "weapon_negev", "models/weapons/v_mach_negev.mdl", "negev"}},
    {EItemDefinitionIndex::weapon_sawedoff, {"Sawed-Off", "weapon_sawedoff", "models/weapons/v_shot_sawedoff.mdl", "sawedoff"}},
    {EItemDefinitionIndex::weapon_tec9, {"Tec-9", "weapon_tec9", "models/weapons/v_pist_tec9.mdl", "tec9"}},
    {EItemDefinitionIndex::weapon_taser, {"Zeus x27", "weapon_taser", "models/weapons/v_eq_taser.mdl", "taser"}},
    {EItemDefinitionIndex::weapon_hkp2000, {"P2000", "weapon_hkp2000", "models/weapons/v_pist_hkp2000.mdl", "hkp2000"}},
    {EItemDefinitionIndex::weapon_mp7, {"MP7", "weapon_mp7", "models/weapons/v_smg_mp7.mdl", "mp7"}},
    {EItemDefinitionIndex::weapon_mp9, {"MP9", "weapon_mp9", "models/weapons/v_smg_mp9.mdl", "mp9"}},
    {EItemDefinitionIndex::weapon_nova, {"Nova", "weapon_nova", "models/weapons/v_shot_nova.mdl", "nova"}},
    {EItemDefinitionIndex::weapon_p250, {"P250", "weapon_p250", "models/weapons/v_pist_p250.mdl", "p250"}},
    {EItemDefinitionIndex::weapon_scar20, {"SCAR-20", "weapon_scar20", "models/weapons/v_snip_scar20.mdl", "scar20"}},
    {EItemDefinitionIndex::weapon_sg556, {"SG 556", "weapon_sg556", "models/weapons/v_rif_sg556.mdl", "sg556"}},
    {EItemDefinitionIndex::weapon_ssg08, {"SSG 08", "weapon_ssg08", "models/weapons/v_snip_ssg08.mdl", "ssg08"}},
    {EItemDefinitionIndex::weapon_knife, {"Knife (Counter-Terrorists)", "weapon_knife", "models/weapons/v_knife_default_ct.mdl", "knife_default_ct"}},
    {EItemDefinitionIndex::weapon_flashbang, {"Flashbang", "weapon_flashbang", "models/weapons/v_eq_flashbang.mdl", "flashbang"}},
    {EItemDefinitionIndex::weapon_hegrenade, {"HE Grenade", "weapon_hegrenade", "models/weapons/v_eq_fraggrenade.mdl", "hegrenade"}},
    {EItemDefinitionIndex::weapon_smokegrenade, {"Smoke Grenade", "weapon_smokegrenade", "models/weapons/v_eq_smokegrenade.mdl", "smokegrenade"}},
    {EItemDefinitionIndex::weapon_molotov, {"Molotov", "weapon_molotov", "models/weapons/v_eq_molotov.mdl", "inferno"}},
    {EItemDefinitionIndex::weapon_decoy, {"Decoy Grenade", "weapon_decoy", "models/weapons/v_eq_decoy.mdl", "decoy"}},
    {EItemDefinitionIndex::weapon_incgrenade, {"Incendiary Grenade", "weapon_incgrenade", "models/weapons/v_eq_incendiarygrenade.mdl", "inferno"}},
    {EItemDefinitionIndex::weapon_c4, {"C4 Explosive", "weapon_c4", "models/weapons/v_ied.mdl"}},
    {EItemDefinitionIndex::weapon_knife_t, {"Knife (Terrorists)", "weapon_knife_t", "models/weapons/v_knife_default_t.mdl", "knife_t"}},
    {EItemDefinitionIndex::weapon_m4a1_silencer, {"M4A1-S", "weapon_m4a1_silencer", "models/weapons/v_rif_m4a1_s.mdl", "m4a1_silencer"}},
    {EItemDefinitionIndex::weapon_usp_silencer, {"USP-S", "weapon_usp_silencer", "models/weapons/v_pist_223.mdl", "usp_silencer"}},
    {EItemDefinitionIndex::weapon_cz75a, {"CZ75 Auto", "weapon_cz75a", "models/weapons/v_pist_cz_75.mdl", "cz75a"}},
    {EItemDefinitionIndex::weapon_revolver, {"R8 Revolver", "weapon_revolver", "models/weapons/v_pist_revolver.mdl", "revolver"}},
    {EItemDefinitionIndex::weapon_bayonet, {"Bayonet", "weapon_bayonet", "models/weapons/v_knife_bayonet.mdl", "bayonet"}},
    {EItemDefinitionIndex::weapon_knife_flip, {"Flip Knife", "weapon_knife_flip", "models/weapons/v_knife_flip.mdl", "knife_flip"}},
    {EItemDefinitionIndex::weapon_knife_gut, {"Gut Knife", "weapon_knife_gut", "models/weapons/v_knife_gut.mdl", "knife_gut"}},
    {EItemDefinitionIndex::weapon_knife_karambit, {"Karambit", "weapon_knife_karambit", "models/weapons/v_knife_karam.mdl", "knife_karambit"}},
    {EItemDefinitionIndex::weapon_knife_m9_bayonet, {"M9 Bayonet", "weapon_knife_m9_bayonet", "models/weapons/v_knife_m9_bay.mdl", "knife_m9_bayonet"}},
    {EItemDefinitionIndex::weapon_knife_tactical, {"Huntsman Knife", "weapon_knife_tactical", "models/weapons/v_knife_tactical.mdl", "knife_tactical"}},
    {EItemDefinitionIndex::weapon_knife_falchion, {"Falchion Knife", "weapon_knife_falchion", "models/weapons/v_knife_falchion_advanced.mdl", "knife_falchion"}},
    {EItemDefinitionIndex::weapon_knife_survival_bowie, {"Bowie Knife", "weapon_knife_survival_bowie", "models/weapons/v_knife_survival_bowie.mdl", "knife_survival_bowie"}},
    {EItemDefinitionIndex::weapon_knife_butterfly, {"Butterfly Knife", "weapon_knife_butterfly", "models/weapons/v_knife_butterfly.mdl", "knife_butterfly"}},
    {EItemDefinitionIndex::weapon_knife_push, {"Shadow Daggers", "weapon_knife_push", "models/weapons/v_knife_push.mdl", "knife_push"}}
};

// Currently unused -- only here for reference.
const std::unordered_map<size_t, std::string> EntityQuality = {
    {0, "Normal"},
    {1, "Genuine"},
    {2, "Vintage"},
    {3, "Unusual"},
    {5, "Community"},
    {6, "Developer"},
    {7, "Self-Made"},
    {8, "Customized"},
    {9, "Strange"},
    {10, "Completed"},
    {12, "Tournament"}
};

class CSkinChanger {
public:
    CSkinChanger();
    void apply(ClientFrameStage_t stage);
};

#endif /* SkinChanger_h */
