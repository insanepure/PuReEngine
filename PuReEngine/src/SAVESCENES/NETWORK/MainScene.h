#ifndef _MAINSCENE_H_
#define _MAINSCENE_H_


// Framework specific includes
#include <PuReEngine/Core.h>
#include <PuReEngine/Defines.h>
#include <thread>

// Game specific includes
#include "FireRope.h"
#include "Ground.h"
#include "Player.h"
#include "Menu.h"
#include "NetworkHandler.h"

// Declare namespace Game
namespace Game
{
    /// @brief MainScene where the game functions are in, inherits from the Scene interface
    ///
    class CMainScene : public PuRe_IScene
    {
    private:
        /// @brief FontMaterial
        ///
        PuRe_IMaterial* m_pFontMaterial;
        /// @brief Default Material
        ///
        PuRe_IMaterial* m_pMaterial;
        /// @brief PlayerModel
        ///
        PuRe_Model* m_pModel;
        /// @brief Handler to handle Network
        ///
        CNetworkHandler* m_pNetworkHandler;
        /// @brief Players
        ///
        CPlayer** m_ppPlayers;
        /// @brief Ground we stand on
        ///
        CFireRope* m_pFireRope;
        /// @brief FireRope that rotates
        ///
        CGround* m_pGround;
        /// @brief Font to display Text
        ///
        PuRe_Font* m_pFont;
        /// @brief Position for the MouseClick
        ///
        PuRe_Vector2F m_MouseClickPosition;
        /// @brief Camera which the player sees from
        ///
        PuRe_Camera* m_pCamera;
        /// @brief If the Game is started
        ///
        bool m_GameStart;
        /// @brief Menu to display Text
        ///
        CMenu* m_pMenu;
    public:
        /// @brief Constructor to Initialize the MainScene
        ///
        CMainScene(PuRe_Application* a_pWindow);
    public:
        /// @brief Loads our Models, threaded function
        ///
        /// @param graphics The graphics interface.
        ///
        void LoadModels(PuRe_IGraphics* a_pGraphics);
        /// @brief Initializes the scene.
        ///
        /// @param graphics The graphics interface.
        ///
        void Initialize(PuRe_IGraphics* a_pGraphics, PuRe_SoundPlayer* a_pSoundPlayer);

        /// @brief Updates the scene.
        ///
        /// @param The graphic interface.
        /// @param The window interface.
        /// @param The input interface.
        /// @param The Time Object
        ///
        /// @returns if it is still running or not
        ///
        bool Update(PuRe_IGraphics* a_pGraphics, PuRe_IWindow* a_pWindow, PuRe_IInput* a_pInput, PuRe_Timer* a_pTimer, PuRe_SoundPlayer* a_pSoundPlayer);

        /// @brief Renders the scene.
        ///
        /// @param graphics The graphics interface.
        ///
        void Render(PuRe_IGraphics* a_pGraphics);

        /// @brief Exists the scene.
        ///
        void Exit();
    };

}

#endif /* _MAINSCENE_H_ */