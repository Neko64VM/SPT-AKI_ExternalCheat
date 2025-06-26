#include "Framework.h"

void CFramework::MiscAll()
{
    // BasePointer
    uintptr_t Physics = m.Read<uintptr_t>(local.m_address + offset::Player::pPhysics);

    uintptr_t BreathEffector = m.Read<uintptr_t>(local.m_pWeaponAnimation + offset::WeaponAnimations::Breath);

    uintptr_t Stamina = m.Read<uintptr_t>(Physics + offset::Physics::Stamina);

    /*
    // No Recoil/Sway
    if (g.g_NoSway) {
        m.Write<int>(local.m_pWeaponAnimation + 0x140, 1); // Mask?
        m.Write<float>(BreathEffector + 0xa4, 0.001f);
    }
    */

    /*
    auto _showDirection = m.Read<Vector3>(local.m_pWeaponAnimation + 0x22C);

    printf("%.1f, %.1f, %.1f\n", _showDirection.x, _showDirection.y, _showDirection.z);

    if (GetAsyncKeyState(VK_HOME) & 0x8000)
        m.Write<Vector3>(local.m_pWeaponAnimation + 0x22C, Vector3(0.03f, 0.f, 0.f));
        */

    // InfStamina
    if (g.g_InfStamina && m.Read<float>(Stamina + 0x48) < 85.f)
        m.Write<float>(Stamina + 0x48, 100.f);

    // NoFall Damage
    if (g.g_NoFallDmg && m.Read<float>(Physics + offset::Physics::FallDamageMultiplier) != 0.f)
        m.Write<float>(Physics + offset::Physics::FallDamageMultiplier, 0.f);
}

void CFramework::GetESPInfo(const int& SpawnType, std::string& vOutStr, ImColor& vOutColor)
{
    switch (SpawnType)
    {
    case SCAV:
        vOutStr = "";
        vOutColor = Col_ESP_Scav;
        break;
    case SNIPER_SCAV:
        vOutStr = "Sniper";
        vOutColor = Col_ESP_Scav;
        break;
    case RESHALA_BOSS:
        vOutStr = "Reshala";
        vOutColor = Col_ESP_Boss;
        break;
    case RESHALA_FOLLOW:
        vOutStr = "follower";
        vOutColor = Col_ESP_SpecialScav;
        break;
    case KILLA_BOSS:
        vOutStr = "Killa";
        vOutColor = Col_ESP_Boss;
        break;
    case SHTURMAN_BOSS:
        vOutStr = "Shturman";
        vOutColor = Col_ESP_Boss;
        break;
    case SHTURMAN_FOLLOW:
        vOutStr = "follower";
        vOutColor = Col_ESP_SpecialScav;
        break;
    case GLUKHAR_BOSS:
        vOutStr = "Glukhar";
        vOutColor = Col_ESP_Boss;
        break;
    case GLUKHAR_FOLLOW_01:
        vOutStr = "follower";
        vOutColor = Col_ESP_SpecialScav;
        break;
    case GLUKHAR_FOLLOW_02:
        vOutStr = "follower";
        vOutColor = Col_ESP_SpecialScav;
        break;
    case GLUKHAR_FOLLOW_03:
        vOutStr = "follower";
        vOutColor = Col_ESP_SpecialScav;
        break;
    case SANITOR_BOSS:
        vOutStr = "Sanitor";
        vOutColor = Col_ESP_Boss;
        break;
    case SANITOR_FOLLOW:
        vOutStr = "follower";
        vOutColor = Col_ESP_SpecialScav;
        break;
    case NORMAL_SCAV:
        vOutStr = "Scav";
        vOutColor = Col_ESP_Scav;
        break;
    case CULTIST_01_SCAV:
        vOutStr = "Cultist";
        vOutColor = Col_ESP_SpecialScav;
        break;
    case CULTIST_02_SCAV:
        vOutStr = "Cultist";
        vOutColor = Col_ESP_SpecialScav;
        break;
    case TAGILLA_BOSS:
        vOutStr = "Tagilla";
        vOutColor = Col_ESP_Boss;
        break;
    case ROGUE_SCAV:
        vOutStr = "Rogue";
        vOutColor = Col_ESP_SpecialScav;
        break;
    case ZRYACHIY_BOSS:
        vOutStr = "Zryachiy";
        vOutColor = Col_ESP_Boss;
        break;
    case ZRYACHIY_FOLLOW:
        vOutStr = "follower";
        vOutColor = Col_ESP_SpecialScav;
        break;
    case KABAN_BOSS:
        vOutStr = "Kaban";
        vOutColor = Col_ESP_Boss;
        break;
    case KABAN_FOLLOW_0:
        vOutStr = "follower";
        vOutColor = Col_ESP_SpecialScav;
        break;
    case KABAN_FOLLOW_1:
        vOutStr = "follower";
        vOutColor = Col_ESP_SpecialScav;
        break;
    case KABAN_FOLLOW_2:
        vOutStr = "follower";
        vOutColor = Col_ESP_SpecialScav;
        break;
    case KABAN_FOLLOW_3:
        vOutStr = "follower";
        vOutColor = Col_ESP_SpecialScav;
        break;
    case KOLLONTAY_BOSS:
        vOutStr = "Kollontay";
        vOutColor = Col_ESP_Boss;
        break;
    case KOLLONTAY_FOLLOW_01:
        vOutStr = "follower";
        vOutColor = Col_ESP_SpecialScav;
        break;
    case KOLLONTAY_FOLLOW_02:
        vOutStr = "follower";
        vOutColor = Col_ESP_SpecialScav;
        break;
    case BTR_VEHICLE:
        vOutStr = "BTR-82";
        vOutColor = ImColor(1.f, 1.f, 1.f, 1.f);
        break;
    case SCAV_PARTISAN:
        vOutStr = "Partisan";
        vOutColor = Col_ESP_Scav;
        break;
    case RAIDER_SCAV:
        vOutStr = "Raider";
        vOutColor = Col_ESP_SpecialScav;
        break;
    case KNIGHT_SCAV:
        vOutStr = "Knight";
        vOutColor = Col_ESP_SpecialScav;
        break;
    case BIGPIPE_SCAV:
        vOutStr = "BigPipe";
        vOutColor = Col_ESP_SpecialScav;
        break;
    case BRIDEYE_SCAV:
        vOutStr = "Birdeye";
        vOutColor = Col_ESP_SpecialScav;
        break;
    case BLOODHOUND_SCAV:
        vOutStr = "Bloodhound";
        vOutColor = Col_ESP_SpecialScav;
        break;
    case PMC_BEAR_PvE:
        vOutStr = "BEAR";
        vOutColor = Col_ESP_PMC;
        break;
    case PMC_USEC_PvE:
        vOutStr = "USEC";
        vOutColor = Col_ESP_PMC;
        break;
    case PMC_BEAR_NEW:
        vOutStr = "BEAR";
        vOutColor = Col_ESP_PMC;
        break;
    case PMC_USEC_NEW:
        vOutStr = "USEC";
        vOutColor = Col_ESP_PMC;
        break;
    default:
        vOutStr = "InValid";
        vOutColor = ImColor(1.f, 1.f, 1.f, 1.f);
        break;
    };
}