#include "include/PuReEngine/PlatformWin.h"
#ifdef _WIN32
namespace PuReEngine
{
    namespace Core
    {

        // **************************************************************************
        // **************************************************************************
        CPlatformWin::CPlatformWin()
        {
        }

        // **************************************************************************
        // **************************************************************************
        CPlatformWin::~CPlatformWin()
        {
        }

        // **************************************************************************
        // **************************************************************************
        ISignalHandler* CPlatformWin::PlatformCreateSignalHandler()
        {
            return new CSignalHandlerWin();
        }

        // **************************************************************************
        // **************************************************************************
        IInput* CPlatformWin::PlatformCreateInput(IWindow* a_pWindow)
        {
            return new CInputWin((HWND)a_pWindow->GetHandle());
        }

        // **************************************************************************
        // **************************************************************************
        IGraphics* CPlatformWin::PlatformCreateGraphics(IWindow* a_pWindow, SGraphicsDescription& a_rDescription)
        {
            HMODULE module;
            IGraphics* pgraphics = nullptr;

            switch (a_rDescription.Module)
            {
            case EGraphicsModuleType::Direct3D11:
                module = LoadLibrary(".\\Modules\\PuRe.Graphics.DirectX11.dll");
                break;
            case EGraphicsModuleType::OpenGL:
                module = LoadLibrary(".\\Modules\\PuRe.Graphics.OpenGL.dll");
                break;

            default:
                module = LoadLibrary(".\\Modules\\PuRe.Graphics.DirectX10.dll");
                break;
            }
            CREATEGRAPHICS graphicscreation = (CREATEGRAPHICS)GetProcAddress(module, "CreateGraphics");
            pgraphics = graphicscreation(a_pWindow, this, a_rDescription);
            pgraphics->Initialize();
            return pgraphics;
        }



        // **************************************************************************
        // **************************************************************************
        IWindow* CPlatformWin::PlatformCreateWindow(SWindowDescription& a_rDescription)
        {
            return new CWindowWin(a_rDescription);
        }

        // **************************************************************************
        // **************************************************************************
        void CPlatformWin::PlatformGraphicsSetPixel(void* a_pContext, int32 a_X, int32 a_Y, Color& a_rColor)
        {
            SetPixel((HDC)a_pContext, a_X, a_Y, RGB(a_rColor.R * 255.0f, a_rColor.G * 255.0f, a_rColor.B * 255.0f));
        }

        // **************************************************************************
        // **************************************************************************
        void* CPlatformWin::PlatformCreateWindowRenderContext(IWindow* a_pWindow)
        {
            return GetDC((HWND)a_pWindow->GetHandle());
        }

        // **************************************************************************
        // **************************************************************************
        void CPlatformWin::PlatformReleaseWindowRenderContext(IWindow* a_pWindow, void* a_pContext)
        {
            ReleaseDC((HWND)a_pWindow->GetHandle(), (HDC)a_pContext);
        }
    }
}
#endif
