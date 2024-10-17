#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include "Entity.h"
#include "Ults.h"
#include "Math.h"

namespace Bone
{
	void Start(intptr_t pawn , ImColor BoneColor);

	void HeadCricle(intptr_t pawn, ImColor Color);

	inline std::vector<Vector3>BoneDrawList{};

	void DrawLine(std::vector<Vector3> list, ImColor Color);

};