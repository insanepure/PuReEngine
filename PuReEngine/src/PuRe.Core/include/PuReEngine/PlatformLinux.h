#ifdef __linux__
#ifndef _PLATFORMLINUX_H_
#define _PLATFORMLINUX_H_
// Platform specific includes
#include <X11/Xlib.h>
#include <dlfcn.h>


// Engine specific includes
#include "IPlatform.h"
#include "ISignalHandler.h"
#include "Color.h"
#include "WindowLinux.h"
#include "InputLinux.h"
#include "SignalHandlerLinux.h"
#include "Defines.h"

#include <iostream>

namespace PuReEngine 
{
    namespace Core 
    {

        class CPlatformLinux : public IPlatform
        {
        public:
            /// @brief Creates an instance of Platform.
            ///
            CPlatformLinux();
            /// @brief Destroyes the Instance of Platform
            ///
            ~CPlatformLinux();
        public:
            /// @brief Initializes a SignalHandler Instance
            ///
            /// @returns Pointer to an ISignalHandler Instance
            ///
            ISignalHandler* PlatformCreateSignalHandler();

            /// @brief Initializes a Input Instance
            ///
            /// @returns Pointer to an IInput Instance
            ///
            IInput* PlatformCreateInput();

            ///// @brief Initializes a Graphic Instance
            /////
            ///// @param A Window Instance
            ///// @param A Graphic Description
            /////
            ///// @returns The Graphic Instance
            /////
            IGraphics* PlatformCreateGraphics(IWindow* a_pWindow, GraphicsDescription& ar_Description);

            /// @brief Initializes a Window Instance
            ///
            /// @param A Window Description
            ///
            /// @returns The Window Instance
            ///
            IWindow* PlatformCreateWindow(WindowDescription& a_rDescription);

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
#endif /* _PLATFORMLINUX_H_ */
#endif
