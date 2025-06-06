#include "Cheat/FrameCore.h"
#include "Framework/Overlay/Overlay.h"
#pragma comment(lib, "freetype.lib")

CFramework* cheat  = new CFramework;

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

	// ImGui io setting
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.IniFilename = nullptr;
	io.LogFilename = nullptr;

	// Load Font
	io.Fonts->AddFontFromMemoryCompressedTTF(RobotoRegular_compressed_data, RobotoRegular_compressed_size, 13.f, nullptr);

	// Load Icon
	static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
	ImFontConfig icons_config;
	icons_config.MergeMode = true;
	icons_config.GlyphOffset.y = 2.f;
	cheat->icon = io.Fonts->AddFontFromMemoryCompressedTTF(FA_compressed_data, FA_compressed_size, 16.f, &icons_config, icons_ranges);
	io.Fonts->Build();

	// スレッドを作成
	std::thread([&]() { cheat->UpdateList(); }).detach();
	std::thread([&]() { cheat->UpdateStaticList(); }).detach();

	overlay->OverlayLoop();
	overlay->DestroyOverlay();
	m.DetachProcess();
	g.process_active = false;
	delete cheat;

	return 0;
}