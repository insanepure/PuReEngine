#ifndef _IWINDOW_H_
#define _IWINDOW_H_

// Engine specific includes
#include "WindowDescription.h"
#include "Vector2.h"
#include <string>

// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {

        /// @brief Base interface for an application window.
        ///
        struct IWindow
        {
            /// @brief Destroyes an Instance of IWindow
            ///
            virtual ~IWindow() {};
            /// @brief Gets the description of the window.
            ///
            /// @returns The description of this window.
            ///
            virtual SWindowDescription GetDescription() = 0;

            /// @brief Creates a Directory
            ///
            /// @param Directory path
            ///
            virtual void MakeDirectory(const char8* a_pDirectoryPath) = 0;

            /// @brief Find A File within an Directory based on an Index
            ///
            /// @param Index within the Directory
            /// @param Directory path
            ///
            /// @returns File as char array
            ///
            virtual std::string GetFileAtIndex(int32 a_Index, const char8* a_pDirectoryPath) = 0;


            /// @brief Change the Display Mode of the Window
            ///
            /// @param Mode to change to
            /// @param Size of the Window
            /// @param Position of the Window
            ///
            virtual void ChangeDisplayMode(EDisplaySetting a_Display, Vector2<int32> a_Size = Vector2<int32>(1024, 768), Vector2<int32> a_Position = Vector2<int32>(0, 0)) = 0;


            /// @brief Shows the window (makes it visible to the user).
            ///
            virtual void Show() = 0;

            /// @brief Hides the window (makes it invisible to the user).
            ///
            virtual void Hide() = 0;

            /// @brief Updates Window Description.
            ///
            virtual void Update() = 0;
            /// @brief Gets a pointer to the handle of the window.
            ///
            /// @returns A pointer to the handle of the window.
            ///
            virtual void* GetHandle() = 0;
        };

    }
}

#endif /* _IWINDOW_H_ */