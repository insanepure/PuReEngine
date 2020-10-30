#ifndef _IPLATFORM_H_
#define _IPLATFORM_H_

// Engine specific includes
#include "IWindow.h"
#include "IGraphics.h"
#include "IInput.h"
#include "ISignalHandler.h"
#include "WindowDescription.h"
#include "GraphicsDescription.h"
#include "Color.h"

// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {
        /// @brief Base interface for handling the plattform specifics
        ///
        struct IPlatform
        {
            /// @brief Destroyes an instance of IPlatform
            ///
            virtual ~IPlatform() {};
            /// @brief Initializes a SignalHandler Instance
            ///
            /// @returns Pointer to an ISignalHandler Instance
            ///
            virtual ISignalHandler* PlatformCreateSignalHandler() = 0;
            /// @brief Initializes a Input Instance
            ///
            /// @param A Window Instance
            ///
            /// @returns Pointer to an IInput Instance
            ///
            virtual IInput* PlatformCreateInput(IWindow* a_pWindow) = 0;

            /// @brief Initializes a Graphic Instance
            ///
            /// @param A Window Instance
            /// @param A Graphic Description
            ///
            /// @returns Pointer to an Graphic Instance
            ///
            virtual IGraphics* PlatformCreateGraphics(IWindow* a_pWindow, SGraphicsDescription& a_rDescription) = 0;

            /// @brief Initializes a Window Instance
            ///
            /// @param A Window Description
            ///
            /// @returns Pointer to an Window Instance
            ///
            virtual IWindow* PlatformCreateWindow(SWindowDescription& a_rDescription) = 0;

            /// @brief Sets a Pixel in a Context
            ///
            /// @param The Context
            /// @param X Position in Screen Space
            /// @param Y Position in Screen Space
            /// @param Color of the Pixel
            ///
            virtual void PlatformGraphicsSetPixel(void* a_pContext, int32 a_X, int32 a_Y, Color& a_rColor) = 0;

            /// @brief Returns a Window Renderer Context
            ///
            /// @param The Window
            ///
            /// @returns The Context
            ///
            virtual void* PlatformCreateWindowRenderContext(IWindow* a_pWindow) = 0;

            /// @brief Releases a Window Renderer Context
            ///
            /// @param The Window
            /// @param The Context
            ///
            virtual void PlatformReleaseWindowRenderContext(IWindow* a_pWindow, void* a_pContext) = 0;
        };

        /// @brief Typedef of IGraphics, which is loaded dynamically
        ///
        typedef IGraphics* (*CREATEGRAPHICS)(IWindow* a_pWindow, IPlatform* a_pPlatform, SGraphicsDescription& a_rDescription);

    }
}

#endif /* _IPLATFORM_H_ */