#pragma once

#include <Windows.h>
#include <iostream>
#include <map>
#include <vector>

namespace Console
{
    inline FILE* file{ nullptr };

    // Console info updates
    inline bool bLobbyStart{ true };
    inline bool bInGameStart{ true };
    inline bool bConsoleChanged{ true };

    void InitConsole();
    void DestroyConsole();
    void PrintCheatOptions(const char * a);
    void Clear();
};