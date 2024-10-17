#include "Entity.h"

std::string string_To_UTF8(const std::string& str);

std::string string_To_UTF8(const std::string& str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

	wchar_t* pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴
	ZeroMemory(pwBuf, nwLen * 2 + 2);

	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char* pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);

	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr(pBuf);

	delete[]pwBuf;
	delete[]pBuf;

	pwBuf = NULL;
	pBuf = NULL;

	return retStr;
}

Vector3 Get::PlayerPos(intptr_t addr)
{
	return *reinterpret_cast<Vector3*>(addr + Offset::Pawn::bPos);
}

int Get::PlayerHealth(intptr_t addr)
{
	int health = Address::ReadInternalMem<int>(addr, { Offset::Pawn::iHealth });
	return health;

}

int Get::PlayerTeam(intptr_t addr)
{

	int team = Address::ReadInternalMem<int>(addr, { Offset::Pawn::iTeamNum }) ;

	return team;

}

bool Get::PawnAlive(intptr_t addr)
{

	return Address::ReadInternalMem<int32_t>(addr, { Offset::Pawn::PawnAlive }) == 1;

}

bool Get::PlayerAlive(intptr_t addr)
{
	
	return Address::ReadInternalMem<int32_t>(addr, { Offset::Pawn::iHealth }) > 0;

}

intptr_t Get::PlayerPawnAddress(intptr_t addr)
{

	int32_t pawn = Address::ReadInternalMem<int32_t>(addr, { Offset::Controller::hPawn });

	const intptr_t cGameEntity{ Address::GetEntityList() + Offset::EntityListPtr };
	const int32_t pawnListOffset{ 8 * ((pawn & 0x7FFF) >> 9) };
	const int32_t pawnBaseOffset{ 0x78 * (pawn & 0x1FF) };

	intptr_t pawnBase{};

	if (pawnListOffset)
		pawnBase = static_cast<intptr_t>(Address::ReadInternalMem<uintptr_t>(cGameEntity, { pawnListOffset, pawnBaseOffset }));
	else
		pawnBase = static_cast<intptr_t>(Address::ReadInternalMem<uintptr_t>(*reinterpret_cast<intptr_t*>(cGameEntity), { pawnBaseOffset }));

	if (!pawnBase) return false;
	
	return pawnBase;

}

Vector3 Get::BonePos(intptr_t addr, int32_t index)
{
	int32_t d = 32 * index;
	intptr_t address{};
	address = static_cast<intptr_t>(Address::ReadInternalMem<uintptr_t>(addr, { Offset::Pawn::pGameSceneNode }));
	if (!address)
	{
		return Vector3();
	}
	address = static_cast<intptr_t>(Address::ReadInternalMem<uintptr_t>(address, { Offset::Pawn::BoneArray }));
	if (!address) 	
	{
		return Vector3();
	}
	return *reinterpret_cast<Vector3*>(address  + d);
}

bool Get::IsDormant(intptr_t addr)
{
	bool Dormant = Address::ReadInternalMem<bool>(addr,
		{ Offset::Pawn::pGameSceneNode, Offset::Pawn::bDormant });

	return Dormant;
}

std::string Get::PlayerName(intptr_t addr)
{
	const char* sEntNamePtr{ reinterpret_cast<char*>(addr + Offset::Controller::cEntName) };
	if (!sEntNamePtr) return "UnKnown";

	const std::string entNameBuffer(sEntNamePtr);



	return string_To_UTF8(entNameBuffer);
}

Vector3 Get::WindowSize() 
{
	Vector3 ret{};
	ret.x = ImGui::GetIO().DisplaySize.x ;
	ret.y = ImGui::GetIO().DisplaySize.y ;
	return ret;
}

Vector3 Get::LastCameraPos(intptr_t addr)
{
	return *reinterpret_cast<Vector3*>(addr + Offset::Pawn::vLastClipCameraPos);;
}


void Set::RadarHack(intptr_t addr) 
{
	bool* SpottedStatus = reinterpret_cast<bool*>(addr + Offset::Pawn::bSpottedByMask);
	*SpottedStatus = 1;
}


void Set::GlowHack(intptr_t addr)
{
	intptr_t GlowColorOverride = addr + Offset::Pawn::m_Glow + Offset::Pawn::m_GlowOverride;
	intptr_t GlowFunction = addr + Offset::Pawn::m_Glow + Offset::Pawn::m_bGlowing;

	int* GlowColor = reinterpret_cast<int*>(GlowColorOverride);
	bool* glow = reinterpret_cast<bool*>(GlowFunction);
	*GlowColor = 0x800000FF;
	*glow = 1;
}


std::string Get::GetWeaponName(intptr_t addr)
{
	intptr_t Weapon = 0;
	std::string WeaponName = {};

	Weapon = Address::RAM<intptr_t>(addr + Offset::Pawn::pClippingWeapon);

	Weapon = Address::RAM<intptr_t>(Weapon + 16);

	Weapon = Address::RAM<intptr_t>(Weapon + 32);

	char* sEntNamePtr{ reinterpret_cast<char*>(Weapon) };
	if (!sEntNamePtr) return "ERROR";

	WeaponName = std::string(sEntNamePtr);

	std::size_t Index = WeaponName.find("_");
	if (Index == std::string::npos || WeaponName.empty())
	{
		WeaponName = u8"UNKNOW_WEAPON";
	}
	else
	{
		WeaponName = WeaponName.substr(Index + 1, WeaponName.size() - Index - 1);
	}

	return WeaponName;
}