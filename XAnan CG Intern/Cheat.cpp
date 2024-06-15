#include "Cheat.h"

bool Cheat::Run() 
{
	if (GameState::IsMatchStarted())
	{
		// Cheat Features
		if (Menu::bAimBot) Aimbot::Start();
		if (Menu::bESP) ESP::Start();
	}
	else
		ImGui::GetBackgroundDrawList()->AddText(ImVec2(200, 100), ImColor(255, 0, 0), std::to_string(GameState::GetMatchState()).c_str());

	return true;

}