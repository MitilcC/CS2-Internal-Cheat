#include "Search.h"

/*

intptr_t PatternScan::GetPatternSize(const std::string& pPattern)
{
	if (pPattern.empty()) return NULL;

	int patternSize{ 0 };
	bool bWildCard{ false };

	for (int i{ 0 }; i < pPattern.length(); ++i)
	{
		if (pPattern[i] == '?')
		{
			bWildCard = true;
			continue;
		}
		else if (bWildCard && pPattern[i] == ' ')
		{
			++patternSize;
			bWildCard = false;
		}
		else if (pPattern[i] != ' ')
		{
			++patternSize;
		}
	}

	return patternSize;
}

std::vector<char> PatternScan::GetParsedPattern(const std::string& pPattern)
{
	if (pPattern.empty())
		return std::vector<char>();

	std::vector<char> parsedPattern{};

	for (int i{ 0 }; i < pPattern.length(); i += 3)
	{
		if (pPattern[i] != ' ')
		{
			const std::string patternSub{ pPattern.substr(i, 2) };

			// Deal with any wildcard type
			if (patternSub == "??")
			{
				parsedPattern.push_back('?');
				continue;
			}
			else if (patternSub == "? ")
			{
				parsedPattern.push_back('?');
				--i; // WildCard is only 1 byte so we have to inc by 2
				continue;
			}

			// Convert the substring into an hex byte
			const char hexByte{ static_cast<char>(std::strtol(patternSub.c_str(), 0, 16)) };

			if (!hexByte)
				return std::vector<char>();

			parsedPattern.push_back(hexByte);
		}
	}

	return parsedPattern;
}

intptr_t PatternScan::GetPatternAddr(char* pRegionAddr, intptr_t pRegionSize, const std::string& pPattern)
{
	// Remove the spaces and formate the pattern into hex byte
	std::vector<char> sPattern{ GetParsedPattern(pPattern) };

	if (sPattern.empty())
		return NULL;

	// Only iterate over the bytes that could potentially be the start of the pattern
	const uintptr_t regionSize{ pRegionSize - (sPattern.size()) };

	for (uintptr_t i{ 0 }; i < regionSize; ++i)
	{
		bool bFound{ true };

		for (uintptr_t j{ 0 }; j < sPattern.size(); ++j)
		{
			if (sPattern[j] != '?' && sPattern[j] != pRegionAddr[i + j])
			{
				bFound = false;
				break;
			}
		}

		if (bFound)
			return reinterpret_cast<intptr_t>(pRegionAddr) + i;
	}

	return 0;
}

intptr_t PatternScan::GetValidMemRegion(LDR_DATA_TABLE_ENTRY* pLdrEntry, const std::string& pPattern)
{
	if (!pLdrEntry || pPattern.empty())
		return 0;

	MEMORY_BASIC_INFORMATION mbi{};

	char* modBaseAddr{ reinterpret_cast<char*>(pLdrEntry->DllBase) };
	const intptr_t modSize{ pLdrEntry->SizeOfImage };

	for (char* currRegion{ modBaseAddr }; currRegion < modBaseAddr + modSize; currRegion += mbi.RegionSize)
	{
		if (!VirtualQuery(currRegion, &mbi, sizeof(mbi)) || mbi.Protect == PAGE_NOACCESS || mbi.State != MEM_COMMIT)
			continue;

		const intptr_t patternRes{ GetPatternAddr(currRegion, mbi.RegionSize, pPattern) };

		if (patternRes) return patternRes;
	}

	MessageBoxA(0, pPattern.c_str(), 0, 0);
	return 0;
}

intptr_t PatternScan::ExtractPointer(intptr_t pPatternResult)
{
	intptr_t resultPointer{};

	constexpr int opcodeSize{ 3 };
	const int32_t offset{ *reinterpret_cast<int32_t*>(pPatternResult + opcodeSize) };

	constexpr int instructionSize{ 7 };
	resultPointer = pPatternResult + static_cast<intptr_t>(offset) + instructionSize;

	return resultPointer;
}

void PatternScan::SetGameEntitySystem(LDR_DATA_TABLE_ENTRY* pLdrEntry, const std::string& pPattern)
{
	Offset::GPointers::EntityList =  cs2_dumper::offsets::client_dll::dwGameEntitySystem;
	pointersState["GameEntitySystem"] = Offset::GPointers::EntityList;
}

void PatternScan::SetGameRules(LDR_DATA_TABLE_ENTRY* pLdrEntry, const std::string& pPattern)
{

	Offset::GPointers::GameRules =  cs2_dumper::offsets::client_dll::dwGameRules;

	pointersState["GameRules"] = Offset::GPointers::GameRules;
}

void PatternScan::SetLpController(LDR_DATA_TABLE_ENTRY* pLdrEntry, const std::string& pPattern)
{
	Offset::GPointers::LP_Controller =  cs2_dumper::offsets::client_dll::dwLocalPlayerController;
	pointersState["LP_Controller"] = Offset::GPointers::LP_Controller;
}

void PatternScan::SetViewMatrix(LDR_DATA_TABLE_ENTRY* pLdrEntry, const std::string& pPattern)
{

	Offset::GPointers::ViewMatrix =  cs2_dumper::offsets::client_dll::dwViewMatrix;

	pointersState["ViewMatrix"] = Offset::GPointers::ViewMatrix;
}

void PatternScan::SetViewAngles(LDR_DATA_TABLE_ENTRY* pLdrEntry, const std::string& pPattern)
{

	Offset::GPointers::ViewAngles =  cs2_dumper::offsets::client_dll::dwViewAngles;

	pointersState["ViewAngles"] = Offset::GPointers::ViewAngles;
}

void PatternScan::SetPrediction(LDR_DATA_TABLE_ENTRY* pLdrEntry, const std::string& pPattern)
{

	Offset::GPointers::Prediction =  cs2_dumper::offsets::client_dll::dwPrediction;

	pointersState["Prediction"] = Offset::GPointers::Prediction;
}

void PatternScan::SetClientMod(PVOID pDllBase)
{
	Offset::GPointers::ClientMod = reinterpret_cast<intptr_t>(pDllBase);
	pointersState["ClientDLL"] = Offset::GPointers::ClientMod;
}

void PatternScan::SetEngine2Mod(PVOID pDllBase)
{
	Offset::GPointers::Engine2Mod = reinterpret_cast<intptr_t>(pDllBase);
	pointersState["Engine2"] = Offset::GPointers::Engine2Mod;
}

bool PatternScan::InitPointers()
{
	LDR_DATA_TABLE_ENTRY* clientLdr{ GetLdrEntry(L"client.dll") };
	LDR_DATA_TABLE_ENTRY* engine2Ldr{ GetLdrEntry(L"engine2.dll") };

	SetClientMod(clientLdr->DllBase);
	SetEngine2Mod(engine2Ldr->DllBase);

	SetGameRules(clientLdr, Pattern::GameRules);
	SetGameEntitySystem(clientLdr, Pattern::EntityList);
	SetLpController(clientLdr, Pattern::LP_Controller);
	SetViewMatrix(clientLdr, Pattern::ViewMatrix);
	SetPrediction(clientLdr, Pattern::Prediction);
	SetViewAngles(engine2Ldr, Pattern::CCSGoInput);

	return ArePointersInit();

}

bool PatternScan::ArePointersInit()
{
	for (const auto& pointer : pointersState)
	{
		if (!pointer.second) return false;
	}

	return true;
}

std::map<std::string_view, intptr_t> PatternScan::GetPtrState()
{
	return pointersState;
}

PEB* PatternScan::GetPEB()
{
	return (PEB*)__readgsqword(0x60);
}

LDR_DATA_TABLE_ENTRY* PatternScan::GetLdrEntry(const wchar_t* pModName)
{
	PEB* peb{ GetPEB() };

	LIST_ENTRY headList{ peb->Ldr->InMemoryOrderModuleList };
	LIST_ENTRY currList{ headList };

	while (currList.Flink != headList.Blink)
	{
		LDR_DATA_TABLE_ENTRY* currLdrEntry{ CONTAINING_RECORD(currList.Flink, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks) };

		if (currLdrEntry->FullDllName.Buffer)
		{
			wchar_t* wNameBuffer{ currLdrEntry->BaseDllName.Buffer };

			// Equal
			if (wcscmp(wNameBuffer, pModName) == 0)
				return currLdrEntry;
		}
		currList = *currList.Flink;
	}

	return nullptr;
}

*/

