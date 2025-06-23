#include "Framework.h"

// いくらかのリストを1RPMで読み取る為の構造体
struct CGameObjectList {
    uint64_t address[64]{};
};

// アイテムを1RPMで読み取るための構造体
struct CGameItemList {
    uint64_t address[2048]{};
};

void CFramework::UpdateList()
{
    // Get GameObjectManager
    while (!tarkov->InitAddress() || !tarkov->UpdateCamera())
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Loop
    while (g.process_active)
    {
        // Sleep...
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        // 仮のリスト用変数
        std::vector<CPlayer>    list_player{};
        std::vector<uintptr_t>  list_grenade{};

        if (g.g_ESP)
        {
            // not In raid
            if (!tarkov->Update())
                continue;

            // PlayerList
            const auto GameWorld = tarkov->m_pLocalGameWorld;
            const auto registered_player = m.Read<uintptr_t>(GameWorld + offset::RegisteredPlayers);
            const auto entity_array = m.Read<UnityList>(registered_player);

            if (entity_array.count <= 0)
                continue;
            else if (entity_array.list_address == NULL)
                continue;

            local.m_address = m.Read<uintptr_t>(GameWorld + offset::MainPlayer);

            if (local.m_address != NULL)
            {
                local.UpdateStatic();
                local.Update();

                auto player_list = m.Read<CGameObjectList>(entity_array.list_address + 0x20);

                // ESP用EntityListを構築
                for (auto i = 0; i < entity_array.count; i++)
                {
                    CPlayer p = CPlayer();
                    p.m_address = player_list.address[i];

                    if (p.m_address != NULL && p.m_address != local.m_address) 
                    {
                        p.UpdateStatic();

                        // Distance check
                        if (GetDistance(local.m_vecOrigin, p.GetBonePosition(BONE_ORIGIN)) < g.g_ESP_MaxDistance)
                        {
                            list_player.push_back(p);
                        }
                    }
                }
            }
        } 
        else {
            std::this_thread::sleep_for(std::chrono::seconds(3));
            continue;
        }

        std::lock_guard<std::mutex> lock0(m_mtxEntityList);
        m_vecEntityList = list_player;
        
        //GrenadeList = list_grenade;
    }
}

// 要改善
void CFramework::UpdateStaticList() // C6262 :(
{
    while (g.process_active)
    {
        std::this_thread::sleep_for(std::chrono::seconds(5));

        std::vector<CItem>  list_item{};
        std::vector<CExfil> list_exfil{};
        const auto GameWorld = tarkov->m_pLocalGameWorld;
        tarkov->UpdateCamera();

        // ItemList
        if (tarkov->Update())
        {
            // Exfil
            if (g.g_ESP_Exfil)
            {
                const auto exfil_controller = m.Read<uintptr_t>(GameWorld + offset::ExfilController);
                const auto exfil_array = m.Read<uintptr_t>(exfil_controller + 0x28);
                auto exfil_list = m.Read<CGameObjectList>(exfil_array + 0x20);

                for (auto j = 0; j < 16; j++)
                {
                    CExfil e;
                    if (e.GetAddress(exfil_list.address[j]))
                    {
                        if (!e.Update())
                            continue;

                        e.m_pExfilName = e.GetName();
                       
                        list_exfil.push_back(e);
                    }
                }
            }

            if (g.g_ESP_Item)
            {
                const auto LootList = m.Read<uintptr_t>(tarkov->m_pLocalGameWorld + offset::LootList);
                const auto ItemArray = m.Read<UnityList>(LootList);

                if (ItemArray.count != 0)
                {
                    auto item_list = m.Read<CGameItemList>(ItemArray.list_address + 0x20);

                    for (int k = 0; k < ItemArray.count; k++)
                    {
                        CItem item;

                        if (item.GetAddress(item_list.address[k])) {
                            item.Update();
                            list_item.push_back(item);
                        }
                    }
                }
            }
        }
        else {
            std::this_thread::sleep_for(std::chrono::seconds(3));
            continue;
        }

        std::lock_guard<std::mutex> lock1(m_mtxExfilList);
        std::lock_guard<std::mutex> lock2(m_mtxItemList);
        m_vecExfilList = list_exfil;
        m_vecItemList = list_item;
    }
}