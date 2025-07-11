#pragma once
#include "../Framework/ImGui/imgui.h"
#include "../Framework/ImGui/imgui_impl_win32.h"
#include "../Framework/ImGui/imgui_impl_dx11.h"
#include "../Framework/ImGui/Custom.h"
#include "../Framework/ImGui/Fonts/fa.h"
#include "../Framework/ImGui/Fonts/RobotoRegular.h"
#include "../Framework/ImGui/Fonts/IconsFontAwesome6.h"
#include "SDK/CPlayer/CPlayer.h"
#include "SDK/CExfil/CExfil.h"
#include "SDK/CItem/CItem.h"
#include <mutex>

class CFramework
{
public:
    
    bool Init();
    void UpdateList();
    void UpdateStaticList();
	void RenderInfo();
	void RenderMenu();
	void RenderESP();
    void MiscAll();
private:
    ImFont* icon{ nullptr };

    // どうにかする
    CGame* tarkov = new CGame();
    
    // スレッドセーフにする
    CPlayer local;

    std::mutex m_mtxEntityList;
    std::mutex m_mtxExfilList;
    std::mutex m_mtxItemList;

    std::vector<CPlayer> m_vecEntityList;
    std::vector<CExfil> m_vecExfilList;
    std::vector<CItem> m_vecItemList;
    std::vector<uintptr_t> m_vecGrenadeList;

    std::vector<CPlayer> GetEntityList() {
        std::lock_guard<std::mutex> lock(m_mtxEntityList);
        return m_vecEntityList;
    }
    std::vector<CExfil> GetExfilList() {
        std::lock_guard<std::mutex> lock(m_mtxExfilList);
        return m_vecExfilList;
    }
    std::vector<CItem> GetItemList() {
        std::lock_guard<std::mutex> lock(m_mtxItemList);
        return m_vecItemList;
    }

    // Colors
    ImColor Col_ESP_PMC = { 1.f, 0.f, 0.85f, 1.f };
    ImColor Col_ESP_Team = { 0.f, 1.f, 0.f, 0.f };
    ImColor Col_ESP_Scav = { 1.f, 1.f, 1.f, 1.f };
    ImColor Col_ESP_pScav = { 1.f, 1.f, 0.f, 1.f };
    ImColor Col_ESP_SpecialScav = { 1.f, 0.5f, 0.f, 1.f };
    ImColor Col_ESP_Boss = { 1.f, 0.f, 0.f, 1.f };
    ImColor Col_ESP_Filled = { 0.f, 0.f, 0.f, 0.25f };

    ImColor Col_ESP_ExfilOpen = { 0.f, 1.f, 0.f, 0.5f };
    ImColor Col_ESP_ExfilClose = { 1.f, 0.3f, 0.f, 0.5f };

    ImColor Col_ESP_Corpse = { 1.f, 1.f, 1.f, 0.9f };
    ImColor Col_ESP_Item_Normal = { 1.f, 1.f, 1.f, 0.7f };
    ImColor Col_ESP_Item_Mid = { 1.f, 0.6f, 0.f, 0.7f };
    ImColor Col_ESP_Item_Rare = { 1.f, 0.f, 0.f, 0.7f };

    ImColor CrosshairColor = { 0.f, 1.f, 0.f, 1.f };

    ImColor TEXT_COLOR_DEFAULT{ 1.f, 1.f, 1.f, 1.f };
    ImColor TEXT_COLOR_ATTENTION{ 1.f, 1.f, 0.f, 1.f };
    ImColor TEXT_COLOR_WARNING{ 1.f, 0.f, 0.f, 1.f };

    void GetESPInfo(const int& SpawnType, std::string& vOutStr, ImColor& vOutColor);

    void DrawLine(ImVec2 a, ImVec2 b, ImColor color, float width)
    {
        ImGui::GetBackgroundDrawList()->AddLine(ImVec2((int)a.x, (int)a.y), ImVec2((int)b.x, (int)b.y), color, width);
    }
    void RectFilled(float x0, float y0, float x1, float y1, ImColor color, float rounding, int rounding_corners_flags)
    {
        ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(x0, y0), ImVec2(x1, y1), color, rounding, rounding_corners_flags);
    }
    void HealthBar(float x, float y, float w, float h, int value, int v_max)
    {
        RectFilled(x, y, x + w, y + h, ImColor(0.f, 0.f, 0.f, 0.725f), 0.f, 0);
        RectFilled(x, y, x + w, y + ((h / float(v_max)) * (float)value), ImColor(min(510 * (v_max - value) / 100, 255), min(510 * value / 100, 255), 25, 255), 0.0f, 0);
    }
    void Circle(ImVec2 pos, float fov_size, ImColor color)
    {
        ImGui::GetBackgroundDrawList()->AddCircle(pos, fov_size, color, 100, 0);
    }
    void String(ImVec2 pos, ImColor color, const char* text)
    {
        ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), pos, color, text, text + strlen(text), 1024, 0);
    }
    void StringEx(ImVec2 pos, ImColor color, float font_size, const char* text)
    {
        ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), font_size, ImVec2(pos.x + 1.f, pos.y + 1.f), ImColor(0.f, 0.f, 0.f, 1.f), text, text + strlen(text), 1024, 0);
        ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), font_size, pos, color, text, text + strlen(text), 1024, 0);
    }

    // Render.cpp
    ImVec2 ToImVec2(const ImVec2& value); // Convert to int
    ImVec2 ToImVec2(const Vector2& value);
    ImColor WithAlpha(const ImColor& color, const float& alpha);
    float GetHueFromTime(float speed = 5.0f);
    ImColor GenerateRainbow(float speed = 5.0f);
    void DrawLine(const Vector2 p1, const Vector2 p2, ImColor color, float thickness = 1.f);
    void DrawBox(int right, int left, int top, int bottom, ImColor color, float thickness = 1.f);
    void DrawCircle(const Vector2 pos, float size, ImColor color);
    void DrawCircle(const Vector2 pos, float size, ImColor color, float alpha);
    void DrawCircleFilled(const Vector2 pos, float size, ImColor color, float alpha);
    void RectFilled(int x0, int y0, int x1, int y1, ImColor color);
    void RectFilled(int x0, int y0, int x1, int y1, ImColor color, float alpha);
    void HealthBar(int x, int y, int w, int h, int value, int v_max, ImColor shadow, float global_alpha);
    void String(const Vector2 pos, ImColor color, float alpha, const char* text);
    void StringEx(Vector2 pos, ImColor shadow_color, float global_alpht, float font_size, const char* text);
};