intptr_t PatternScan::GetPatternSize(const std::string& pPattern)
{
	if (pPattern.empty()) return NULL;

	int patternSize{ 0 };
	bool bWildCard{ false };

	for (int i{ 0 }; i < pPattern.length(); ++i)
	{
		if (pPattern[i] == '?')
		{
			bWildCard = true;
			continue;
		}
		else if (bWildCard && pPattern[i] == ' ')
		{
			++patternSize;
			bWildCard = false;
		}
		else if (pPattern[i] != ' ')
		{
			++patternSize;
		}
	}

	return patternSize;
}

std::vector<char> PatternScan::GetParsedPattern(const std::string& pPattern)
{
	if (pPattern.empty())
		return std::vector<char>();

	std::vector<char> parsedPattern{};

	for (int i{ 0 }; i < pPattern.length(); i += 3)
	{
		if (pPattern[i] != ' ')
		{
			const std::string patternSub{ pPattern.substr(i, 2) };

			// Deal with any wildcard type
			if (patternSub == "??")
			{
				parsedPattern.push_back('?');
				continue;
			}
			else if (patternSub == "? ")
			{
				parsedPattern.push_back('?');
				--i; // WildCard is only 1 byte so we have to inc by 2
				continue;
			}

			// Convert the substring into an hex byte
			const char hexByte{ static_cast<char>(std::strtol(patternSub.c_str(), 0, 16)) };

			if (!hexByte)
				return std::vector<char>();

			parsedPattern.push_back(hexByte);
		}
	}

	return parsedPattern;
}

