#include "Cheat/Framework.h"
#include "Framework/Overlay/Overlay.h"
#include "Framework/ImGui/imgui_freetype.h"
#pragma comment(lib, "freetype.lib")

auto cheat = std::make_unique<CFramework>();

bool CFramework::Init()
{
	// ImGui io setting
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.IniFilename = nullptr;
	io.LogFilename = nullptr;

	ImFontConfig cfg;
	cfg.FontBuilderFlags |= ImGuiFreeTypeBuilderFlags_ForceAutoHint;

	// Load Font
	io.Fonts->AddFontFromMemoryCompressedTTF(RobotoRegular_compressed_data, RobotoRegular_compressed_size, 13.f, nullptr);

	// Load Icon
	static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
	ImFontConfig icons_config;
	icons_config.MergeMode = true;
	icons_config.GlyphOffset.y = 2.f;
	icon = io.Fonts->AddFontFromMemoryCompressedTTF(FA_compressed_data, FA_compressed_size, 16.f, &icons_config, icons_ranges);
	io.Fonts->Build();

	// ImGui Style
	ImGuiStyle& style = ImGui::GetStyle();

	// Border
	style.WindowBorderSize = 0.f;
	style.ChildBorderSize = 1.f;
	style.PopupBorderSize = 1.f;
	style.FrameBorderSize = 0.f;
	style.TabBorderSize = 1.f;
	style.TabBarBorderSize = 0.f;
	// Rounding
	style.WindowRounding = 0.f;
	style.ChildRounding = 6.f;
	style.FrameRounding = 0.f;
	style.PopupRounding = 0.f;
	style.TabRounding = 0.f;
	// Misc
	style.ScrollbarSize = 3.f;
	style.GrabMinSize = 5.f;
	style.SeparatorTextBorderSize = 1.f;
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);

	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_WindowBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
	colors[ImGuiCol_Border] = ImVec4(0.27f, 0.27f, 0.27f, 0.50f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.45f, 0.45f, 0.81f, 1.00f);
	colors[ImGuiCol_Border] = ImVec4(0.45f, 0.45f, 0.81f, 0.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.39f, 0.39f, 0.78f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.35f, 0.35f, 0.78f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.27f, 0.27f, 0.27f, 0.50f);
	colors[ImGuiCol_Tab] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.13f, 0.13f, 0.13f, 0.97f);
	colors[ImGuiCol_TabActive] = ImVec4(0.09f, 0.09f, 0.09f, 1.00f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.45f, 0.45f, 0.81f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.45f, 0.45f, 0.81f, 1.00f);

	return true;
}

void Overlay::OverlayUserFunction()
{
	cheat->MiscAll();

	cheat->RenderInfo();

	if (g.g_ESP)
		cheat->RenderESP();

	if (g.ShowMenu)
		cheat->RenderMenu();
}

// DEBUG時にはコンソールウィンドウを表示する
#if _DEBUG
int main()
#else 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#endif
{
	auto overlay = std::make_unique<Overlay>();

	// Fix DPI Scale
	SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);

	// ウィンドウをベースにして初期化を行う
	if (!m.AttachProcess("EscapeFromTarkov", InitMode::WINDOW_TITLE)) // 詳細は Memory/Memory.h を参照
		return 1;

	// Overlay
	if (!overlay->InitOverlay("EscapeFromTarkov", InitMode::WINDOW_TITLE)) // MemoryInitModeと同様
		return 2;

	// Cheat
	if (!cheat->Init())
		return 3;

	// スレッドを作成
	std::thread([&]() { cheat->UpdateList(); }).detach();
	std::thread([&]() { cheat->UpdateStaticList(); }).detach();

	overlay->OverlayLoop();
	overlay->DestroyOverlay();
	m.DetachProcess();
	g.process_active = false;

	return 0;
}