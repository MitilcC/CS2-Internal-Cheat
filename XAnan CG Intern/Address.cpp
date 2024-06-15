#include "Address.h"

intptr_t Address::GetEntityBase(intptr_t pIndex)
{
	const intptr_t entListBase{ static_cast<intptr_t>(ReadInternalMem<uintptr_t>(Offset::GPointers::ClientMod,
		{ Offset::GPointers::EntityList, Offset::EntityListPtr })) };

	constexpr intptr_t entPadding{ 0x78 };
	const intptr_t currEntIndex{ (pIndex + 1) * entPadding };
	return static_cast<intptr_t>(ReadInternalMem<uintptr_t>(entListBase, { currEntIndex }));
}

float* Address::GetViewMatrixPtr()
{
	return reinterpret_cast<float*>(Offset::GPointers::ClientMod + Offset::GPointers::ViewMatrix);
}

Vector3* Address::GetViewAnglesPtr()
{
	return reinterpret_cast<Vector3*>(Offset::GPointers::ClientMod + Offset::GPointers::ViewAngles);
}

intptr_t Address::GetPredictionBase()
{
	return static_cast<intptr_t>(ReadInternalMem<uintptr_t>(Offset::GPointers::ClientMod, { Offset::GPointers::Prediction }));
}

intptr_t Address::GetLocalPlayerControl()
{
	return static_cast<intptr_t>(ReadInternalMem<uintptr_t>(Offset::GPointers::ClientMod, { Offset::GPointers::LP_Controller }));
}

int* Address::GetMatchStateIdPtr()
{
	return reinterpret_cast<int*>(Address::GetPredictionBase() + Offset::IsMatchStarted);
}

intptr_t* Address::GetDeathMatchRulesPtr()
{
	const intptr_t deathMatchRulesPtr{ static_cast<intptr_t>(ReadInternalMem<uintptr_t>(Offset::GPointers::ClientMod,
		{
			Offset::GPointers::GameRules,
			Offset::CS_GameRules::GameModeRules ,
			Offset::CS_GameRules::DeathMatchPtr
		}
	)) };

	return reinterpret_cast<intptr_t*>(deathMatchRulesPtr);
}

intptr_t Address::GetEntityList()
{
	return static_cast<intptr_t>(ReadInternalMem<uintptr_t>(Offset::GPointers::ClientMod, { Offset::GPointers::EntityList }));
}