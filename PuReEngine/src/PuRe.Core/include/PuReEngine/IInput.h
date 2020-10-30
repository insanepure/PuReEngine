#ifndef _IINPUT_H_
#define _IINPUT_H_

// Engine specific includes
#include "Defines.h"
#include "Vector2.h"

// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {

        /// @brief Class for Input Handling
        ///
        struct IInput
        {
            /// @brief Mouse Clicks
            ///
            enum EMouse
            {
                LeftClick, MiddleClick, RightClick
            };
            /// @brief Keyboard Keys
            ///
            enum EKeys
            {
                Zero, One, Two, Three, Four, Five, Six, Seven, Eight, Nine,
                A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
                Enter, Backspace, Space, Ctrl, Alt, Shift, ESC,
                F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
                Left, Up, Right, Down, Period, Comma, Minus,
                Num_Zero, Num_One, Num_Two, Num_Three, Num_Four, Num_Five, Num_Six, Num_Seven, Num_Eight, Num_Nine,
                Delete, Insert, PrintScreen
            };
            /// @brief GamePad Keys
            ///
            enum EGamepad
            {
                Pad_A, Pad_B, Pad_X, Pad_Y, DPAD_Left, DPAD_Right, DPAD_Up, DPAD_Down, Left_Shoulder, Right_Shoulder, Pad_Back, Pad_Start, Left_Thumb, Right_Thumb
            };

            /// @brief Destroyes the instance of IInput
            ///
            virtual ~IInput() {};

            /// @brief Returns the State of Lock for the Cursor
            ///
            /// @returns true if locked
            ///
            virtual bool GetCursorLock() = 0;

            /// @brief Lock Cursor at Position
            ///
            virtual void LockCursor() = 0;

            /// @brief UnLock Cursor at Position
            ///
            virtual void UnLockCursor() = 0;

            /// @brief Get the Amount of connected GamePads
            ///
            /// @returns int as the amount of connected gamepads
            ///
            virtual int GetGamepads() = 0;


            /// @brief Set the Cursor's Position
            ///
            /// @param Position as Vector2
            ///
            virtual void SetCursorPosition(Vector2<int32> a_Position) = 0;

            /// @brief Returns whether a Gamepad is pressed once or not
            ///
            /// @param Checked Gamepad Key
            /// @param Gamepad index
            ///
            /// @returns Boolean if the Gamepad Key is still pressed 
            ///
            virtual bool GamepadPressed(EGamepad a_Key, int32 index) = 0;

            /// @brief Returns whether a Gamepad is still pressed or not
            ///
            /// @param Checked Gamepad Key
            /// @param Gamepad index
            ///
            /// @returns Boolean if the Gamepad Key is still pressed
            ///
            virtual bool GamepadIsPressed(EGamepad a_Key, int32 index) = 0;

            /// @brief Returns the Gamepad Left Thumb
            ///
            /// @param Gamepad index
            ///
            /// @returns Vector2 with the Gamepad Left Thumb
            ///
            virtual Vector2<float32> GetGamepadLeftThumb(int32 index) = 0;

            /// @brief Returns the Gamepad Right Thumb
            ///
            /// @param Gamepad index
            ///
            /// @returns Vector2 with the Gamepad Right Thumb
            ///
            virtual Vector2<float32> GetGamepadRightThumb(int32 index) = 0;

            /// @brief Returns the Gamepad Left Trigger at the shoulder
            ///
            /// @param Gamepad index
            ///
            /// @returns float32 with the Value of the Left Trigger at the shoulder
            ///
            virtual float32 GetGamepadLeftTrigger(int32 index) = 0;

            /// @brief Returns the Gamepad Right Trigger at the shoulder
            ///
            /// @param Gamepad index
            ///
            /// @returns float32 with the Value of the Right Trigger at the shoulder
            ///
            virtual float32 GetGamepadRightTrigger(int32 index) = 0;

            /// @brief Returns whether a Keyboard Key is pressed once or not
            ///
            /// @param Checked a Keyboard Key
            ///
            /// @returns Boolean if the a Keyboard Key is pressed once
            ///
            virtual bool KeyPressed(EKeys a_Key) = 0;

            /// @brief Returns whether a MouseKey is pressed once or not
            ///
            /// @param Checked MouseKey
            ///
            /// @returns Boolean if the MouseKey is pressed once
            ///
            virtual bool MousePressed(EMouse a_Key) = 0;

            /// @brief Returns whether a Keyboard Key is still pressed
            ///
            /// @param Checked a Keyboard Key
            ///
            /// @returns Boolean if the Keyboard Key is still pressed
            ///
            virtual bool KeyIsPressed(EKeys a_Key) = 0;

            /// @brief Returns whether a MouseKey is still pressed
            ///
            /// @param Checked MouseKey
            ///
            /// @returns Boolean if the MouseKey is still pressed
            ///
            virtual bool MouseIsPressed(EMouse a_Key) = 0;

            /// @brief Returns the absolute Mouse Position
            ///
            /// @returns Vector2 with the Moouse Coordinate
            ///
            virtual Vector2<float32> GetAbsoluteMousePosition() = 0;

            /// @brief Returns the relativeMouse Position
            ///
            /// @returns Vector2 with the Moouse Coordinate
            ///
            virtual Vector2<float32> GetRelativeMousePosition() = 0;

            /// @brief Returns the Mouse Scroll
            ///
            /// @returns the Mouse scroll as float32
            ///
            virtual float32 GetMouseScroll() = 0;

            /// @brief Returns if X has been clicked on the window
            ///
            /// @returns Boolean whether X has been clicked or not
            ///
            virtual bool CheckQuit() = 0;

            /// @brief Update the Mouse and Keys, is called by the engine
            ///
            virtual void Update() = 0;

        };

    }
}

#endif /* _IINPUT_H_ */