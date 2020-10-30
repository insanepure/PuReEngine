#include "include/PuReEngine/InputLinux.h"
#ifdef __linux__
namespace PuReEngine 
{
    namespace Core 
    {

        // **************************************************************************
        // **************************************************************************
        CInputLinux::CInputLinux()
        {
            //Set all to false
            PuRe_CLEAR(this->m_KeyPress);
            PuRe_CLEAR(this->m_KeyIsPress);
            PuRe_CLEAR(this->m_MousePress);
            PuRe_CLEAR(this->m_MouseIsPress);
            PuRe_CLEAR(this->m_GamepadPress);
            PuRe_CLEAR(this->m_GamepadIsPress);

            this->m_Quit = false;
        }

        // **************************************************************************
        // **************************************************************************
        bool CInputLinux::GamepadPressed(EGamepad a_Key, int32 index)
        {
            return this->m_GamepadPress[a_Key];
        }

        // **************************************************************************
        // **************************************************************************
        bool CInputLinux::GamepadIsPressed(EGamepad a_Key, int32 index)
        {
            return this->m_GamepadIsPress[a_Key];
        }
        Vector2<float32> CInputLinux::GetGamepadLeftThumb(int32 index)
        {
            Vector2<float32> thumb(0.0f,0.0f);
            return thumb;
        }

        // **************************************************************************
        // **************************************************************************
        Vector2<float32> CInputLinux::GetGamepadRightThumb(int32 index)
        {
            Vector2<float32> thumb(0.0f, 0.0f);
            return thumb;
        }

        // **************************************************************************
        // **************************************************************************
        float32 CInputLinux::GetGamepadLeftTrigger(int32 index)
        {
            float32 trigger = 0.0f;
            return trigger;
        }

        // **************************************************************************
        // **************************************************************************
        float32 CInputLinux::GetGamepadRightTrigger(int32 index)
        {
            float32 trigger = 0.0f;
            return trigger;
        }

        // **************************************************************************
        // **************************************************************************
        bool CInputLinux::KeyPressed(Keys a_Key)
        {
            return this->m_KeyPress[a_Key];
        }

        // **************************************************************************
        // **************************************************************************
        bool CInputLinux::KeyIsPressed(Keys a_Key)
        {
            return this->m_KeyIsPress[a_Key];
        }

        // **************************************************************************
        // **************************************************************************
        bool CInputLinux::MousePressed(Mouse a_Key)
        {
            return this->m_MousePress[a_Key];
        }

        // **************************************************************************
        // **************************************************************************
        bool CInputLinux::MouseIsPressed(Mouse a_Key)
        {
            return this->m_MouseIsPress[a_Key];
        }

        // **************************************************************************
        // **************************************************************************
        Vector2<float32> CInputLinux::GetAbsoluteMousePosition()
        {
            return this->m_MousePosition;
        }

        // **************************************************************************
        // **************************************************************************
        Vector2<float32> CInputLinux::GetRelativeMousePosition()
        {
            return this->m_MousePositionLast-this->m_MousePosition;
        }

        // **************************************************************************
        // **************************************************************************
        bool CInputWin::GetCursorLock()
        {
            return this->m_CursorLock;
        }

        // **************************************************************************
        // **************************************************************************
        void CInputWin::LockCursor()
        {
            this->m_CursorLock = true;
        }

        // **************************************************************************
        // **************************************************************************
        void CInputWin::UnLockCursor()
        {
            this->m_CursorLock = false;
        }

        // **************************************************************************
        // **************************************************************************
        bool CInputLinux::CheckQuit()
        {
            return this->m_Quit;
        }
        // **************************************************************************
        // **************************************************************************
        void CInputLinux::Update()
        {
            XEvent event;
            Display *display = XOpenDisplay(NULL);
            Window root= XDefaultRootWindow(display);
            XGrabPointer(display, root, False, ButtonPressMask, GrabModeAsync,
                GrabModeAsync, None, None, CurrentTime);
            XSelectInput(display, root, ButtonPressMask);
        }
    }
}
#endif
