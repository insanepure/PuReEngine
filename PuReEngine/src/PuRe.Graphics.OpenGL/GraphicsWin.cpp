#ifdef _WIN32
#include "include\PuReEngine\OpenGL\GraphicsWin.h"

namespace PuReEngine
{
    namespace Graphics
    {
        namespace OpenGL
        {

            // **************************************************************************
            // **************************************************************************
            COSGraphics::COSGraphics(IWindow* a_pWindow, IPlatform* a_pPlatform, SGraphicsDescription& a_rDescription)
            {
                this->m_HWND = (HWND)a_pWindow->GetHandle();
                this->m_pWindow = a_pWindow;
                this->m_pPlatform = a_pPlatform;
                this->m_pDescription = &a_rDescription;
                PIXELFORMATDESCRIPTOR pfd;
                int format;

                //Get Device
                this->m_HDC = GetDC(this->m_HWND);

                //set Pixelformat description
                ZeroMemory(&pfd, sizeof(pfd));
                pfd.nSize = sizeof(pfd);
                pfd.nVersion = 1;
                pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
                pfd.iPixelType = PFD_TYPE_RGBA;
                pfd.cColorBits = 24;
                pfd.cDepthBits = 16;
                pfd.iLayerType = PFD_MAIN_PLANE;

                //set Pixelformat
                format = ChoosePixelFormat(this->m_HDC, &pfd);
                SetPixelFormat(this->m_HDC, format, &pfd);

                //create rendercontext
                this->m_HRC = wglCreateContext(this->m_HDC);
                wglMakeCurrent(this->m_HDC, this->m_HRC);

            }

            // **************************************************************************
            // **************************************************************************
            void COSGraphics::SwapBuffs()
            {
                SwapBuffers(this->m_HDC);
            }

            // **************************************************************************
            // **************************************************************************
            COSGraphics::~COSGraphics()
            {
                wglMakeCurrent(NULL, NULL);
                wglDeleteContext(this->m_HRC);
                ReleaseDC(this->m_HWND, this->m_HDC);
            }
        }
    }
}
#endif