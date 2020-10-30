#ifdef __linux__
#ifndef _WINDOWLINUX_H_
#define _WINDOWLINUX_H_
// Platform specific includes
#include <X11/Xlib.h>
#include <sys/stat.h> 

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
        class CWindowLinux : public IWindow
        {
        private:

            /// @brief The window description.
            ///
            WindowDescription m_Description;

            /// @brief Indicates whether this window is visible.
            ///
            bool m_IsVisible;

            /// @brief The window handle.
            ///
            Window m_HWND;

            /// @brief The display handle;
            ///
            Display* m_pDisplay;
        public:

            /// @brief Creates an instance of Window.
            ///
            /// @param description The window description.
            ///
            CWindowLinux(WindowDescription& a_rDescription);

            /// @brief Destroyes an instance of Window.
            ///
            ~CWindowLinux();
        public:

            /// @brief Shows the window (makes it visible to the user).
            ///
            void Show();

            /// @brief Hides the window.
            ///
            void Hide();

            /// @brief Get the Window Description
            ///
            /// @returns Window Description Struct
            ///
            SWindowDescription GetDescription();

            /// @brief Creates a Directory
            ///
            /// @param Directory path
            ///
            void MakeDirectory(const char8* a_DirectoryPath);

            /// @brief Find A File within an Directory based on an Index
            ///
            /// @param Index within the Directory
            /// @param Directory path
            ///
            /// @returns File as char array
            ///
            std::string GetFileAtIndex(int32 a_Index, const char8* a_pDirectoryPath);

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
#endif /* _WINDOWLINUX_H_ */
#endif