intptr_t PatternScan::GetPatternAddr(char* pRegionAddr, intptr_t pRegionSize, const std::string& pPattern)
{
	// Remove the spaces and formate the pattern into hex byte
	std::vector<char> sPattern{ GetParsedPattern(pPattern) };

	if (sPattern.empty())
		return NULL;

	// Only iterate over the bytes that could potentially be the start of the pattern
	const uintptr_t regionSize{ pRegionSize - (sPattern.size()) };

	for (uintptr_t i{ 0 }; i < regionSize; ++i)
	{
		bool bFound{ true };

		for (uintptr_t j{ 0 }; j < sPattern.size(); ++j)
		{
			if (sPattern[j] != '?' && sPattern[j] != pRegionAddr[i + j])
			{
				bFound = false;
				break;
			}
		}

		if (bFound)
			return reinterpret_cast<intptr_t>(pRegionAddr) + i;
	}

	return 0;
}

intptr_t PatternScan::GetValidMemRegion(LDR_DATA_TABLE_ENTRY* pLdrEntry, const std::string& pPattern)
{
	if (!pLdrEntry || pPattern.empty())
		return 0;

	MEMORY_BASIC_INFORMATION mbi{};

	char* modBaseAddr{ reinterpret_cast<char*>(pLdrEntry->DllBase) };
	const intptr_t modSize{ pLdrEntry->SizeOfImage };

	for (char* currRegion{ modBaseAddr }; currRegion < modBaseAddr + modSize; currRegion += mbi.RegionSize)
	{
		if (!VirtualQuery(currRegion, &mbi, sizeof(mbi)) || mbi.Protect == PAGE_NOACCESS || mbi.State != MEM_COMMIT)
			continue;

		const intptr_t patternRes{ GetPatternAddr(currRegion, mbi.RegionSize, pPattern) };

		if (patternRes) return patternRes;
	}

	MessageBoxA(0, pPattern.c_str(), 0, 0);
	return 0;
}

