#pragma once
#include <cstdint>
#include "Address.h"

namespace GameState
{
	enum GameStateId
	{
		NO_STATE,
		IN_LOBBY = 4,
		IN_GAME = 8,
		UN_KNOWN = 16,
	};

	inline bool bDefaultChange{ false };
	bool IsDeathMatch();
	bool IsMatchStarted();
	int GetMatchState();
};