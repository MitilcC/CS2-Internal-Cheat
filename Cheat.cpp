#include "Cheat.h"
#include "Console.h"

bool Cheat::Run() 
{
	if (Menu::ShowMenu)
		Menu::start();
	
	static std::chrono::time_point LastTimePoint = std::chrono::steady_clock::now();
	auto CurTimePoint = std::chrono::steady_clock::now();

	if (GetAsyncKeyState(VK_HOME) && CurTimePoint - LastTimePoint >= std::chrono::milliseconds(150))
	{
		Menu::ShowMenu = !Menu::ShowMenu;
		LastTimePoint = CurTimePoint;
	}


	if (GameState::IsMatchStarted())
	{
		if (Menu::bAimBot) Aimbot::Start();

		if (Menu::bESP) ESP::Start();
	}


	return true;

}