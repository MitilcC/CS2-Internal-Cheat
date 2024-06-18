#pragma once
#include "Windows.h"
#include "Offsets.h"
#include "Address.h"
#include "Vector.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include <string>
#include <bitset>
#include <map>

class Player
{
public:
	intptr_t control;
	intptr_t pawn;
	int32_t health;
	int32_t team;
	Vector3 pos;
	std::string name;
};

enum BoneIndex
{
	head = 6,
	neck_0 = 5,
	spine_1 = 4,
	spine_2 = 2,
	pelvis = 0,
	arm_upper_L = 8,
	arm_lower_L = 9,
	hand_L = 10,
	arm_upper_R = 13,
	arm_lower_R = 14,
	hand_R = 15,
	leg_upper_L = 22,
	leg_lower_L = 23,
	ankle_L = 24,
	leg_upper_R = 25,
	leg_lower_R = 26,
	ankle_R = 27,
};

namespace Get
{
	intptr_t PlayerPawnAddress(intptr_t addr);
	bool PawnAlive(intptr_t addr);
	bool PlayerAlive(intptr_t addr);
	int32_t PlayerTeam(intptr_t addr);
	int32_t PlayerHealth(intptr_t addr);
	Vector3 PlayerPos(intptr_t addr);
	Vector3 BonePos(intptr_t addr, int32_t index);
	bool IsDormant(intptr_t addr);
	std::string PlayerName(intptr_t addr);
	Vector3 WindowSize();
	Vector3 LastCameraPos(intptr_t addr);
}

namespace Set
{
	void RadarHack(intptr_t addr);
}

struct BoneJoint
{
	Vector3 pos{};
	float scale;
	float rotation[4];
};
