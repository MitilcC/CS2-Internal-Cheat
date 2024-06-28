// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "include.h"
#include "Cheat.h"
#include "Search.h"
#include "Menu.h"
#include "imgui/font.h"
#include "Console.h"

bool init = false;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;

void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	io.Fonts->AddFontFromMemoryTTF(&inter, sizeof inter, 16 * dpi_scale, NULL, io.Fonts->GetGlyphRangesCyrillic());
	chinesefont = io.Fonts->AddFontFromFileTTF("c:/windows/fonts/simhei.ttf", 15.0f, NULL, io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
	tab_text1 = io.Fonts->AddFontFromMemoryTTF(&inter, sizeof inter, 12 * dpi_scale, NULL, io.Fonts->GetGlyphRangesCyrillic());
	tab_text2 = io.Fonts->AddFontFromMemoryTTF(&inter, sizeof inter, 24 * dpi_scale, NULL, io.Fonts->GetGlyphRangesCyrillic());
	tab_text3 = io.Fonts->AddFontFromMemoryTTF(&inter, sizeof inter, 40 * dpi_scale, NULL, io.Fonts->GetGlyphRangesCyrillic());
	ico = io.Fonts->AddFontFromMemoryTTF(&icon, sizeof icon, 25 * dpi_scale, NULL, io.Fonts->GetGlyphRangesCyrillic());
	ico_2 = io.Fonts->AddFontFromMemoryTTF(&Menuicon, sizeof Menuicon, 20 * dpi_scale, NULL, io.Fonts->GetGlyphRangesCyrillic());
	ico_subtab = io.Fonts->AddFontFromMemoryTTF(&icon, sizeof icon, 35 * dpi_scale, NULL, io.Fonts->GetGlyphRangesCyrillic());
	ico_logo = io.Fonts->AddFontFromMemoryTTF(&icon, sizeof icon, 31 * dpi_scale, NULL, io.Fonts->GetGlyphRangesCyrillic());
	tab_textA = io.Fonts->AddFontFromMemoryTTF(&inter, sizeof inter, 19 * dpi_scale, NULL, io.Fonts->GetGlyphRangesCyrillic());
	ico_minimize = io.Fonts->AddFontFromMemoryTTF(&icon, sizeof icon, 27 * dpi_scale, NULL, io.Fonts->GetGlyphRangesCyrillic());

	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			init = true;
		}

		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}


	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	Cheat::Run();

	ImGui::Render();

	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return oPresent(pSwapChain, SyncInterval, Flags);
}

DWORD WINAPI MainThread(LPVOID lpReserved)
{

	PatternScan patternScan{};

	if (patternScan.InitPointers())
	{

		//Console::InitConsole();

		bool init_hook = false;
		do
		{
			if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
			{
				kiero::bind(8, (void**)&oPresent, hkPresent);
				init_hook = true;
			}
		} while (!init_hook);

	}
	else
	{
		MessageBox(0,L"Update Offsets error !",0,0);
	}

	return TRUE;
}
template <typename C> 
constexpr int StringCompare(const C* tszLeft, const C* tszRight)
{
	if (tszLeft == nullptr)
		return -1;

	if (tszRight == nullptr)
		return 1;

	using ComparisonType_t = std::conditional_t<std::is_same_v<C, char>, std::uint8_t, std::conditional_t<sizeof(wchar_t) == 2U, std::int16_t, std::int32_t>>;

	ComparisonType_t nLeft, nRight;
	do
	{
		nLeft = static_cast<ComparisonType_t>(*tszLeft++);
		nRight = static_cast<ComparisonType_t>(*tszRight++);

		if (nLeft == C('\0'))
			break;
	} while (nLeft == nRight);

	return nLeft - nRight;
}
#pragma region memory_get

void* GetModuleBaseHandle(const wchar_t* wszModuleName)
{
	const _PEB* pPEB = reinterpret_cast<_PEB*>(__readgsqword(0x60));

	if (wszModuleName == nullptr)
		return pPEB->ImageBaseAddress;

	void* pModuleBase = nullptr;
	for (LIST_ENTRY* pListEntry = pPEB->Ldr->InMemoryOrderModuleList.Flink; pListEntry != &pPEB->Ldr->InMemoryOrderModuleList; pListEntry = pListEntry->Flink)
	{
		const _LDR_DATA_TABLE_ENTRY* pEntry = CONTAINING_RECORD(pListEntry, _LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);

		if (pEntry->FullDllName.Buffer != nullptr && StringCompare(wszModuleName, pEntry->BaseDllName.Buffer) == 0)
		{
			pModuleBase = pEntry->DllBase;
			break;
		}
	}

	return pModuleBase;
}
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  dwReason,
                       LPVOID lpReserved
                     )
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
/*
 * check did all game modules have been loaded
 * @note: navsystem.dll is the last loaded module
 * port from asphyxia
 */
		while (GetModuleBaseHandle(L"navsystem.dll") == nullptr)
			Sleep(150);//chk per 150ms
			

		CreateThread(nullptr, 0, MainThread, hModule, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
}

