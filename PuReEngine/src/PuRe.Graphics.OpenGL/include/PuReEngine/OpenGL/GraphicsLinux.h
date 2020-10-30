#ifdef __linux__
#ifndef _GRAPHICSLINUX_H_
#define _GRAPHICSLINUX_H_
// Linux Specific includes
#include <X11/Xlib.h>
#include <X11/extensions/xf86vmode.h>
// OpenGL specific includes
#include <GL/glew.h>
#include <GL/glx.h>

// PuReEngine::Core specific includes
#include "PuReEngine/IWindow.h"
#include "PuReEngine/IPlatform.h"
#include "PuReEngine/GraphicsDescription.h"


namespace PuReEngine 
{
    namespace Graphics 
    {
        namespace OpenGL 
        {

            using ::PuReEngine::Core::IWindow;
            using ::PuReEngine::Core::IPlatform;
            using ::PuReEngine::Core::IGraphics;
            using ::PuReEngine::Core::GraphicsDescription;

            class COSGraphics
            {

            private:
                /// @brief Pointer to the Window drawn on
                ///
                IWindow* m_pWindow;
                /// @brief Pointer to the Platform Interface
                ///
                IPlatform* m_pPlatform;
                /// @brief Graphics Description
                ///
                GraphicsDescription* m_pDescription;

                /// @brief The window handle.
                ///
                Window m_HWND;

                /// @brief The display handle;
                ///
                Display* m_pDisplay;
                /// @brief The GL Context;
                //
                GLXContext m_Xontext;
            public:
                /// @brief Initializes an Platform Graphic Object
                ///
                /// @param Pointer to the Window Interface
                /// @param Pointer to the Platform Interface
                /// @param Graphics Description        
                ///
                COSGraphics(IWindow* a_pWindow, IPlatform* a_pPlatform, GraphicsDescription& a_rDescription);

                /// @brief Destroyes Platform Graphic Object
                ///
                ~COSGraphics();
            public:
                /// @brief Swap Buffers
                ///
                void SwapBuffs();
            };

        }
    }
}
#endif /* _GRAPHICSLINUX_H_ */
#endif
