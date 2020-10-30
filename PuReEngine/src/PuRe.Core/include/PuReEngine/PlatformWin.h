#ifdef _WIN32
#ifndef _PLATFORMWIN_H_
#define _PLATFORMWIN_H_
// Platform specific includes
#include <Windows.h>
#include <iostream>

// Engine specific includes
#include "IPlatform.h"
#include "Color.h"
#include "WindowWin.h"
#include "InputWin.h"
#include "SignalHandlerWin.h"
#include "IGraphics.h"

// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {

        class CPlatformWin : public IPlatform
        {
        public:
            /// @brief Creates an instance of Platform.
            ///
            CPlatformWin();
            /// @brief Destroyes the Instance of Platform
            ///
            ~CPlatformWin();
        public:
            /// @brief Initializes a SignalHandler Instance
            ///
            /// @returns Pointer to an ISignalHandler Instance
            ///
            ISignalHandler* PlatformCreateSignalHandler();

            /// @brief Initializes a Input Instance
            ///
            /// @param A Window Instance
            ///
            /// @returns Pointer to an IInput Instance
            ///
            IInput* PlatformCreateInput(IWindow* a_pWindow);

            /// @brief Initializes a Graphic Instance
            ///
            /// @param A Window Instance
            /// @param A Graphic Description
            ///
            /// @returns The Graphic Instance
            ///
            IGraphics* PlatformCreateGraphics(IWindow* a_pWindow, SGraphicsDescription& a_rDescription);

            /// @brief Initializes a Window Instance
            ///
            /// @param A Window Description
            ///
            /// @returns The Window Instance
            ///
            IWindow* PlatformCreateWindow(SWindowDescription& a_rDescription);

            /// @brief Sets a Pixel in a Context
            ///
            /// @param The Context
            /// @param X Position in Screen Space
            /// @param Y Position in Screen Space
            /// @param Color of the Pixel
            ///
            void PlatformGraphicsSetPixel(void* a_pContext, int32 a_X, int32 a_Y, Color& a_rColor);

            /// @brief Returns a Window Renderer Context
            ///
            /// @param The Window
            ///
            /// @returns The Context
            ///
            void* PlatformCreateWindowRenderContext(IWindow* a_pWindow);

            /// @brief Releases a Window Renderer Context
            ///
            /// @param The Window
            /// @param The Context
            ///
            void PlatformReleaseWindowRenderContext(IWindow* a_pWindow, void* a_pContext);
        };

    }
}
#endif /* _PLATFORMWIN_H_ */
#endif
