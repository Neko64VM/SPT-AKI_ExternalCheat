#pragma once
#include "..\ImGui\imgui.h"
#include "..\ImGui\imgui_impl_win32.h"
#include "..\ImGui\imgui_impl_dx11.h"
#include <dwmapi.h>
#include <thread>
#include <string>
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

class Overlay
{
private:
	// オーバーレイに登録する情報
	WNDCLASSEXA wc{};
	HWND Hwnd;
	char Title[32] = "The Overlay";
	char Class[32] = "WND_CLS";

	// ターゲットウィンドウに関する情報
	HWND TargetHwnd;
	char TargetClass[128]{};
	RECT GameRect{};
	POINT GamePoint{};

	// Window LONG
	LONG MenuStyle = WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_TOPMOST;
	LONG ESPStyle = WS_EX_TRANSPARENT | WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_TOPMOST;

	bool CreateOverlay();
	HWND GetTargetWindow(const std::string processName);	// 実行ファイル名からウィンドウハンドルを取得する
public:
	bool InitOverlay(const std::string targetName, int mode);
	void OverlayUserFunction();
	void OverlayLoop();
	void DestroyOverlay();
	void OverlayManager();
};

extern ID3D11Device* g_pd3dDevice;
extern ID3D11DeviceContext* g_pd3dDeviceContext;
extern IDXGISwapChain* g_pSwapChain;
extern ID3D11RenderTargetView* g_mainRenderTargetView;