#include "include/MainScene.h"
namespace Game
{

    CMainScene::CMainScene(PuRe_Application* a_pApplication)
    {
    }

    // **************************************************************************
    // **************************************************************************
    void CMainScene::Initialize(PuRe_IGraphics* a_pGraphics, PuRe_SoundPlayer* a_pSoundPlayer)
    {
        PuRe_GraphicsDescription gdesc = a_pGraphics->GetDescription();
        //Camera
        this->m_pCamera = new PuRe_Camera(PuRe_Vector2F((float32)gdesc.ResolutionWidth, (float32)gdesc.ResolutionHeight), PuRe_Camera_Perspective);
        this->m_pCamera->SetFoV(10.0f);
        this->m_pCamera->SetPosition(PuRe_Vector3F(1.67f, 0.58f, 0.0f));
        this->m_pCamera->Rotate(-50.0f, 22.0f, 0.0f);
        this->m_pCamera->Move(PuRe_Vector3F(0.0f, 0.0f, -1.0f));

        //materials
        this->m_pMaterial = a_pGraphics->LoadMaterial("../data/effects/default/default");
        this->m_pFontMaterial = a_pGraphics->LoadMaterial("../data/effects/font/default");


        this->m_pFont = new PuRe_Font(a_pGraphics, this->m_pMaterial, "../data/textures/font.png");

        this->m_pFireRope = new CFireRope(40, 1.0f, new PuRe_Sprite(a_pGraphics, this->m_pMaterial, "../data/textures/fire.png"));
        this->m_pGround = new CGround(new PuRe_Sprite(a_pGraphics, this->m_pMaterial, "../data/textures/dirt.png"));
        this->m_pModel = new PuRe_Model(a_pGraphics, this->m_pMaterial, "../data/models/squirtle/Squirtle.obj");
        this->m_ppPlayers = new CPlayer*[4];
        for (int32 i = 0; i < 4; i++)
            this->m_ppPlayers[i] = new CPlayer(this->m_pModel);

        PuRe_Camera* pGuiCamera = new PuRe_Camera(PuRe_Vector2F((float32)gdesc.ResolutionWidth, (float32)gdesc.ResolutionHeight), PuRe_Camera_Orthogonal);
        pGuiCamera->SetFoV(10.0f);
        this->m_pMenu = new CMenu(new PuRe_Font(a_pGraphics, this->m_pFontMaterial, "../data/textures/font.png"), pGuiCamera);

        this->m_pNetworkHandler = new CNetworkHandler(this->m_ppPlayers);

    }

    // **************************************************************************
    // **************************************************************************
    bool CMainScene::Update(PuRe_IGraphics* a_pGraphics, PuRe_IWindow* a_pWindow, PuRe_IInput* a_pInput, PuRe_Timer* a_pTimer, PuRe_SoundPlayer* a_pSoundPlayer)
    {
        //Handle ESC Button
        if (a_pInput->KeyPressed(a_pInput->ESC))
            return true;
        //Seconds for frame independent movement
        float32 Seconds = a_pTimer->GetElapsedSeconds();

        this->m_pMenu->Update(a_pInput, this->m_pNetworkHandler);

        if (this->m_pNetworkHandler->m_IsSet)
        {
            this->m_pNetworkHandler->HandleData(a_pInput);
        }
        if (this->m_pNetworkHandler->m_GameEnd)
        {
            this->m_pMenu->m_Menu = 0;
            this->m_pNetworkHandler->m_GameStarted = false;
            this->m_pNetworkHandler->m_GameEnd = false;
            for (int32 i = 0; i < 4; i++)
            {
                this->m_ppPlayers[i]->m_IsPlaying = false;
            }
        }
        else if (this->m_pNetworkHandler->m_GameStarted)
        {
            this->m_pMenu->m_Menu = 6;
            this->m_pMenu->m_Round = this->m_pNetworkHandler->m_Round;
            this->m_pNetworkHandler->m_Time += Seconds;
            this->m_pFireRope->Rotate(this->m_pNetworkHandler->m_Time);
            this->m_pFireRope->IncreaseSpeed(Seconds / 100.0f);
            for (int32 i = 0; i < 4; i++)
            {
                if (this->m_ppPlayers[i]->isHit()&&this->m_pFireRope->m_CanHit)
                    this->m_ppPlayers[i]->m_isDead = true;
            }
        }
        for (int32 i = 0; i < 4; i++)
            this->m_ppPlayers[i]->Update(Seconds);


        return false;
    }

    // **************************************************************************
    // **************************************************************************
    void CMainScene::Render(PuRe_IGraphics* a_pGraphics)
    {
        PuRe_Color clear = PuRe_Color(0.0f, 0.4f, 1.0f);
        PuRe_GraphicsDescription gdesc = a_pGraphics->GetDescription();

        a_pGraphics->Begin(clear);
        this->m_pGround->Draw(this->m_pCamera, PuRe_Vector3F(0.0f, -0.15f, 1.0f), PuRe_Vector3F(90.0f*0.0174532925f, 90.0f*0.0174532925f, 0.0f), PuRe_Vector3F(2.0f, 2.0f, 1.0f));

        if (this->m_pNetworkHandler->m_GameStarted)
        {
            this->m_pFireRope->Display(this->m_pCamera);
        }
        for (int32 i = 0; i < 4; i++)
        {
            this->m_ppPlayers[i]->Draw(this->m_pCamera, PuRe_Vector3F((0.1f*i) + 0.2f, -0.15f, 1.0f), PuRe_Vector3F(0.0f*0.0174532925f, -90.0f*0.0174532925f, 0.0f));
        }
        this->m_pMenu->Display(PuRe_Vector2F((float32)gdesc.ResolutionWidth, (float32)gdesc.ResolutionHeight));
        a_pGraphics->End();
    }

    // **************************************************************************
    // **************************************************************************
    void CMainScene::Exit()
    {
        for (int32 i = 0; i < 4; i++)
        {
            SAFE_DELETE(this->m_ppPlayers[i]);
        }
        SAFE_DELETE(this->m_pNetworkHandler);
        SAFE_DELETE(this->m_pFontMaterial);
        SAFE_DELETE(this->m_pMaterial);
        SAFE_DELETE(this->m_pModel);
        SAFE_DELETE(this->m_pGround);
        SAFE_DELETE(this->m_pFireRope);
        SAFE_DELETE(this->m_pMenu);
        SAFE_DELETE(this->m_pCamera);
    }
}
