#ifdef _WIN32
#ifndef _INPUTWIN_H_
#define _INPUTWIN_H_
// Platform specific includes
#include <Windows.h>
#include <Xinput.h>
#include <cstdio>

// Engine specific includes
#include "Defines.h"
#include "IInput.h"

// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {

        /// @brief Class for Input Handling
        ///
        class CInputWin : public IInput
        {
        private:
            /// @brief State of the Cursor
            ///
            bool m_CursorLock;
            /// @brief MouseScroll
            ///
            float32 m_MouseScroll;
            /// @brief Relative Mouse Change
            ///
            Vector2<float32> m_MouseRelative;
            /// @brief Mouse Position
            ///
            Vector2<float32> m_MousePosition;
            /// @brief Gamepad pressed once
            ///
            bool m_GamepadPress[4][14];
            /// @brief Gamepad pressed
            ///
            bool m_GamepadIsPress[4][14];
            /// @brief Mouse pressed once
            ///
            bool m_MousePress[3];
            /// @brief Mouse pressed
            ///
            bool m_MouseIsPress[3];
            /// @brief Key pressed once
            ///
            bool m_KeyPress[75];
            /// @brief Mouse pressed
            ///
            bool m_KeyIsPress[75];
            /// @brief X on Window
            ///
            bool m_Quit;
            /// @brief Window Handle
            ///
            HWND m_HWND;
        public:
            /// @brief Creates an instance of CInputWin
            ///
            /// @param Window Handle
            ///
            CInputWin(HWND a_HWND);

            /// @brief Destroyes the instance of CInputWin
            ///
            ~CInputWin();
        public:

            /// @brief Returns the State of Lock for the Cursor
            ///
            /// @returns true if locked
            ///
            bool GetCursorLock();

            /// @brief Lock Cursor at Position
            ///
            void LockCursor();

            /// @brief UnLock Cursor at Position
            ///
            void UnLockCursor();

            /// @brief Get the Amount of connected GamePads
            ///
            /// @returns int as the amount of connected gamepads
            ///
            int GetGamepads();

            /// @brief Set the Cursor's Position
            ///
            /// @param Position as Vector2
            ///
            void SetCursorPosition(Vector2<int32> a_Position);

            /// @brief Returns whether a Gamepad is pressed once or not
            ///
            /// @param Checked Gamepad Key
            /// @param Gamepad index
            ///
            /// @returns Boolean if the Gamepad Key is still pressed 
            ///
            bool GamepadPressed(EGamepad a_Key, int32 index);

            /// @brief Returns whether a Gamepad is still pressed or not
            ///
            /// @param Checked Gamepad Key
            /// @param Gamepad index
            ///
            /// @returns Boolean if the Gamepad Key is still pressed
            ///
            bool GamepadIsPressed(EGamepad a_Key, int32 index);

            /// @brief Returns the Gamepad Left Thumb
            ///
            /// @param Gamepad index
            ///
            /// @returns Vector2 with the Gamepad Left Thumb
            ///
            Vector2<float32> GetGamepadLeftThumb(int32 index);

            /// @brief Returns the Gamepad Right Thumb
            ///
            /// @param Gamepad index
            ///
            /// @returns Vector2 with the Gamepad Right Thumb
            ///
            Vector2<float32> GetGamepadRightThumb(int32 index);

            /// @brief Returns the Gamepad Left Trigger at the shoulder
            ///
            /// @param Gamepad index
            ///
            /// @returns float32 with the Value of the Left Trigger at the shoulder
            ///
            float32 GetGamepadLeftTrigger(int32 index);

            /// @brief Returns the Gamepad Right Trigger at the shoulder
            ///
            /// @param Gamepad index
            ///
            /// @returns float32 with the Value of the Right Trigger at the shoulder
            ///
            float32 GetGamepadRightTrigger(int32 index);

            /// @brief Returns whether a Keyboard Key is pressed once or not
            ///
            /// @param Checked a Keyboard Key
            ///
            /// @returns Boolean if the a Keyboard Key is pressed once
            ///
            bool KeyPressed(EKeys a_Key);

            /// @brief Returns whether a MouseKey is pressed once or not
            ///
            /// @param Checked MouseKey
            ///
            /// @returns Boolean if the MouseKey is pressed once
            ///
            bool MousePressed(EMouse a_Key);

            /// @brief Returns whether a Keyboard Key is still pressed
            ///
            /// @param Checked a Keyboard Key
            ///
            /// @returns Boolean if the Keyboard Key is still pressed
            ///
            bool KeyIsPressed(EKeys a_Key);

            /// @brief Returns whether a MouseKey is still pressed
            ///
            /// @param Checked MouseKey
            ///
            /// @returns Boolean if the MouseKey is still pressed
            ///
            bool MouseIsPressed(EMouse a_Key);

            /// @brief Returns the absolute Mouse Position
            ///
            /// @returns Vector2 with the Moouse Coordinate
            ///
            Vector2<float32> GetAbsoluteMousePosition();

            /// @brief Returns the relativeMouse Position
            ///
            /// @returns Vector2 with the Moouse Coordinate
            ///
            Vector2<float32> GetRelativeMousePosition();

            /// @brief Returns the Mouse Scroll
            ///
            /// @returns the Mouse scroll as float32
            ///
            float32 GetMouseScroll();

            /// @brief Returns if X has been clicked on the window
            ///
            /// @returns Boolean whether X has been clicked or not
            ///
            bool CheckQuit();

            /// @brief Update the Mouse and Keys, is called by the engine
            ///
            void Update();
        };

    }
}
#endif /* _INPUTWIN_H_ */
#endif