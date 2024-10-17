#pragma once
#include <cstddef>
#include <vector>
#include "offsets.h"
#include "Vector.h"
#include "Windows.h"

namespace Address
{
	float* GetViewMatrixPtr();
	int* GetMatchStateIdPtr();
	Vector3* GetViewAnglesPtr();
	intptr_t GetPredictionBase();
	intptr_t GetLocalPlayerControl();
	intptr_t* GetDeathMatchRulesPtr();
	intptr_t GetEntityList();
	intptr_t GetEntityBase(intptr_t pIndex);

	template<typename T>
	T ReadInternalMem(intptr_t pBaseAddr, std::vector<intptr_t> pListOffset)
	{
		if ((!pBaseAddr || pListOffset.empty()))
			return T();

		intptr_t addrBuffer{ pBaseAddr };
		T addrResult{};

		for (const auto& currOffset : pListOffset)
		{
			if (!currOffset) return T();

			if (IsBadReadPtr((void*)(addrBuffer + currOffset), sizeof(T)))
				return NULL;

			addrBuffer = *reinterpret_cast<intptr_t*>(addrBuffer + currOffset);
			addrResult = static_cast<T>(addrBuffer);
		}

		return addrResult;
	}

	template<typename T>
	T RAM(intptr_t addr)
	{
		T Buffer = T();
		__try {

			if ((addr < 0x1000000 - 0x8) || (addr > 0x7FFFFFF00000 - 0x8)) {
				return Buffer;
			}
			if (IsBadReadPtr(PVOID(addr), sizeof(T)) == 0) {
				Buffer = *reinterpret_cast<T*>(addr);
			}
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {

		}
		return Buffer;
	}

	template <typename T>
	bool ReadMemory(intptr_t Address, T& Value, int Size)
	{
		HANDLE pro = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetCurrentProcessId());
		if (ReadProcessMemory(pro, reinterpret_cast<LPCVOID>(Address), &Value, Size, 0))
		{
			CloseHandle(pro);
			return true;
		}
		return false;
	}
}
