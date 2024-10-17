#pragma once
#include "Offsets.h"
#include "Vector.h"
#include "Peb.h"
#include <Windows.h>
#include <vector>
#include <map>
#include <string>
#include "Console.h"
class PatternScan
{
private:
	std::map<std::string_view, intptr_t> pointersState;

	PEB* GetPEB();
	LDR_DATA_TABLE_ENTRY* GetLdrEntry(const wchar_t* pModName);

	void SetViewAngles(LDR_DATA_TABLE_ENTRY* pLdrEntry, const std::string& pPattern);
	void SetPrediction(LDR_DATA_TABLE_ENTRY* pLdrEntry, const std::string& pPattern);
	void SetViewMatrix(LDR_DATA_TABLE_ENTRY* pLdrEntry, const std::string& pPattern);
	void SetGameRules(LDR_DATA_TABLE_ENTRY* pLdrEntry, const std::string& pPattern);
	void SetLpController(LDR_DATA_TABLE_ENTRY* pLdrEntry, const std::string& pPattern);
	void SetGameEntitySystem(LDR_DATA_TABLE_ENTRY* pLdrEntry, const std::string& pPattern);

	intptr_t GetPatternSize(const std::string& pPattern);
	std::vector<char> GetParsedPattern(const std::string& pPattern);
	intptr_t GetPatternAddr(char* currRegion, intptr_t pRegionSize, const std::string& pPattern);
	intptr_t GetValidMemRegion(LDR_DATA_TABLE_ENTRY* pLdrEntry, const std::string& pPattern);
	intptr_t ExtractPointer(intptr_t pPatternResult);

public:

	void SetClientMod(PVOID pDllBase);
	void SetEngine2Mod(PVOID pDllBase);
	bool ArePointersInit();
	bool InitPointers();
	std::map<std::string_view, intptr_t> GetPtrState();
};

namespace Pattern
{
	inline const std::string EntityList{ "48 8B 0D ?? ?? ?? ?? 48 89 7C 24 ?? 8B FA C1 EB" };
	inline const std::string ViewMatrix{ "48 8D 0D ?? ?? ?? ?? 48 C1 E0 06" };
	inline const std::string LP_Controller{ "48 8B ? ? ? ? ? 48 85 ? 74 ? B2 ? E8 ? ? ? ? 45 33" };
	inline const std::string GameRules{ "48 8B ? ? ? ? ? 4C 8B ? 48 8B ? 48 8B ? FF 90 ? ? ? ? 0F B6" };
	inline const std::string Prediction{ "48 8B ? ? ? ? ? B2 ? F3 0F ? ? ? ? 89 6C" };
	inline const std::string CCSGoInput{ "4C 89 ? ? ? ? ? 0F 11 ? ? ? ? ? 48 89 ? ? ? ? ? 4C 89" }; // Dereference 2 times
	inline const std::string BoneMatrix{ "4D 8B ? ? ? ? ? 4D 8B ? ? ? ? ? 8B 9F" };
}
