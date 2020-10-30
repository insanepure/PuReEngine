#ifndef _TESTSCENE_H_
#define _TESTSCENE_H_

// Framework specific includes
#include <PuReEngine/Core.h>
#include <PuReEngine/Defines.h>

// Declare namespace Game
namespace Game
{
    /// @brief MainScene where the game functions are in, inherits from the Scene interface
    ///
    class CTestScene : public PuRe_IScene
    {
    public:
        /// @brief Constructor to Initialize the MainScene
        ///
        CTestScene(PuRe_Application* a_pWindow);
    public:
        /// @brief Initializes the scene.
        ///
        /// @param graphics The graphics interface.
        /// @param The window interface.
        ///
        void Initialize(PuRe_Application* a_pWindow);

        /// @brief Updates the scene.
        ///
        /// @param The graphic interface.
        /// @param The window interface.
        /// @param The input interface.
        /// @param The Time Object
        ///
        /// @returns if it is still running or not
        ///
        int Update(PuRe_Application* a_pWindow);

        /// @brief Renders the scene.
        ///
        /// @param graphics The graphics interface.
        ///
        void Render(PuRe_Application* a_pWindow);

        /// @brief Exists the scene.
        ///
        void Exit();

    };

}

#endif /* _TESTSCENE_H_ */