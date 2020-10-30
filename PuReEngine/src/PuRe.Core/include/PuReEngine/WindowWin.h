#ifdef _WIN32
#ifndef _WINDOWWIN_H_
#define _WINDOWWIN_H_
// Platform specific includes
#include <Windows.h>

// Engine specific includes
#include "Defines.h"
#include "IWindow.h"
#include "WindowDescription.h"

// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {

        /// @brief A Windows window, inherits from the Interface
        ///
        class CWindowWin : public IWindow
        {
        private:

            /// @brief The window description.
            ///
            SWindowDescription m_Description;

            /// @brief Indicates whether this window is visible.
            ///
            bool m_IsVisible;

            /// @brief The window handle.
            ///
            HWND m_HWND;

            /// @brief The application instance handle.
            ///
            HINSTANCE m_Instance;
        public:

            /// @brief Creates an instance of Window.
            ///
            /// @param description The window description.
            ///
            CWindowWin(SWindowDescription& a_rDescription);

            /// @brief Destroyes an instance of Window.
            ///
            ~CWindowWin();
        public:

            /// @brief Shows the window (makes it visible to the user).
            ///
            void Show();

            /// @brief Hides the window.
            ///
            void Hide();

            /// @brief Creates a Directory
            ///
            /// @param Directory path
            ///
            void MakeDirectory(const char8* a_pDirectoryPath);

            /// @brief Find A File within an Directory based on an Index
            ///
            /// @param Index within the Directory
            /// @param Directory path
            ///
            /// @returns File as char array
            ///
            std::string GetFileAtIndex(int32 a_Index, const char8* a_pDirectoryPath);


            /// @brief Change the Display Mode of the Window
            ///
            /// @param Mode to change to
            ///
            void ChangeDisplayMode(EDisplaySetting a_Display, Vector2<int32> a_Size = Vector2<int32>(1024, 768), Vector2<int32> a_Position = Vector2<int32>(0, 0));

            /// @brief Get the Window Description
            ///
            /// @returns Window Description Struct
            ///
            SWindowDescription GetDescription();

            /// @brief Gets the window handle.
            ///
            /// @returns The handle of this window.
            ///
            void* GetHandle();

            /// @brief Updates Window Description.
            ///
            void Update();
        };

    }
}
#endif /* _WINDOWWIN_H_ */
#endif
