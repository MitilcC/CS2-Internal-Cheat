#include "LocalPlayer.h"


bool LocalPlayer::SetViewAngles(const Vector3& targetAngle)
{

	Vector3* viewAnglesPtr{ Address::GetViewAnglesPtr() };

	if (!viewAnglesPtr) return false;

	viewAnglesPtr->x = targetAngle.x;
	viewAnglesPtr->y = targetAngle.y;

	return true;
}

Vector3 LocalPlayer::GetViewAngles()
{
	return *reinterpret_cast<Vector3*>(Offset::GPointers::ClientMod + Offset::GPointers::ViewAngles);
}

bool LocalPlayer::SetSmoothViewAngles(Vector3 pTargetAngle, const int pSmoothValue)
{
	Vector3* lpViewAngles{ Address::GetViewAnglesPtr() };

	Vector3 deltaAngle{ pTargetAngle - *lpViewAngles };

	Aimbot::NormalizeYaw(deltaAngle.y);

	if (lpViewAngles->x != pTargetAngle.x)
		lpViewAngles->x += deltaAngle.x / pSmoothValue;

	if (lpViewAngles->y != pTargetAngle.y)
		lpViewAngles->y += deltaAngle.y / pSmoothValue;

	return true;
}

