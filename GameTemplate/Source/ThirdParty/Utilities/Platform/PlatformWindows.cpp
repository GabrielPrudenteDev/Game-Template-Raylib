#ifdef PLATFORM_WINDOWS
#include "Platform.h"
namespace WIN {
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
}
#endif // PLATFORM_WINDOWS

static WIN::HANDLE hConsole;
static int defaultAttributes;

FPlatform::FPlatform()
{
	hConsole = WIN::GetStdHandle(((WIN::DWORD)-11));
	WIN::CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	WIN::GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	defaultAttributes = consoleInfo.wAttributes;
}

void FPlatform::SetConsoleTextAttribute(int attribute)
{
	if (!hConsole) {

		hConsole = WIN::GetStdHandle(((WIN::DWORD)-11));
		WIN::CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
		WIN::GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
		defaultAttributes = consoleInfo.wAttributes;
	}

	WIN::SetConsoleTextAttribute(hConsole, attribute);
}

void FPlatform::ResetConsoleDefaultAttributes()
{
	WIN::SetConsoleTextAttribute(hConsole, defaultAttributes);
}