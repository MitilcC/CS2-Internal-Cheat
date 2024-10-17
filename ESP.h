#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include "Address.h"
#include "LocalPlayer.h"
#include "Entity.h"
#include "menu.h"
#include "Ults.h"
#include <vector>
#include <bitset>
#include "Console.h"
#include "Bone.h"

namespace ESP
{
	void DrawHealth(float MaxHealth, float CurrentHealth, ImVec2 Pos, ImVec2 Size, bool Horizontal = true);
	bool Start();
};