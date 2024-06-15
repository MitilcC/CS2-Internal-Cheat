#pragma once
#include"GameState.h"
#include <Windows.h>
#include <iostream>
#include <map>
#include <vector>

namespace Menu
{
	inline bool bESP = { true };
	inline bool bAimBot = { true };
	inline bool TeamCheck = { true };
	inline int FovValue = { 90 };
	inline bool AimLock = { false };
	inline bool AimHead = { false };
	inline int smoothvalue = { 10 };

	namespace ESP 
	{
		inline bool Box = { true };
		inline bool Health = { true };
		inline bool Name = { true };
		inline bool Weapon = { true };
		inline bool Line = { true };
	}

	namespace Aimbot
	{
		inline bool Client = { true };
		inline bool TeamCheck = { true };
		inline int AimSize = { 100 };
		inline int AimKey = { 18 };
		inline int32_t AimPos = { 6 };
	}

}

