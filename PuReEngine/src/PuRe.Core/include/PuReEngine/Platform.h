#ifndef _PLATFORM_H_
#define _PLATFORM_H_
#ifdef _WIN32 //Win32 and Win64
#define _WINSOCKAPI_
#include <Windows.h>
#include "PlatformWin.h"
#include "WindowWin.h"

/// @brief declare Main Function
///
#ifdef _DEBUG
#define PURE_MAIN main()
#else
#define PURE_MAIN __stdcall WinMain(HINSTANCE,HINSTANCE,LPSTR,int)
#endif

/// @brief Creates Plattform specific Platform Interface
///
PuReEngine::Core::IPlatform* PuRe_CreatePlatform()
{
    return new PuReEngine::Core::CPlatformWin();
}
#elif __linux__
#include <X11/Xlib.h>
#include "PlatformLinux.h"
#include "WindowLinux.h"

/// @brief declare Main Function
///
#define PURE_MAIN main()

/// @brief Creates Plattform specific Platform Interface
///
PuReEngine::Core::IPlatform* PuRe_CreatePlatform()
{
    return new PuReEngine::Core::CPlatformLinux();
}

#else
#error "Unsupported Platform!"

#endif

#endif /* _PLATFORM_H_ */