intptr_t PatternScan::ExtractPointer(intptr_t pPatternResult)
{
	intptr_t resultPointer{};

	constexpr int opcodeSize{ 3 };
	const int32_t offset{ *reinterpret_cast<int32_t*>(pPatternResult + opcodeSize) };

	constexpr int instructionSize{ 7 };
	resultPointer = pPatternResult + static_cast<intptr_t>(offset) + instructionSize;

	return resultPointer;
}

void PatternScan::SetGameEntitySystem(LDR_DATA_TABLE_ENTRY* pLdrEntry, const std::string& pPattern)
{
	intptr_t resultPointer{};

	// Get the address of the pattern result
	const intptr_t patternAddr{ GetValidMemRegion(pLdrEntry, pPattern) };

	if (patternAddr)
		resultPointer = ExtractPointer(patternAddr);

	Offset::GPointers::EntityList = resultPointer - reinterpret_cast<intptr_t>(pLdrEntry->DllBase);

	std::cout << "GameEntitySystem : " << resultPointer - reinterpret_cast<intptr_t>(pLdrEntry->DllBase) << '\n';

	pointersState["GameEntitySystem"] = resultPointer;
}

void PatternScan::SetGameRules(LDR_DATA_TABLE_ENTRY* pLdrEntry, const std::string& pPattern)
{
	intptr_t resultPointer{};

	// Get the address of the pattern result
	const intptr_t patternAddr{ GetValidMemRegion(pLdrEntry, pPattern) };

	if (patternAddr)
		resultPointer = ExtractPointer(patternAddr);

	Offset::GPointers::GameRules = resultPointer - reinterpret_cast<intptr_t>(pLdrEntry->DllBase);

	std::cout << "GameRules : " << resultPointer - reinterpret_cast<intptr_t>(pLdrEntry->DllBase) << '\n';

	pointersState["GameRules"] = resultPointer;
}

void PatternScan::SetLpController(LDR_DATA_TABLE_ENTRY* pLdrEntry, const std::string& pPattern)
{
	intptr_t resultPointer{};

	// Get the address of the pattern result
	const intptr_t patternAddr{ GetValidMemRegion(pLdrEntry, pPattern) };

	if (patternAddr)
		resultPointer = ExtractPointer(patternAddr);

	Offset::GPointers::LP_Controller = resultPointer - reinterpret_cast<intptr_t>(pLdrEntry->DllBase);

	std::cout << "LP_Controller : " << resultPointer - reinterpret_cast<intptr_t>(pLdrEntry->DllBase) << '\n';

	pointersState["LP_Controller"] = resultPointer;
}

void PatternScan::SetViewMatrix(LDR_DATA_TABLE_ENTRY* pLdrEntry, const std::string& pPattern)
{
	intptr_t resultPointer{};

	// Get the address of the pattern result
	const intptr_t patternAddr{ GetValidMemRegion(pLdrEntry, pPattern) };

	if (patternAddr)
		resultPointer = ExtractPointer(patternAddr);

	// Storing the offset of the pointer
	Offset::GPointers::ViewMatrix = resultPointer - reinterpret_cast<intptr_t>(pLdrEntry->DllBase);

	std::cout << "ViewMatrix : " << resultPointer - reinterpret_cast<intptr_t>(pLdrEntry->DllBase) << '\n';

	pointersState["ViewMatrix"] = resultPointer;
}

