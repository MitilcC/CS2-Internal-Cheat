#pragma once
#include "Address.h"
#include "LocalPlayer.h"
#include "Entity.h"
#include "Ults.h"
#include "menu.h"
#include <vector>
#include <bitset>
#include <thread>
#include "Console.h"
#include "math.h"

namespace Aimbot
{
	bool Start();
	bool GetBestTarget();
	void NormalizePitch(float& pPitch);
	void NormalizeYaw(float& pYaw);
	float GetMagnitude(const Vector3& pVec);
	Vector3 GetTargetAngle(Vector3 pTargetPos);
	bool ShotTarget();
	void ReleaseMouseButton();
};

namespace Target
{
	inline intptr_t addr{};
}