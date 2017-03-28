#include "Chams.h"

CChams::CChams() {
    hidden_tex = CreateMaterial(false, false, true, true, true, true, true);
    visible_tex = CreateMaterial(true, false, true, true, true, true, true);
    hidden_flat = CreateMaterial(false, true, true, true, true, true, true);
    visible_flat = CreateMaterial(true, true, true, true, true, true, true);
}

void CChams::AddMaterial(std::string filename, std::string type, std::string texture, bool ignorez, bool nofog, bool model, bool nocull, bool halflambert, bool gluelook) {
    if (!Func::IsFileExists(Func::GetWorkingPath().append("csgo/materials/").append(filename).append(".vmt")))
    {
        std::stringstream ss;

        ss << "\"" + type + "\"" << std::endl;
        ss << "{" << std::endl;
        ss << "\t\"$basetexture\" \"" + texture + "\"" << std::endl;
        ss << "\t\"$ignorez\" \"" + std::to_string(ignorez) + "\"" << std::endl;
        ss << "\t\"$nofog\" \"" + std::to_string(nofog) + "\"" << std::endl;
        ss << "\t\"$model\" \"" + std::to_string(model) + "\"" << std::endl;
        ss << "\t\"$nocull\" \"" + std::to_string(nocull) + "\"" << std::endl;
        ss << "\t\"$halflambert\" \"" + std::to_string(halflambert) + "\"" << std::endl;
        if(gluelook) {
            ss << "\t\"$envmap\" \"env_cubemap\"" << std::endl;
            ss << "\t\"$normalmapalphaenvmapmask\" 1" << std::endl;
            ss << "\t\"$envmapcontrast\" 1" << std::endl;
        }
        ss << "}" << std::endl;

        std::ofstream(Func::GetWorkingPath().append("csgo/materials/").append(filename).append(".vmt").c_str()) << ss.str();
    }
}

IMaterial* CChams::CreateMaterial(bool ignorez, bool flat, bool nofog, bool model, bool nocull, bool halflambert, bool gluelook) {
    IMaterial* createdMaterial;

    if(gluelook) {
        if (ignorez)
        {
            if (flat) {
                if (!Func::IsFileExists(Func::GetWorkingPath().append("csgo/materials/").append("chamsmat_flat_ignorez").append(".vmt")))
                {
                    AddMaterial("chamsmat_flat_ignorez", "UnlitGeneric", "VGUI/white_additive", ignorez, nofog, model, nocull, halflambert, gluelook);
                }
                createdMaterial = Interfaces::MaterialSystem()->FindMaterial("chamsmat_flat_ignorez");
            } else {
                if (!Func::IsFileExists(Func::GetWorkingPath().append("csgo/materials/").append("chamsmat_ignorez").append(".vmt")))
                {
                    AddMaterial("chamsmat_ignorez", "VertexLitGeneric", "VGUI/white_additive", ignorez, nofog, model, nocull, halflambert, gluelook);
                }
                createdMaterial = Interfaces::MaterialSystem()->FindMaterial("chamsmat_ignorez");
            }
        }
        else
        {
            if (flat) {
                if (!Func::IsFileExists(Func::GetWorkingPath().append("csgo/materials/").append("chamsmat_flat").append(".vmt")))
                {
                    AddMaterial("chamsmat_flat", "UnlitGeneric", "VGUI/white_additive", ignorez, nofog, model, nocull, halflambert, gluelook);
                }
                createdMaterial = Interfaces::MaterialSystem()->FindMaterial("chamsmat_flat");
            } else {
                if (!Func::IsFileExists(Func::GetWorkingPath().append("csgo/materials/").append("chamsmat").append(".vmt")))
                {
                    AddMaterial("chamsmat", "VertexLitGeneric", "VGUI/white_additive", ignorez, nofog, model, nocull, halflambert, gluelook);
                }
                createdMaterial = Interfaces::MaterialSystem()->FindMaterial("chamsmat");
            }
        }
    }

    createdMaterial->IncrementReferenceCount();

    return createdMaterial;
}

void CChams::apply(IMatRenderContext* oriContext, const DrawModelState_t &oriState, const ModelRenderInfo_t &oriPInfo, matrix3x4_t *oriPCustomBoneToWorld)
{
    if(INIGET_BOOL("Main", "enabled")) {
        if(INIGET_BOOL("Chams", "enabled")) {
            if (oriPInfo.pModel) {
                std::string szModelName = Interfaces::ModelInfo()->GetModelName(oriPInfo.pModel);
                if(INIGET_BOOL("Chams", "players")) {
                    if (szModelName.find("models/player/") != std::string::npos)
                    {
                        C_CSPlayer* pModelPlayer = (C_CSPlayer*)Interfaces::EntityList()->GetClientEntity(oriPInfo.entity_index);
                        if (pModelPlayer && pModelPlayer->IsValidLivePlayer())
                        {
                            if (pModelPlayer->GetTeamNum() == EntityTeam::TEAM_T)
                            {
                                if(INIGET_BOOL("Chams", "wallhack")) {
                                    ForceMaterial(visible_tex, INIGET_COLOR("Colors", "color_t"), pModelPlayer->GetImmune());
                                    Interfaces::ModelRender()->DrawModelExecute(oriContext, oriState, oriPInfo, oriPCustomBoneToWorld);
                                }

                                ForceMaterial(hidden_tex, INIGET_COLOR("Colors", "color_t_visible"), pModelPlayer->GetImmune());
                                Interfaces::ModelRender()->DrawModelExecute(oriContext, oriState, oriPInfo, oriPCustomBoneToWorld);

                            }
                            else if (pModelPlayer->GetTeamNum() == EntityTeam::TEAM_CT)
                            {
                                if(INIGET_BOOL("Chams", "wallhack")) {
                                    ForceMaterial(visible_tex, INIGET_COLOR("Colors", "color_ct"), pModelPlayer->GetImmune());
                                    Interfaces::ModelRender()->DrawModelExecute(oriContext, oriState, oriPInfo, oriPCustomBoneToWorld);
                                }

                                ForceMaterial(hidden_tex, INIGET_COLOR("Colors", "color_ct_visible"), pModelPlayer->GetImmune());
                                Interfaces::ModelRender()->DrawModelExecute(oriContext, oriState, oriPInfo, oriPCustomBoneToWorld);
                            }
                        }
                    }
                }
            }
        }
    }

    Interfaces::ModelRender()->DrawModelExecute(oriContext, oriState, oriPInfo, oriPCustomBoneToWorld);
    Interfaces::ModelRender()->ForcedMaterialOverride(nullptr);
}

void CChams::ForceMaterial(IMaterial* material, Color color, bool immune = false)
{
    if (material)
    {
        float alpha = 1.f;
        if (immune) {
            alpha = 0.5f;
        }

        material->AlphaModulate(alpha);
        material->ColorModulate(color.r() / 255.0f, color.g() / 255.0f, color.b() / 255.0f);

        Interfaces::ModelRender()->ForcedMaterialOverride(material);
    }
}
