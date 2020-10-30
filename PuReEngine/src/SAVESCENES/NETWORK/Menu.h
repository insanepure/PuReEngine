#ifndef _MENU_H_
#define _MENU_H_

// Framework specific includes
#include <PuReEngine/Core.h>
#include <PuReEngine/Defines.h>

#include "NetworkHandler.h"


namespace Game
{
    class CMenu
    {
    public:
        /// @brief Port of the Host
        ///
        std::string m_Port;
        /// @brief IP of the Host
        ///
        std::string m_IP;
        /// @brief Font to Display Text
        ///
        PuRe_Font* m_pFont;
        /// @brief Camera to Use
        ///
        PuRe_Camera* m_pGuiCamera;
        /// @brief Where we are in our Menu
        ///
        int32 m_Menu;
        /// @brief Round we are in
        ///
        int32 m_Round;
    public:
        CMenu(PuRe_Font* a_pFont, PuRe_Camera*a_pGuiCamera);
        ~CMenu();
    public:
        void Update(PuRe_IInput* a_pInput, CNetworkHandler* a_pNetworkHandler);
        void Display(PuRe_Vector2F Resolution);

    };
}

#endif /* _MENU_H_ */