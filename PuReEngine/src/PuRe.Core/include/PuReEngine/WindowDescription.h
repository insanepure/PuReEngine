#ifndef _WINDOWDESCRIPTION_H_
#define _WINDOWDESCRIPTION_H_

// Engine specific includes
#include "Defines.h"

// Declare namespace PuReEngine::Core
namespace PuReEngine 
{
    namespace Core 
    {
        enum EDisplaySetting
        {
            Windowed,
            Fullscreen,
            FullscreenWindowed
        };
        /// @brief Description of the Window Object
        ///
        struct SWindowDescription
        {
            /// @brief The window x position
            ///
            int32 X;
            
            /// @brief The window y position
            ///
            int32 Y;
            
            /// @brief The window width.
            ///
            int32 Width;
            
            /// @brief The window height.
            ///
            int32 Height;
            
            /// @brief The window title.
            ///
            const char8* Title;
            
            /// @brief Whether it should be started in fullscreen or not
            ///
            EDisplaySetting DisplaySetting;


            /// @brief Whether The Cursor is shown or not.
            ///
            bool ShowCursor;


            /// @brief Whether The Cursor is locked at start or not.
            ///
            bool LockCursor;

            /// @brief Whether The Cursor is locked in the Window or not
            ///
            bool CursorInWindow;
        };

    }
}

#endif /* _WINDOWDESCRIPTION_H_ */