void PatternScan::SetViewAngles(LDR_DATA_TABLE_ENTRY* pLdrEntry, const std::string& pPattern)
{

	intptr_t* resultPointer{ nullptr };
	/*
		// Get the address of the pattern result
	const intptr_t patternAddr{ GetValidMemRegion(pLdrEntry, pPattern) };

	if (patternAddr)
	{
		resultPointer = reinterpret_cast<intptr_t*>(ExtractPointer(patternAddr));

		// Dereference the pointer 2 times to access CCSGO_Input Base address
		for (int i{ 0 }; i < 2; ++i)
			resultPointer = reinterpret_cast<intptr_t*>(*resultPointer);

		// Storing the offset of the pointer
		const intptr_t CCSGO_InputOffset = reinterpret_cast<intptr_t>(resultPointer) - Offset::GPointers::ClientMod;
		Offset::GPointers::ViewAngles = CCSGO_InputOffset - Offset::CCSGO_Input::ViewAngles;
	}
	*/

	Offset::GPointers::ViewAngles = cs2_dumper::offsets::client_dll::dwViewAngles;

	std::cout << "ViewAngles : " << Offset::GPointers::ViewAngles << '\n';

	pointersState["ViewAngles"] = Offset::GPointers::ViewAngles;
}

void PatternScan::SetPrediction(LDR_DATA_TABLE_ENTRY* pLdrEntry, const std::string& pPattern)
{
	intptr_t resultPointer{};

	// Get the address of the pattern result
	const intptr_t patternAddr{ GetValidMemRegion(pLdrEntry, pPattern) };

	if (patternAddr)
		resultPointer = ExtractPointer(patternAddr);

	// Storing the offset of the pointer 
	Offset::GPointers::Prediction = resultPointer - reinterpret_cast<intptr_t>(pLdrEntry->DllBase);

	std::cout << "Prediction : " << resultPointer - reinterpret_cast<intptr_t>(pLdrEntry->DllBase) << '\n';

	pointersState["Prediction"] = resultPointer;
}

void PatternScan::SetClientMod(PVOID pDllBase)
{
	Offset::GPointers::ClientMod = reinterpret_cast<intptr_t>(pDllBase);
	pointersState["ClientDLL"] = Offset::GPointers::ClientMod;
}

void PatternScan::SetEngine2Mod(PVOID pDllBase)
{
	Offset::GPointers::Engine2Mod = reinterpret_cast<intptr_t>(pDllBase);
	pointersState["Engine2"] = Offset::GPointers::Engine2Mod;
}

bool PatternScan::InitPointers()
{
	LDR_DATA_TABLE_ENTRY* clientLdr{ GetLdrEntry(L"client.dll") };
	LDR_DATA_TABLE_ENTRY* engine2Ldr{ GetLdrEntry(L"engine2.dll") };

	SetClientMod(clientLdr->DllBase);
	SetEngine2Mod(engine2Ldr->DllBase);

	SetGameRules(clientLdr, Pattern::GameRules);
	SetGameEntitySystem(clientLdr, Pattern::EntityList);
	SetLpController(clientLdr, Pattern::LP_Controller);
	SetViewMatrix(clientLdr, Pattern::ViewMatrix);
	SetPrediction(clientLdr, Pattern::Prediction);
	SetViewAngles(engine2Ldr, Pattern::CCSGoInput);

	return ArePointersInit();

}

bool PatternScan::ArePointersInit()
{
	for (const auto& pointer : pointersState)
	{
		if (!pointer.second) return false;
	}

	return true;
}

std::map<std::string_view, intptr_t> PatternScan::GetPtrState()
{
	return pointersState;
}

PEB* PatternScan::GetPEB()
{
	return (PEB*)__readgsqword(0x60);
}

LDR_DATA_TABLE_ENTRY* PatternScan::GetLdrEntry(const wchar_t* pModName)
{
	PEB* peb{ GetPEB() };

	LIST_ENTRY headList{ peb->Ldr->InMemoryOrderModuleList };
	LIST_ENTRY currList{ headList };

	while (currList.Flink != headList.Blink)
	{
		LDR_DATA_TABLE_ENTRY* currLdrEntry{ CONTAINING_RECORD(currList.Flink, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks) };

		if (currLdrEntry->FullDllName.Buffer)
		{
			wchar_t* wNameBuffer{ currLdrEntry->BaseDllName.Buffer };

			// Equal
			if (wcscmp(wNameBuffer, pModName) == 0)
				return currLdrEntry;
		}
		currList = *currList.Flink;
	}

	return nullptr;
}