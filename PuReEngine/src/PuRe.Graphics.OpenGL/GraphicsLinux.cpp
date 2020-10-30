#ifdef __linux__
#include "include/PuReEngine/OpenGL/GraphicsLinux.h"

namespace PuReEngine 
{
    namespace Graphics 
    {
        namespace OpenGL 
        {

            // **************************************************************************
            // **************************************************************************
            COSGraphics::COSGraphics(IWindow* a_pWindow, IPlatform* a_pPlatform, GraphicsDescription& a_rDescription)
            {
                static int attrListDbl[] =
                {
                    GLX_RGBA, GLX_DOUBLEBUFFER,
                    GLX_RED_SIZE, 4,
                    GLX_GREEN_SIZE, 4,
                    GLX_BLUE_SIZE, 4,
                    GLX_DEPTH_SIZE, 16,
                    None
                };
                this->m_pWindow = a_pWindow;
                this->m_pPlatform = a_pPlatform;
                this->m_Description = &a_rDescription;
                this->m_pDisplay = (Display*)a_pWindow->GetHandle();
                int32 focusstate = 0;

                //Get focus
                XGetInputFocus(this->m_pDisplay,&this->m_HWND,&focusstate);
                //get screen
                int screen = DefaultScreen(this->m_pDisplay);
                //get visual info based on attributes
                XVisualInfo* pvi = glXChooseVisual(this->m_pDisplay, screen, attrListDbl);
                //create context
                this->m_Context = glXCreateContext(this->m_pDisplay, pvi, 0, GL_TRUE);
                //append context to window
                glXMakeCurrent(this->m_pDisplay, this->m_HWND, this->m_Context);
                glXIsDirect(this->m_pDisplay, this->m_Context);
            }

            // **************************************************************************
            // **************************************************************************
            void COSGraphics::SwapBuffs()
            {
                glXSwapBuffers(this->m_pDisplay, this->m_HWND);
            }

            // **************************************************************************
            // **************************************************************************
            COSGraphics::~COSGraphics()
            {
                glXMakeCurrent(this->m_pDisplay, None, NULL);
                glXDestroyContext(this->m_pDisplay, this->m_Context);
            }
        }
    }
}
#endif
