#ifndef _APPLICATION_H_
#define _APPLICATION_H_

// Engine specific includes
#include "IWindow.h"
#include "IPlatform.h"
#include "IGraphics.h"
#include "IScene.h"
#include "IInput.h"
#include "ISignalHandler.h"
#include "ApplicationDescription.h"
#include "Timer.h"
#include "SoundPlayer.h"

// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {
        /// @brief An application.
        ///
        class CApplication
        {

        private:
            /// @brief A pointer to the application window.
            ///
            IWindow* m_pWindow;

            /// @brief A pointer to the platform.
            ///
            IPlatform* m_pPlatform;

            ///// @brief A pointer to the application graphics interface.
            /////
            IGraphics* m_pGraphics;

            ///// @brief A pointer to the signalhandler interface.
            /////
            ISignalHandler* m_pSignalHandler;

            ///// @brief A pointer to the input interface.
            /////
            IInput* m_pInput;

            ///// @brief A pointer to the timer object.
            /////
            CTimer* m_pTimer;

            ///// @brief A pointer to the soundplayer object.
            /////
            CSoundPlayer* m_pSoundPlayer;

            // @brief A pointer to the application description.
            ///
            SApplicationDescription* m_pDescription;

            /// @brief Indicates whether the application has quit.
            ///
            bool m_Quit;

        public:

            /// @brief Creates an instance of Application.
            ///
            /// @param platfiorm The platform.
            /// @param description The application description.
            ///
            CApplication(IPlatform* a_pPlatform, SApplicationDescription& a_rDescription);

        public:

            /// @brief Runs (starts) the application with the specified scene.
            ///
            /// @param scene The initialization scene.
            ///
            void Run(IScene* a_pScene);

            ///// @brief Gets the Input interface.
            /////
            ///// @returns A pointer to the Input interface.
            /////
            IInput* GetInput();

            ///// @brief Gets the Sound interface.
            /////
            ///// @returns A pointer to the Sound interface.
            /////
            CSoundPlayer* GetSoundPlayer();

            ///// @brief Gets the Timer interface.
            /////
            ///// @returns A pointer to the Timer interface.
            /////
            CTimer* GetTimer();

            ///// @brief Gets the Window interface.
            /////
            ///// @returns A pointer to the Window interface.
            /////
            IWindow* GetWindow();

            ///// @brief Gets the graphics interface.
            /////
            ///// @returns A pointer to the graphics interface.
            /////
            IGraphics* GetGraphics();

            /// @brief Gets the platform interface.
            ///
            /// @returns A pointer to the platform interface.
            ///
            IPlatform* GetPlatform();
        };
    }
}

#endif /* _APPLICATION_H_ */