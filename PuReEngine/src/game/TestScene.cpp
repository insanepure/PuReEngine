#include "include/TestScene.h"
namespace Game
{
     
    CTestScene::CTestScene(PuRe_Application*)
    {
    }

    // **************************************************************************
    // **************************************************************************
    void CTestScene::Initialize(PuRe_Application* a_pApplication)
    {
        PuRe_GraphicsDescription gdesc = a_pApplication->GetGraphics()->GetDescription();

    }

    // **************************************************************************
    // **************************************************************************
    int CTestScene::Update(PuRe_Application*)
    {
       
        return 1;
    }

    // **************************************************************************
    // **************************************************************************
    void CTestScene::Render(PuRe_Application* a_pApplication)
    {
        PuRe_Color PuRe_CLEAR = PuRe_Color(0.0f, 0.4f, 1.0f, 1.0f);

        PuRe_IGraphics* graphics = a_pApplication->GetGraphics();
        PuRe_BoundingBox viewport;
        viewport.m_Position = PuRe_Vector3F(0.0f,0.0f,0.0f);
        viewport.m_Size = PuRe_Vector3F(1024.0f, 768.0f, 0.0f);


        graphics->Clear(PuRe_Color(0.0f, 0.4f, 1.0f));
        graphics->Begin(viewport);


        graphics->End();


        ///////////////// END FINAL PASS ////////////////////
    }

    // **************************************************************************
    // **************************************************************************
    void CTestScene::Exit()
    {
      
    }
}
