#ifndef _ISCENE_H_
#define _ISCENE_H_

// Engine specific includes
#include "Defines.h"


// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {
        class CApplication;
        /// @brief Base interface for scenes.
        ///
        struct IScene
        {
            /// @brief Initializes the scene.
            ///
            /// @param pointer to the application.
            ///
            virtual void Initialize(CApplication* a_pApplication) = 0;

            /// @brief Updates the scene.
            ///
            /// @param pointer to the application.
            ///
            /// @return A State to return what this Scene is doing, for switching Scenes
            ///
            virtual int Update(CApplication* a_pApplication) = 0;

            /// @brief Renders the scene.
            ///
            /// @param pointer to the application.
            ///
            virtual void Render(CApplication* a_pApplication) = 0;

            /// @brief Exists the scene.
            ///
            virtual void Exit() = 0;
        };

    }
}

#endif /* _ISCENE_H_ */