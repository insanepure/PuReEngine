#include "include/Menu.h"

namespace Game
{
    CMenu::CMenu(PuRe_Font* a_pFont, PuRe_Camera*a_pGuiCamera) : m_pFont(a_pFont), m_pGuiCamera(a_pGuiCamera)
    {

    }
    CMenu::~CMenu()
    {
        SAFE_DELETE(this->m_pFont);
        SAFE_DELETE(this->m_pGuiCamera);
    }
    void CMenu::Update(PuRe_IInput* a_pInput, CNetworkHandler* a_pNetworkHandler)
    {
        switch (m_Menu)
        {
        case 0:
            if (a_pInput->KeyPressed(a_pInput->Space))
                this->m_Menu = 2;
            else if (a_pInput->KeyPressed(a_pInput->Enter) || a_pInput->GamepadPressed(a_pInput->Pad_Start,0))
                this->m_Menu = 1;
            break;
        case 1: case 4:
            if (a_pInput->KeyPressed(a_pInput->Zero) && this->m_Port.length() < 6)
                this->m_Port += "0";
            else if (a_pInput->KeyPressed(a_pInput->One) && this->m_Port.length() < 6)
                this->m_Port += "1";
            else if (a_pInput->KeyPressed(a_pInput->Two) && this->m_Port.length() < 6)
                this->m_Port += "2";
            else if (a_pInput->KeyPressed(a_pInput->Three) && this->m_Port.length() < 6)
                this->m_Port += "3";
            else if (a_pInput->KeyPressed(a_pInput->Four) && this->m_Port.length() < 6)
                this->m_Port += "4";
            else if (a_pInput->KeyPressed(a_pInput->Five) && this->m_Port.length() < 6)
                this->m_Port += "5";
            else if (a_pInput->KeyPressed(a_pInput->Six) && this->m_Port.length() < 6)
                this->m_Port += "6";
            else if (a_pInput->KeyPressed(a_pInput->Seven) && this->m_Port.length() < 6)
                this->m_Port += "7";
            else if (a_pInput->KeyPressed(a_pInput->Eight) && this->m_Port.length() < 6)
                this->m_Port += "8";
            else if (a_pInput->KeyPressed(a_pInput->Nine) && this->m_Port.length() < 6)
                this->m_Port += "9";
            else if (a_pInput->KeyPressed(a_pInput->Backspace) && this->m_Port.length() != 0)
                this->m_Port = this->m_Port.substr(0, this->m_Port.length() - 1);
            else if (a_pInput->KeyPressed(a_pInput->Enter) && this->m_Port.length() > 3)
            {
                if (m_Menu == 1)
                {
                    this->m_Menu = 3;
                    a_pNetworkHandler ->Set(this->m_Port,"localhost",true); //Server
                }
                else
                {
                    this->m_Menu = 5;
                    a_pNetworkHandler->Set(this->m_Port, this->m_IP, false); //Client
                }
            }
            break;
        case 2:
            if (a_pInput->KeyPressed(a_pInput->Zero) && this->m_IP.length() < 20)
                this->m_IP += "0";
            else if (a_pInput->KeyPressed(a_pInput->One) && this->m_IP.length() < 20)
                this->m_IP += "1";
            else if (a_pInput->KeyPressed(a_pInput->Two) && this->m_IP.length() < 20)
                this->m_IP += "2";
            else if (a_pInput->KeyPressed(a_pInput->Three) && this->m_IP.length() < 20)
                this->m_IP += "3";
            else if (a_pInput->KeyPressed(a_pInput->Four) && this->m_IP.length() < 20)
                this->m_IP += "4";
            else if (a_pInput->KeyPressed(a_pInput->Five) && this->m_IP.length() < 20)
                this->m_IP += "5";
            else if (a_pInput->KeyPressed(a_pInput->Six) && this->m_IP.length() < 20)
                this->m_IP += "6";
            else if (a_pInput->KeyPressed(a_pInput->Seven) && this->m_IP.length() < 20)
                this->m_IP += "7";
            else if (a_pInput->KeyPressed(a_pInput->Eight) && this->m_IP.length() < 20)
                this->m_IP += "8";
            else if (a_pInput->KeyPressed(a_pInput->Nine) && this->m_IP.length() < 20)
                this->m_IP += "9";
            else if (a_pInput->KeyPressed(a_pInput->Period) && this->m_IP.length() < 20)
                this->m_IP += ".";
            else if (a_pInput->KeyPressed(a_pInput->Backspace) && this->m_IP.length() != 0)
                this->m_IP = this->m_IP.substr(0, this->m_IP.length() - 1);
            else if (a_pInput->KeyPressed(a_pInput->Enter) && this->m_IP.length() > 8)
                this->m_Menu = 4;
            break;
        }
    }
    void CMenu::Display(PuRe_Vector2F Resolution)
    {
        std::string text;
        switch (m_Menu)
        {
        case 0:
            this->m_pFont->Draw(this->m_pGuiCamera, "Press Enter to Host!", PuRe_Vector3F(16.0f, Resolution.Y - 32.0f, 0.0f), PuRe_Vector3F(16.0f, 16.0f, 1.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f),16.0f);
            this->m_pFont->Draw(this->m_pGuiCamera, "Press Space to Join!", PuRe_Vector3F(16.0f, Resolution.Y - 96.0f, 0.0f), PuRe_Vector3F(16.0f, 16.0f, 1.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 16.0f);
            break;
        case 1:
            text = "Choose Port: " + m_Port;
            this->m_pFont->Draw(this->m_pGuiCamera, text.c_str(), PuRe_Vector3F(16.0f, Resolution.Y - 32.0f, 0.0f), PuRe_Vector3F(16.0f, 16.0f, 1.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 16.0f);
            break;
        case 2:
            text = "Type in IP of Host: " + m_IP;
            this->m_pFont->Draw(this->m_pGuiCamera, text.c_str(), PuRe_Vector3F(16.0f, Resolution.Y - 32.0f, 0.0f), PuRe_Vector3F(16.0f, 16.0f, 1.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 16.0f);
            break;
        case 3:
            this->m_pFont->Draw(this->m_pGuiCamera, "Waiting for Players", PuRe_Vector3F(16.0f, Resolution.Y - 32.0f, 0.0f), PuRe_Vector3F(16.0f, 16.0f, 1.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 16.0f);
            this->m_pFont->Draw(this->m_pGuiCamera, "Press Enter to Start!", PuRe_Vector3F(16.0f, Resolution.Y - 96.0f, 0.0f), PuRe_Vector3F(16.0f, 16.0f, 1.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 16.0f);
            break;
        case 4:
            text = "Type in Port of Host: " + m_Port;
            this->m_pFont->Draw(this->m_pGuiCamera, text.c_str(), PuRe_Vector3F(16.0f, Resolution.Y - 32.0f, 0.0f), PuRe_Vector3F(16.0f, 16.0f, 1.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 16.0f);
            break;
        case 5:
            this->m_pFont->Draw(this->m_pGuiCamera, "Connection found, Waiting to Start", PuRe_Vector3F(16.0f, Resolution.Y - 32.0f, 0.0f), PuRe_Vector3F(16.0f, 16.0f, 1.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 16.0f);
            break;
        case 6:
            text = "Round "+std::to_string(this->m_Round);
            this->m_pFont->Draw(this->m_pGuiCamera, text.c_str(), PuRe_Vector3F(16.0f, Resolution.Y - 32.0f, 0.0f), PuRe_Vector3F(16.0f, 16.0f, 1.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 16.0f);
            break;
        }
    }
}