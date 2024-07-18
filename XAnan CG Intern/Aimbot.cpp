#include "Aimbot.h"

Vector3 LastAngles{};
bool ShotFired = false;
Vector3 WantAngele{};

bool Aimbot::GetBestTarget()
{
	Player LocalPlayer{};

	LocalPlayer.control = Address::GetLocalPlayerControl();

	if (!LocalPlayer.control)
		return false;

	LocalPlayer.pawn = Get::PlayerPawnAddress(LocalPlayer.control);

	if (!LocalPlayer.pawn)
		return false;

	LocalPlayer.team = Get::PlayerTeam(LocalPlayer.pawn);

	if (!Get::PlayerAlive(LocalPlayer.pawn))
	{
		return false;
	}

	int Distance = 0;
	int LastDistance = 999999999;

	for (int i{ 0 }; i < 64; ++i)
	{

		Player Entity{};

		Entity.control = Address::GetEntityBase(i);

		if (!Entity.control)
			continue;

		if (!Get::PawnAlive(Entity.control))
		{
			continue;
		}

		Entity.pawn = Get::PlayerPawnAddress(Entity.control);

		if (!Entity.pawn)
			continue;

		Entity.team = Get::PlayerTeam(Entity.pawn);

		Entity.health = Get::PlayerHealth(Entity.pawn);

		if (Get::IsDormant(Entity.pawn))
		{
			continue;
		}

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

		Vector3 AimPos = Get::BonePos(Entity.pawn, Menu::Aimbot::AimPos);

		Vector3 EndPos{};

		Vector3 Window = Get::WindowSize();

		if (!Utils::WorldToScreen(AimPos, EndPos, Address::GetViewMatrixPtr(), Window.x, Window.y))
			continue;

		if (EndPos.x > Window.x / 2 - Menu::Aimbot::AimSize && EndPos.x < Window.x / 2 + Menu::Aimbot::AimSize && EndPos.y > Window.y / 2 - Menu::Aimbot::AimSize && EndPos.y < Window.y / 2 + Menu::Aimbot::AimSize)
		{
			int left = Window.x / 2 - EndPos.x ;
			int right = Window.y / 2 - EndPos.y;
			Distance = Math::distance(left,right);
			if(Distance < LastDistance)
			{
				LastDistance = Distance;
				Target::addr= Entity.pawn;
			}
		}
	}

	return true;
}


void Aimbot::NormalizePitch(float& pPitch)
{
	pPitch = (pPitch < -89.0f) ? -89.0f : pPitch;

	pPitch = (pPitch > 89.f) ? 89.0f : pPitch;
}

void Aimbot::NormalizeYaw(float& pYaw)
{
	while (pYaw > 180.f) pYaw -= 360.f;

	while (pYaw < -180.f) pYaw += 360.f;
}

float Aimbot::GetMagnitude(const Vector3& pVec)
{
	return ::sqrtf((pVec.x * pVec.x) +
		(pVec.y * pVec.y) +
		(pVec.z * pVec.z));
}

Vector3 Aimbot::GetTargetAngle(Vector3 pTargetPos)
{
	Vector3 targetAngle{};
	Player LocalPlayer{};

	LocalPlayer.control = Address::GetLocalPlayerControl();

	LocalPlayer.pawn = Get::PlayerPawnAddress(LocalPlayer.control);

	Vector3 lpPos = Get::LastCameraPos(LocalPlayer.pawn);

	const Vector3 deltaPos{ pTargetPos - lpPos };

	const float distPos{ GetMagnitude(deltaPos) };

	constexpr float radToDegree{ 57.295776f };
	targetAngle.x = -asinf(deltaPos.z / distPos) * radToDegree;
	targetAngle.y = atan2f(deltaPos.y, deltaPos.x) * radToDegree;

	NormalizePitch(targetAngle.x);

	return targetAngle;
}

void Aimbot::ReleaseMouseButton()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

bool Aimbot::ShotTarget()
{
	Vector3 targetAngle{};
	LastAngles = LocalPlayer::GetViewAngles();
	targetAngle = Aimbot::GetTargetAngle(Get::BonePos(Target::addr,Menu::Aimbot::AimPos));
	LocalPlayer::SetViewAngles(targetAngle);
	//mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	ShotFired = true;
}

bool Aimbot::Start()
{
	bool CanAim = GetBestTarget();

	if (GetAsyncKeyState(Menu::Aimbot::AimKey) && CanAim)
	{
		if (Get::PlayerAlive(Target::addr))
		{
			ShotTarget();
		}
		else
			Target::addr = {};
	}
	else
	{
		Target::addr = 0;
	}

	if (ShotFired)
	{
		//LocalPlayer::SetViewAngles(LastAngles);
		ShotFired = false;
	}

}

