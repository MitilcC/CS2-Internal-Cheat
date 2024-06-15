#include "Entity.h"

Vector3 Get::PlayerPos(intptr_t addr)
{
	return *reinterpret_cast<Vector3*>(addr + Offset::Pawn::bPos);
}

int32_t Get::PlayerHealth(intptr_t addr)
{
	int32_t health = Address::ReadInternalMem<int32_t>(addr, { Offset::Pawn::iHealth });
	return health;

}

int32_t Get::PlayerTeam(intptr_t addr)
{

	int32_t team = Address::ReadInternalMem<int32_t>(addr, { Offset::Pawn::iTeamNum }) ;

	return team;

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

	return entNameBuffer;
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



