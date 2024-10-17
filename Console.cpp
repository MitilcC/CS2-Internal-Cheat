#include "Console.h"

void Console::InitConsole()
{
	if (!file)
	{
		AllocConsole();
		freopen_s(&file, "CONOUT$", "w", stdout);
	}
}

void Console::DestroyConsole()
{
	if (file)
		fclose(file);

	FreeConsole();
}

void Console::PrintCheatOptions(const char* a)
{
	std::cout << a << '\n';
}

void Console::Clear()
{
	system("cls");
}