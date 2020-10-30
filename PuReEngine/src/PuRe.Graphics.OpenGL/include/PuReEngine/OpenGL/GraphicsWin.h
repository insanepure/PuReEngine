#ifdef _WIN32
#ifndef _GRAPHICSWIN_H_
#define _GRAPHICSWIN_H_
// Windows specific includes
#include <windows.h>                              
// OpenGL specific includes
#define GLEW_STATIC
#include <GL/glew.h>

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
            using ::PuReEngine::Core::SGraphicsDescription;

            class COSGraphics
            {
            private:
                /// @brief Pointer to the Window drawn on
                ///
                IWindow* m_pWindow;
                /// @brief Pointer to the Platform Interface
                ///
                IPlatform* m_pPlatform;
                /// @brief Window Handle
                ///
                HWND m_HWND;
                /// @brief GDI Device Context
                ///
                HDC m_HDC;
                /// @brief Rendering Context
                ///
                HGLRC m_HRC;
                /// @brief Graphics Description
                ///
                SGraphicsDescription* m_pDescription;
            public:
                /// @brief Initializes an Platform Graphic Object
                ///
                /// @param Pointer to the Window Interface
                /// @param Pointer to the Platform Interface
                /// @param Graphics Description
                ///
                COSGraphics(IWindow* a_pWindow, IPlatform* a_pPlatform, SGraphicsDescription& a_rDescription);

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
#endif /* _GRAPHICSWIN_H_ */
#endif
