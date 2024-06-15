#include "ESP.h"

void ESP::DrawHealthBar(int boxX, int boxY, int w, int boxH, int health) 
{
	int left = boxX - w - 3;
	ImGui::GetBackgroundDrawList()->AddRect(ImVec2(left - 1 ,boxY + 3), ImVec2(left - 1 +  w, boxY + boxH - 3),ImColor(0,0,0), 4);
	ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(left, boxY + 4), ImVec2(left + w, boxY + boxH - 4), ImColor(255,255,255), 4);
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(left - 23, boxY + 3), ImColor(0, 0, 0), std::to_string(health).c_str());
	float pos = (100 - health) / 100;

	ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(left, boxY + 4 + boxH * pos), ImVec2(left + w, boxY + boxH - 4), ImColor(0,255,64), 4);

}

bool ESP::Start() 
{

	Player LocalPlayer{};

	LocalPlayer.control = Address::GetLocalPlayerControl();

	LocalPlayer.pawn = Get::PlayerPawnAddress(LocalPlayer.control);

	LocalPlayer.team = Get::PlayerTeam(LocalPlayer.pawn);


	for (int i{ 0 }; i < 64; ++i)
	{

		Vector4 Draw {};
		int distance = 0;

		Player Entity{};

		Entity.control = Address::GetEntityBase(i);

		Entity.pawn = Get::PlayerPawnAddress(Entity.control);
		
		Entity.team = Get::PlayerTeam(Entity.pawn);

		Entity.health = Get::PlayerHealth(Entity.pawn);

		if(Get::IsDormant(Entity.pawn))
		{
			continue;
		}

		ImGui::GetBackgroundDrawList()->AddText(ImVec2(100, i * 10), ImColor(0, 255, 255), std::to_string(Entity.health).c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImVec2(200, i * 10), ImColor(0, 255, 255), std::to_string(Entity.team).c_str());


		if (Menu::TeamCheck && Entity.team == LocalPlayer.team)
		{
			continue;
		}

		if (Entity.team != 2 && Entity.team != 3)
		{
			continue;
		}

		if (!Get::PlayerAlive(Entity.pawn))
		{
			continue;
		}


		Entity.name = Get::PlayerName(Entity.control);

		Entity.pos = Get::PlayerPos(Entity.pawn);

		const float  w  { ImGui::GetIO().DisplaySize.x };
		const float  h  { ImGui::GetIO().DisplaySize.y };

		Vector3 currBotPos = Get::BonePos(Entity.pawn,Bone::ankle_L) ;

		Vector3 currTopPos = Get::BonePos(Entity.pawn, Bone::head) ;

		Vector3 curr2DBot{};
		Vector3 curr2DTop{};


		if (!Utils::WorldToScreen(currBotPos, curr2DBot, Address::GetViewMatrixPtr(), w, h))
			continue;
		if (!Utils::WorldToScreen(currTopPos, curr2DTop, Address::GetViewMatrixPtr(), w, h))
			continue;

		const float height{ ::abs(curr2DTop.y - curr2DBot.y) * 1.25f };
		const float width{ height / 2.f };
		const float x = curr2DTop.x - (width / 2.f);
		const float y = curr2DTop.y - (width / 2.5f);

		if (Menu::ESP::Box) 
		{
			ImGui::GetBackgroundDrawList()->AddRect(ImVec2(x, y), ImVec2(x + width, y + height), ImColor(0, 255, 255));
		}

		if (Menu::ESP::Line)
		{
			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(w / 2, h), ImVec2(x + height / 2, y + height), ImColor(0, 255, 255));
		}

		if (Menu::ESP::Health)
		{
			DrawHealthBar(x, y, 5, height, Entity.health);
		}

		if (Menu::ESP::Name)
		{
			ImGui::GetBackgroundDrawList()->AddText(ImVec2(x, y - 10), ImColor(0, 255, 255), Entity.name.c_str());
		}



	    
	}

	return true;
}

