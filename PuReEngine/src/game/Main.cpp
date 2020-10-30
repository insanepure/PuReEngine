#include <PuReEngine/Platform.h>
#include <PuReEngine/Core.h>
// Application specific includes
#include "include/TestScene.h"



int PURE_MAIN
{
    //Memory Leak detection
    static unsigned int breakId = 210;
    _CrtSetBreakAlloc(breakId);
    {
        PuRe_IPlatform* pplatform = PuRe_CreatePlatform();
        PuRe_ApplicationDescription description;
        description.Graphics.ResolutionWidth = 1920;
        description.Graphics.ResolutionHeight = 1080;
        description.Graphics.Module = PuRe_GraphicsModuleType::OpenGL;
        description.Window.Title = "PuReEngine - Development";
        description.Window.Width = 1024;
        description.Window.Height = 768;
        description.Window.X = 100;
        description.Window.Y = 100;
        description.Window.DisplaySetting = PuRe_DisplaySetting::Windowed;
        description.Window.ShowCursor = true;
        description.Window.LockCursor = false;
        description.Window.CursorInWindow = false;
        PuRe_Application* papplication = new PuRe_Application(pplatform, description);
        Game::CTestScene scene(papplication);

        papplication->Run(&scene);

        SAFE_DELETE(papplication);
        SAFE_DELETE(pplatform);
    }
    //Print memory leak in output
    _CrtDumpMemoryLeaks();
}