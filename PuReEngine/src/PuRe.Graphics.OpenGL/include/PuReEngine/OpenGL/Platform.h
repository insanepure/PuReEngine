#pragma once

#ifdef _WIN32 //Win32 and Win64

#include "GraphicsWin.h"

#elif __linux__
#include "GraphicsLinux.h"
#else
#error "Unsupported Platform!"
#endif


using ::PuReEngine::Core::IWindow;
using ::PuReEngine::Core::IPlatform;
using ::PuReEngine::Core::SGraphicsDescription;
/// @brief Creates Plattform specific Graphic-Creation Interface
///
/// @param Pointer to the IWindow
/// @param Pointer to the IPLatform
/// @param Address of the Graphic Description
///
/// @returns Pointer to the Graphic Object
///
PuReEngine::Graphics::OpenGL::COSGraphics* CreateGraphic(IWindow* window, IPlatform* platform, SGraphicsDescription& description)
{
  return new PuReEngine::Graphics::OpenGL::COSGraphics(window, platform, description);
}
