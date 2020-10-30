#include "include/PuReEngine/PlatformLinux.h"
#ifdef __linux__
namespace PuReEngine 
{
    namespace Core 
    {

        // **************************************************************************
        // **************************************************************************
        CPlatformLinux::CPlatformLinux()
        {
        }

        // **************************************************************************
        // **************************************************************************
        CPlatformLinux::~CPlatformLinux()
        {
        }

        // **************************************************************************
        // **************************************************************************
        ISignalHandler* CPlatformWin::PlatformCreateSignalHandler()
        {
            return new CSignalHandlerLinux();
        }

        // **************************************************************************
        // **************************************************************************
        IInput* CPlatformLinux::PlatformCreateInput()
        {
            return new CInputLinux();
        }

        // **************************************************************************
        // **************************************************************************
        IWindow* CPlatformLinux::PlatformCreateWindow(WindowDescription& a_rDescription)
        {
            return new WindowLinux(a_rDescription);
        }

        // **************************************************************************
        // **************************************************************************
        IGraphics* CPlatformLinux::PlatformCreateGraphics(IWindow* a_pWindow, GraphicsDescription& a_rDescription)
        {
            void* pmodule;
            IGraphics* pgraphics = 0;
            pmodule = dlopen("./modules/libPuRe.Graphics.OpenGL.so",RTLD_NOW);
            //DWORD lol = dlerror();
            CREATEGRAPHICS graphicscreation = (CREATEGRAPHICS)dlsym(pmodule, "CreateGraphics");
            //DWORD lol = dlerror();
            pgraphics = graphicscreation(a_pWindow, this, a_rDescription);
            pgraphics->Initialize();
            return pgraphics;
        }

        // **************************************************************************
        // **************************************************************************
        void CPlatformLinux::PlatformGraphicsSetPixel(void* a_pContext, int32 a_X, int32 a_Y, Color& a_rColor)
        {
        }

        // **************************************************************************
        // **************************************************************************
        void* CPlatformLinux::PlatformCreateWindowRenderContext(IWindow* a_pWindow)
        {
            return 0;
        }

        // **************************************************************************
        // **************************************************************************
        void CPlatformLinux::PlatformReleaseWindowRenderContext(IWindow* a_pWindow, void* a_pContext)
        {
        }

    }
}
#endif
