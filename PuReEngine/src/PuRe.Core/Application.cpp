#include "include/PuReEngine/Application.h"

namespace PuReEngine
{
    namespace Core
    {
        // **************************************************************************
        // **************************************************************************
        CApplication::CApplication(IPlatform* a_pm_pPlatform, SApplicationDescription& a_rDescription)
        {
            this->m_Quit = false;
            this->m_pDescription = &a_rDescription;
            this->m_pPlatform = a_pm_pPlatform;
        }

        // **************************************************************************
        // **************************************************************************
        void CApplication::Run(IScene* a_pScene)
        {
            this->m_pSignalHandler = this->m_pPlatform->PlatformCreateSignalHandler();
            // Create main Window
            this->m_pWindow = this->m_pPlatform->PlatformCreateWindow(this->m_pDescription->Window);
            this->m_pWindow->Show();

            // Create graphics module
            this->m_pGraphics = this->m_pPlatform->PlatformCreateGraphics(this->m_pWindow, this->m_pDescription->Graphics);

            // Create input module
            this->m_pInput = this->m_pPlatform->PlatformCreateInput(this->m_pWindow);
            //Set Cursor Lock
            if (this->m_pDescription->Window.LockCursor)
                this->m_pInput->LockCursor();
            else
                this->m_pInput->UnLockCursor();

            //start Time
            this->m_pTimer = new CTimer();

            //start Sound
            this->m_pSoundPlayer = new CSoundPlayer();

            a_pScene->Initialize(const_cast<CApplication*>(this));

            while (!this->m_Quit)
            {
                //Check if Window Settings have been changed
                this->m_pWindow->Update();
                //update Input
                this->m_pInput->Update();
                this->m_Quit = this->m_pInput->CheckQuit();
                if (!this->m_Quit)
                {
                    //Update Time
                    this->m_pTimer->Update();
                    //Update Sound
                    this->m_pSoundPlayer->Update();
                    //Run Update Script
                    this->m_Quit = a_pScene->Update(const_cast<CApplication*>(this)) == 0;
                    //Calculate FPS
                    this->m_pTimer->CalculateFPS();
                    if (!this->m_Quit)
                    {
                        //Run Render Script
                        a_pScene->Render(const_cast<CApplication*>(this));
                    }
                }
            }

            a_pScene->Exit();

            SAFE_DELETE(this->m_pSoundPlayer);
            SAFE_DELETE(this->m_pSignalHandler);
            SAFE_DELETE(this->m_pTimer);
            SAFE_DELETE(this->m_pInput);
            SAFE_DELETE(this->m_pGraphics);
            SAFE_DELETE(this->m_pWindow);

        }

        // **************************************************************************
        // **************************************************************************
        IInput* CApplication::GetInput()
        {
            return this->m_pInput;
        }

        // **************************************************************************
        // **************************************************************************
        CSoundPlayer* CApplication::GetSoundPlayer()
        {
            return this->m_pSoundPlayer;
        }

        // **************************************************************************
        // **************************************************************************
        CTimer* CApplication::GetTimer()
        {
            return this->m_pTimer;
        }

        // **************************************************************************
        // **************************************************************************
        IWindow* CApplication::GetWindow()
        {
            return this->m_pWindow;
        }

        // **************************************************************************
        // **************************************************************************
        IGraphics* CApplication::GetGraphics()
        {
            return this->m_pGraphics;
        }

        // **************************************************************************
        // **************************************************************************
        IPlatform* CApplication::GetPlatform()
        {
            return this->m_pPlatform;
        }

    }
}
