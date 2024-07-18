#pragma once
#include <cstdint>
#include "CS2_Dumper/offsets.hpp"
#include "CS2_Dumper/client.dll.hpp"

namespace Offset
{
	inline constexpr intptr_t EntityListPtr{ 0x10 }; // GameEntitySystem + EntityListPtr
	inline constexpr intptr_t IsMatchStarted{ 0xA0 }; // Prediction + IsMatchStarted
	inline constexpr intptr_t PlayerPawn{ cs2_dumper::schemas::client_dll::CCSPlayerController::m_hPlayerPawn };

	inline constexpr intptr_t EntityList{ cs2_dumper::offsets::client_dll::dwEntityList};
	inline constexpr intptr_t LocalPlayerControl{ cs2_dumper::offsets::client_dll::dwLocalPlayerController };
	inline constexpr intptr_t ViewMatrix{ cs2_dumper::offsets::client_dll::dwViewMatrix };

	namespace GPointers
	{
		inline intptr_t ClientMod{};
		inline intptr_t Engine2Mod{};
		inline intptr_t GameRules{};
		inline intptr_t CCSGO_Input{};
		inline intptr_t LP_Controller{};
		inline intptr_t ViewMatrix{};
		inline intptr_t ViewAngles{};
		inline intptr_t EntityList{};
		inline intptr_t Prediction{};
	}

	namespace Pawn
	{
		inline constexpr intptr_t PawnAlive = cs2_dumper::schemas::client_dll::CCSPlayerController::m_bPawnIsAlive;
		inline constexpr intptr_t BoneArray{ cs2_dumper::schemas::client_dll::CSkeletonInstance::m_modelState + 0x80 }; // GameSceneNode + BoneArray
		inline constexpr intptr_t iHealth{ cs2_dumper::schemas::client_dll::C_BaseEntity::m_iHealth };
		inline constexpr intptr_t pGameSceneNode{ cs2_dumper::schemas::client_dll::C_BaseEntity::m_pGameSceneNode };
		inline constexpr intptr_t iTeamNum{ cs2_dumper::schemas::client_dll::C_BaseEntity::m_iTeamNum };
		inline constexpr intptr_t vLastClipCameraPos{ cs2_dumper::schemas::client_dll::C_CSPlayerPawnBase::m_vecLastClipCameraPos };
		inline constexpr intptr_t vAngEyeAngles{ cs2_dumper::schemas::client_dll::C_CSPlayerPawnBase::m_angEyeAngles };
		inline constexpr intptr_t bSpottedMask{ cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_entitySpottedState + cs2_dumper::schemas::client_dll::EntitySpottedState_t::m_bSpottedByMask }; // C_CSPlayerPawn::entitySpottedState + EntitySpottedState_t::bSpottedByMask
		inline constexpr intptr_t bDormant{ cs2_dumper::schemas::client_dll::CGameSceneNode::m_bDormant }; // GameSceneNode + bDormant
		inline constexpr intptr_t bPos{ cs2_dumper::schemas::client_dll::C_BasePlayerPawn::m_vOldOrigin }; // GameSceneNode + bDormant
		inline constexpr intptr_t IsAlive{ cs2_dumper::schemas::client_dll::CCSPlayerController::m_bPawnIsAlive };
		inline constexpr intptr_t CurrentArmor{ cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_ArmorValue };
		inline constexpr intptr_t pClippingWeapon{ cs2_dumper::schemas::client_dll::C_CSPlayerPawnBase::m_pClippingWeapon };
		inline constexpr intptr_t bSpottedByMask = cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_entitySpottedState + cs2_dumper::schemas::client_dll::EntitySpottedState_t::m_bSpottedByMask;	// C_CSPlayerPawn::entitySpottedState + EntitySpottedState_t::bSpottedByMask
		inline constexpr intptr_t m_Glow = cs2_dumper::schemas::client_dll::C_BaseModelEntity::m_Glow;
		inline constexpr intptr_t m_GlowOverride = cs2_dumper::schemas::client_dll::CGlowProperty::m_glowColorOverride;
		inline constexpr intptr_t m_bGlowing = cs2_dumper::schemas::client_dll::CGlowProperty::m_bGlowing;
		inline constexpr intptr_t m_fGlowColor = cs2_dumper::schemas::client_dll::CGlowProperty::m_fGlowColor;

	};

	namespace WeaponBaseData
	{
		inline constexpr intptr_t WeaponDataPTR = cs2_dumper::schemas::client_dll::C_BaseEntity::m_nSubclassID + 0x08;
		inline constexpr intptr_t szName = cs2_dumper::schemas::client_dll::CCSWeaponBaseVData::m_szName;
		inline constexpr intptr_t Clip1 = cs2_dumper::schemas::client_dll::C_BasePlayerWeapon::m_iClip1;					// C_BasePlayerWeapon::m_iClip1
		inline constexpr intptr_t MaxClip = cs2_dumper::schemas::client_dll::CBasePlayerWeaponVData::m_iMaxClip1;					// CBasePlayerWeaponVData::m_iMaxClip1
		inline constexpr intptr_t CycleTime = cs2_dumper::schemas::client_dll::CCSWeaponBaseVData::m_flCycleTime;
		inline constexpr intptr_t Penetration = cs2_dumper::schemas::client_dll::CCSWeaponBaseVData::m_flPenetration;
		inline constexpr intptr_t WeaponType = cs2_dumper::schemas::client_dll::CCSWeaponBaseVData::m_WeaponType;
		inline constexpr intptr_t Inaccuracy = cs2_dumper::schemas::client_dll::CCSWeaponBaseVData::m_flInaccuracyMove;				// CCSWeaponBaseVData::m_flInaccuracyMove
		inline constexpr intptr_t inReload = cs2_dumper::schemas::client_dll::C_CSWeaponBase::m_bInReload;
		inline constexpr intptr_t m_nNumBullets = cs2_dumper::schemas::client_dll::CCSWeaponBaseVData::m_nNumBullets;
		inline constexpr intptr_t WeaponSize = 0x50;
		inline constexpr intptr_t ActiveWeapon = cs2_dumper::schemas::client_dll::CPlayer_WeaponServices::m_hActiveWeapon;
		inline constexpr intptr_t Item = cs2_dumper::schemas::client_dll::C_AttributeContainer::m_Item;						// C_AttributeContainer::m_Item
		inline constexpr intptr_t ItemDefinitionIndex = cs2_dumper::schemas::client_dll::C_EconItemView::m_iItemDefinitionIndex;
		inline constexpr intptr_t m_MeshGroupMask = cs2_dumper::schemas::client_dll::CModelState::m_MeshGroupMask;			// CModelState::m_MeshGroupMask
	} 

	namespace Controller
	{
		inline constexpr intptr_t cEntName{ cs2_dumper::schemas::client_dll::CBasePlayerController::m_iszPlayerName };
		inline constexpr intptr_t hPawn{ cs2_dumper::schemas::client_dll::CCSPlayerController::m_hPlayerPawn };
	};

	namespace CCSGO_Input
	{
		inline constexpr intptr_t ViewAngles{ 0xB0 }; // CCSGOInput - ViewAngles
	}

	namespace CS_GameRules
	{
		inline constexpr intptr_t GameModeRules{ cs2_dumper::schemas::client_dll::C_CSGameRules::m_pGameModeRules };
		inline constexpr intptr_t DeathMatchPtr{ 0x30 }; // GameRules + GameModeRules + DeathMatchPtr
	};
}