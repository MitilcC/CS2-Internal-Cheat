#include "GameState.h"

bool GameState::IsDeathMatch()
{
	const intptr_t* deathMatchPtr{ Address::GetDeathMatchRulesPtr() };
	return deathMatchPtr ? true : false;
}

int GameState::GetMatchState()
{
	const int matchStateId{ *Address::GetMatchStateIdPtr() };

	return matchStateId;
}


bool GameState::IsMatchStarted()
{
	const int matchStateId{ *Address::GetMatchStateIdPtr() };

	//std::cout << matchStateId << '\n';

	switch (matchStateId)
	{
	case IN_GAME: return true;
	case IN_LOBBY: return false;
	case NO_STATE: return false;
	case UN_KNOWN: return true;
	case NOCONNECT: return false;
	default: return false;
	}

	return false;
}