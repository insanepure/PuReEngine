#include "include/PuReEngine/InputWin.h"
#ifdef _WIN32
namespace PuReEngine
{
    namespace Core
    {

        // **************************************************************************
        // **************************************************************************
        CInputWin::CInputWin(HWND a_HWND) : m_HWND(a_HWND)
        {
            //Set all to false
            PuRe_CLEAR(this->m_KeyPress);
            PuRe_CLEAR(this->m_KeyIsPress);
            PuRe_CLEAR(this->m_MousePress);
            PuRe_CLEAR(this->m_MouseIsPress);
            PuRe_CLEAR(this->m_GamepadPress);
            PuRe_CLEAR(this->m_GamepadIsPress);
            this->m_MousePosition = Vector2<float32>(0.0f, 0.0f);
            this->m_MouseRelative = Vector2<float32>(0.0f, 0.0f);
            this->m_CursorLock = true;
            this->m_Quit = false;
        }
        CInputWin::~CInputWin()
        {

        }

        // **************************************************************************
        // **************************************************************************
        bool CInputWin::GamepadPressed(EGamepad a_Key, int32 index)
        {
            if (GetForegroundWindow() == this->m_HWND&&index < 4)
                return this->m_GamepadPress[index][a_Key];
            else
                return false;
        }

        // **************************************************************************
        // **************************************************************************
        void CInputWin::SetCursorPosition(Vector2<int32> a_Position)
        {
            if (GetForegroundWindow() == this->m_HWND)
            {
                RECT winRC, clientRC;
                GetWindowRect(this->m_HWND, &winRC); //get the current window rect
                GetClientRect(this->m_HWND, &clientRC); //get the current client rect
                int dx = (clientRC.right - clientRC.left); //calculate difference between current client width and desired client width
                int dy = (clientRC.bottom - clientRC.top); //same for height
                //adjust the size
                int32 Width = (winRC.right - winRC.left - dx) / 2; //Width of the Window at the left side
                int32 Height = (winRC.bottom - winRC.top - dy) - Width; //Height of the topbar

                SetCursorPos(winRC.left + a_Position.X + Width, winRC.top + a_Position.Y + Height);
                this->m_MousePosition = Vector2<float32>((float32)a_Position.X, (float32)a_Position.Y);
            }
        }

        int CInputWin::GetGamepads()
        {   
            int pads = 0;
            XINPUT_STATE state;
            for (unsigned int i = 0; i < 4; i++)
            {
                if(XInputGetState(i, &state) == ERROR_SUCCESS)
                    pads++;
            }
            return pads;
        }

        // **************************************************************************
        // **************************************************************************
        bool CInputWin::GamepadIsPressed(EGamepad a_Key, int32 index)
        {
            if (GetForegroundWindow() == this->m_HWND&&index < 4)
                return this->m_GamepadIsPress[index][a_Key];
            else
                return false;
        }
        Vector2<float32> CInputWin::GetGamepadLeftThumb(int32 index)
        {
            XINPUT_STATE state;
            Vector2<float32> thumb(0.0f, 0.0f);
            if (GetForegroundWindow() == this->m_HWND&&index < 4 && XInputGetState(index, &state) == ERROR_SUCCESS)
            {
                thumb.X = fmaxf(-1, (float32)state.Gamepad.sThumbLX / 32767);
                thumb.Y = fmaxf(-1, (float32)state.Gamepad.sThumbLY / 32767);
            }
            return thumb;
        }

        // **************************************************************************
        // **************************************************************************
        Vector2<float32> CInputWin::GetGamepadRightThumb(int32 index)
        {
            XINPUT_STATE state;
            Vector2<float32> thumb(0.0f, 0.0f);
            if (GetForegroundWindow() == this->m_HWND&&index < 4 && XInputGetState(index, &state) == ERROR_SUCCESS)
            {
                thumb.X = fmaxf(-1, (float32)state.Gamepad.sThumbRX / 32767);
                thumb.Y = fmaxf(-1, (float32)state.Gamepad.sThumbRY / 32767);
            }
            return thumb;
        }

        // **************************************************************************
        // **************************************************************************
        float32 CInputWin::GetGamepadLeftTrigger(int32 index)
        {
            XINPUT_STATE state;
            float32 trigger = 0.0f;
            if (GetForegroundWindow() == this->m_HWND&&index < 4 && XInputGetState(index, &state) == ERROR_SUCCESS)
            {
                trigger = (float32)state.Gamepad.bLeftTrigger / 255;
            }
            return trigger;
        }

        // **************************************************************************
        // **************************************************************************
        float32 CInputWin::GetGamepadRightTrigger(int32 index)
        {
            XINPUT_STATE state;
            float32 trigger = 0.0f;
            if (GetForegroundWindow() == this->m_HWND&&index < 4 && XInputGetState(index, &state) == ERROR_SUCCESS)
            {
                trigger = (float32)state.Gamepad.bRightTrigger / 255;
            }
            return trigger;
        }

        // **************************************************************************
        // **************************************************************************
        bool CInputWin::KeyPressed(EKeys a_Key)
        {
            return this->m_KeyPress[a_Key];
        }

        // **************************************************************************
        // **************************************************************************
        bool CInputWin::KeyIsPressed(EKeys a_Key)
        {
            return this->m_KeyIsPress[a_Key];
        }

        // **************************************************************************
        // **************************************************************************
        bool CInputWin::MousePressed(EMouse a_Key)
        {
            return this->m_MousePress[a_Key];
        }

        // **************************************************************************
        // **************************************************************************
        bool CInputWin::MouseIsPressed(EMouse a_Key)
        {
            return this->m_MouseIsPress[a_Key];
        }

        // **************************************************************************
        // **************************************************************************
        Vector2<float32> CInputWin::GetAbsoluteMousePosition()
        {
            return this->m_MousePosition;
        }

        // **************************************************************************
        // **************************************************************************
        Vector2<float32> CInputWin::GetRelativeMousePosition()
        {
            return this->m_MouseRelative;
        }

        // **************************************************************************
        // **************************************************************************
        float32 CInputWin::GetMouseScroll()
        {
            return this->m_MouseScroll;
        }

        // **************************************************************************
        // **************************************************************************
        bool CInputWin::CheckQuit()
        {
            return this->m_Quit;
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
        void CInputWin::Update()
        {
            MSG msg;
            //set all once Press to false
            this->m_MouseScroll = 0.0f;
            this->m_MouseRelative = this->m_MousePosition;
            PuRe_CLEAR(this->m_KeyPress);
            PuRe_CLEAR(this->m_MousePress);
            PuRe_CLEAR(this->m_GamepadPress);
            char key = 0;

            //this is needed because we want to check if it is pressed once or kept pressing
            //so for checking if it is pressed once we need to check if it was pressed before or not
            for (int32 i = 0; i < 4; i++)
            {
                XINPUT_STATE state;
                ZeroMemory(&state, sizeof(XINPUT_STATE));
                if (XInputGetState(i, &state) == ERROR_SUCCESS)
                {
                    for (int32 key = 0; key < 14; key++)
                    {
                        switch (key)
                        {
                        case EGamepad::Pad_A:
                            if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0)
                            {
                                if (!this->m_GamepadIsPress[i][key])
                                    this->m_GamepadPress[i][key] = true;
                                this->m_GamepadIsPress[i][key] = true;
                            }
                            else
                            {
                                this->m_GamepadIsPress[i][key] = false;
                            }
                            break;
                        case EGamepad::Pad_B:
                            if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0)
                            {
                                if (!this->m_GamepadIsPress[i][key]) this->m_GamepadPress[i][key] = true;
                                this->m_GamepadIsPress[i][key] = true;
                            }
                            else
                                this->m_GamepadIsPress[i][key] = false;
                            break;
                        case EGamepad::Pad_X:
                            if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_X) != 0)
                            {
                                if (!this->m_GamepadIsPress[i][key]) this->m_GamepadPress[i][key] = true;
                                this->m_GamepadIsPress[i][key] = true;
                            }
                            else
                                this->m_GamepadIsPress[i][key] = false;;
                            break;
                        case EGamepad::Pad_Y:
                            if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) != 0)
                            {
                                if (!this->m_GamepadIsPress[i][key]) this->m_GamepadPress[i][key] = true;
                                this->m_GamepadIsPress[i][key] = true;
                            }
                            else
                                this->m_GamepadIsPress[i][key] = false;
                            break;
                        case EGamepad::DPAD_Left:
                            if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0)
                            {
                                if (!this->m_GamepadIsPress[i][key]) this->m_GamepadPress[i][key] = true;
                                this->m_GamepadIsPress[i][key] = true;
                            }
                            else
                                this->m_GamepadIsPress[i][key] = false;
                            break;
                        case EGamepad::DPAD_Right:
                            if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0)
                            {
                                if (!this->m_GamepadIsPress[i][key]) this->m_GamepadPress[i][key] = true;
                                this->m_GamepadIsPress[i][key] = true;
                            }
                            else
                                this->m_GamepadIsPress[i][key] = false;
                            break;
                        case EGamepad::DPAD_Up:
                            if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0)
                            {
                                if (!this->m_GamepadIsPress[i][key]) this->m_GamepadPress[i][key] = true;
                                this->m_GamepadIsPress[i][key] = true;
                            }
                            else
                                this->m_GamepadIsPress[i][key] = false;
                            break;
                        case EGamepad::DPAD_Down:
                            if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0)
                            {
                                if (!this->m_GamepadIsPress[i][key]) this->m_GamepadPress[i][key] = true;
                                this->m_GamepadIsPress[i][key] = true;
                            }
                            else
                                this->m_GamepadIsPress[i][key] = false;
                            break;
                        case EGamepad::Left_Shoulder:
                            if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0)
                            {
                                if (!this->m_GamepadIsPress[i][key]) this->m_GamepadPress[i][key] = true;
                                this->m_GamepadIsPress[i][key] = true;
                            }
                            else
                                this->m_GamepadIsPress[i][key] = false;
                            break;
                        case EGamepad::Right_Shoulder:
                            if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0)
                            {
                                if (!this->m_GamepadIsPress[i][key]) this->m_GamepadPress[i][key] = true;
                                this->m_GamepadIsPress[i][key] = true;
                            }
                            else
                                this->m_GamepadIsPress[i][key] = false;
                            break;
                        case EGamepad::Pad_Back:
                            if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) != 0)
                            {
                                if (!this->m_GamepadIsPress[i][key]) this->m_GamepadPress[i][key] = true;
                                this->m_GamepadIsPress[i][key] = true;
                            }
                            else
                                this->m_GamepadIsPress[i][key] = false;
                            break;
                        case EGamepad::Pad_Start:
                            if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_START) != 0)
                            {
                                if (!this->m_GamepadIsPress[i][key]) this->m_GamepadPress[i][key] = true;
                                this->m_GamepadIsPress[i][key] = true;
                            }
                            else
                                this->m_GamepadIsPress[i][key] = false;
                            break;
                        case EGamepad::Left_Thumb:
                            if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) != 0)
                            {
                                if (!this->m_GamepadIsPress[i][key]) this->m_GamepadPress[i][key] = true;
                                this->m_GamepadIsPress[i][key] = true;
                            }
                            else
                                this->m_GamepadIsPress[i][key] = false;
                            break;
                        case EGamepad::Right_Thumb:
                            if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) != 0)
                            {
                                if (!this->m_GamepadIsPress[i][key]) this->m_GamepadPress[i][key] = true;
                                this->m_GamepadIsPress[i][key] = true;
                            }
                            else
                                this->m_GamepadIsPress[i][key] = false;
                            break;
                        }
                    }

                }
            }

            while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
                switch (msg.message)
                {
                case WM_QUIT:
                    this->m_Quit = true;
                    break;
                case WM_SYSKEYUP: case WM_SYSKEYDOWN:
                    if (msg.wParam == VK_F10)
                    {
                        if (msg.message == WM_SYSKEYDOWN)
                        {
                            if (!this->m_KeyIsPress[this->F10]) this->m_KeyPress[this->F10] = true;
                            this->m_KeyIsPress[this->F10] = true;
                        }
                        else
                            this->m_KeyIsPress[this->F10] = false;
                        continue;
                    }
                    else if (msg.message == WM_SYSKEYDOWN)
                    {
                        if (!this->m_KeyIsPress[this->Alt]) this->m_KeyPress[this->Alt] = true;
                        this->m_KeyIsPress[this->Alt] = true;
                    }
                    else
                        this->m_KeyIsPress[this->Alt] = false;
                    break;
                case WM_KEYDOWN: case WM_KEYUP:
                    switch (msg.wParam)
                    {
                        //Arrow Keys
                    case VK_LEFT:  case VK_UP: case VK_RIGHT: case VK_DOWN:
                        key = (char8)msg.wParam - 37 + 55; // Left is key 55
                        if (msg.message == WM_KEYDOWN)
                        {
                            if (!this->m_KeyIsPress[key]) this->m_KeyPress[key] = true;
                            this->m_KeyIsPress[key] = true;
                        }
                        else
                            this->m_KeyIsPress[key] = false;
                        break;
                        //F1-F12
                    case VK_F1: case VK_F2: case VK_F3: case VK_F4: case VK_F5: case VK_F6: case VK_F7: case VK_F8: case VK_F9:
                    case VK_F10: case VK_F11: case VK_F12:
                        key = (char8)msg.wParam - 112 + 43; // F1 is key 43
                        if (msg.message == WM_KEYDOWN)
                        {
                            if (!this->m_KeyIsPress[key]) this->m_KeyPress[key] = true;
                            this->m_KeyIsPress[key] = true;
                        }
                        else
                            this->m_KeyIsPress[key] = false;
                        break;
                        //1-9
                    case 0x30: case 0x31: case 0x32: case 0x33: case 0x34: case 0x35: case 0x36: case 0x37: case 0x38:
                    case 0x39:
                        key = (char8)msg.wParam - 48; // zero is key 0
                        if (msg.message == WM_KEYDOWN)
                        {
                            if (!this->m_KeyIsPress[key]) this->m_KeyPress[key] = true;
                            this->m_KeyIsPress[key] = true;
                        }
                        else
                            this->m_KeyIsPress[key] = false;
                        break;
                    case 0x60: case 0x61: case 0x62: case 0x63: case 0x64: case 0x65: case 0x66: case 0x67:
                    case 0x68: case 0x69:
                        key = (char8)msg.wParam - 96 + 62; // zero is key 0
                        if (msg.message == WM_KEYDOWN)
                        {
                            if (!this->m_KeyIsPress[key]) this->m_KeyPress[key] = true;
                            this->m_KeyIsPress[key] = true;
                        }
                        else
                            this->m_KeyIsPress[key] = false;
                        break;
                        //A-Z
                    case 0x41: case 0x42: case 0x43: case 0x44: case 0x45: case 0x46: case 0x47: case 0x48: case 0x49:
                    case 0x4A: case 0x4B: case 0x4C: case 0x4D: case 0x4E: case 0x4F: case 0x50: case 0x51: case 0x52:
                    case 0x53: case 0x54: case 0x55: case 0x56: case 0x57: case 0x58: case 0x59: case 0x5A:
                        key = (char8)msg.wParam - 65 + 10; // A is key 10
                        if (msg.message == WM_KEYDOWN)
                        {
                            if (!this->m_KeyIsPress[key]) this->m_KeyPress[key] = true;
                            this->m_KeyIsPress[key] = true;
                        }
                        else
                            this->m_KeyIsPress[key] = false;
                        break;
                        //Escape
                    case VK_ESCAPE:
                        if (msg.message == WM_KEYDOWN)
                        {
                            if (!this->m_KeyIsPress[this->ESC]) this->m_KeyPress[this->ESC] = true;
                            this->m_KeyIsPress[this->ESC] = true;
                        }
                        else
                            this->m_KeyIsPress[this->ESC] = false;
                        break;
                        //Shift
                    case VK_SHIFT:
                        if (msg.message == WM_KEYDOWN)
                        {
                            if (!this->m_KeyIsPress[this->Shift]) this->m_KeyPress[this->Shift] = true;
                            this->m_KeyIsPress[this->Shift] = true;
                        }
                        else
                            this->m_KeyIsPress[this->Shift] = false;
                        break;
                        //Alt
                    case VK_MENU:
                        if (msg.message == WM_KEYDOWN)
                        {
                            if (!this->m_KeyIsPress[this->Alt]) this->m_KeyPress[this->Alt] = true;
                            this->m_KeyIsPress[this->Alt] = true;
                        }
                        else
                            this->m_KeyIsPress[this->Alt] = false;
                        break;
                        //Ctrl
                    case VK_CONTROL:
                        if (msg.message == WM_KEYDOWN)
                        {
                            if (!this->m_KeyIsPress[this->Ctrl]) this->m_KeyPress[this->Ctrl] = true;
                            this->m_KeyIsPress[this->Ctrl] = true;
                        }
                        else
                            this->m_KeyIsPress[this->Ctrl] = false;
                        break;
                        //Space
                    case VK_SPACE:
                        if (msg.message == WM_KEYDOWN)
                        {
                            if (!this->m_KeyIsPress[this->Space]) this->m_KeyPress[this->Space] = true;
                            this->m_KeyIsPress[this->Space] = true;
                        }
                        else
                            this->m_KeyIsPress[this->Space] = false;
                        break;
                        //Delete
                    case VK_DELETE:
                        if (msg.message == WM_KEYDOWN)
                        {
                            if (!this->m_KeyIsPress[this->Delete]) this->m_KeyPress[this->Delete] = true;
                            this->m_KeyIsPress[this->Delete] = true;
                        }
                        else
                            this->m_KeyIsPress[this->Delete] = false;
                        break;
                        //Delete
                    case VK_INSERT:
                        if (msg.message == WM_KEYDOWN)
                        {
                            if (!this->m_KeyIsPress[this->Insert]) this->m_KeyPress[this->Insert] = true;
                            this->m_KeyIsPress[this->Insert] = true;
                        }
                        else
                            this->m_KeyIsPress[this->Insert] = false;
                        break;
                        //Delete
                    case VK_SNAPSHOT:
                        if (msg.message == WM_KEYDOWN)
                        {
                            if (!this->m_KeyIsPress[this->PrintScreen]) this->m_KeyPress[this->PrintScreen] = true;
                            this->m_KeyIsPress[this->PrintScreen] = true;
                        }
                        else
                            this->m_KeyIsPress[this->PrintScreen] = false;
                        break;
                        //Enter
                    case VK_RETURN:
                        if (msg.message == WM_KEYDOWN)
                        {
                            if (!this->m_KeyIsPress[this->Enter]) this->m_KeyPress[this->Enter] = true;
                            this->m_KeyIsPress[this->Enter] = true;
                        }
                        else
                            this->m_KeyIsPress[this->Enter] = false;
                        break;
                        //Backspace
                    case VK_BACK:
                        if (msg.message == WM_KEYDOWN)
                        {
                            if (!this->m_KeyIsPress[this->Backspace]) this->m_KeyPress[this->Backspace] = true;
                            this->m_KeyIsPress[this->Backspace] = true;
                        }
                        else
                            this->m_KeyIsPress[this->Backspace] = false;
                        break;
                        //Period/Dot
                    case VK_OEM_PERIOD:
                        if (msg.message == WM_KEYDOWN)
                        {
                            if (!this->m_KeyIsPress[this->Period]) this->m_KeyPress[this->Period] = true;
                            this->m_KeyIsPress[this->Period] = true;
                        }
                        else
                            this->m_KeyIsPress[this->Period] = false;
                        break;
                        //Comma
                    case VK_OEM_COMMA:
                        if (msg.message == WM_KEYDOWN)
                        {
                            if (!this->m_KeyIsPress[this->Comma]) this->m_KeyPress[this->Comma] = true;
                            this->m_KeyIsPress[this->Comma] = true;
                        }
                        else
                            this->m_KeyIsPress[this->Comma] = false;
                        break;
                        //Minus
                    case VK_OEM_MINUS:
                        if (msg.message == WM_KEYDOWN)
                        {
                            if (!this->m_KeyIsPress[this->Minus]) this->m_KeyPress[this->Minus] = true;
                            this->m_KeyIsPress[this->Minus] = true;
                        }
                        else
                            this->m_KeyIsPress[this->Minus] = false;
                        break;
                    default:
                        break;
                    }
                    break;
                case WM_MOUSEWHEEL:
                    this->m_MouseScroll = GET_WHEEL_DELTA_WPARAM(msg.wParam) / 120.0f;
                    break;
                case WM_MOUSEMOVE:
                    this->m_MousePosition.X = LOWORD(msg.lParam);
                    this->m_MousePosition.Y = HIWORD(msg.lParam);
                    break;
                case WM_LBUTTONDOWN:
                    this->m_MousePress[this->LeftClick] = true;
                    this->m_MouseIsPress[this->LeftClick] = true;
                    break;
                case WM_LBUTTONUP:
                    this->m_MouseIsPress[this->LeftClick] = false;
                    break;
                case WM_MBUTTONDOWN:
                    this->m_MousePress[this->MiddleClick] = true;
                    this->m_MouseIsPress[this->MiddleClick] = true;
                    break;
                case WM_MBUTTONUP:
                    this->m_MouseIsPress[this->MiddleClick] = false;
                    break;
                case WM_RBUTTONDOWN:
                    this->m_MousePress[this->RightClick] = true;
                    this->m_MouseIsPress[this->RightClick] = true;
                    break;
                case WM_RBUTTONUP:
                    this->m_MouseIsPress[this->RightClick] = false;
                    break;

                default:
                    break;
                }
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }


            this->m_MouseRelative = this->m_MousePosition - this->m_MouseRelative;
            if (this->m_CursorLock)
            {
                RECT winRC;
                GetWindowRect(this->m_HWND, &winRC); //get the current window rect
                this->SetCursorPosition(Vector2<int32>((winRC.right - winRC.left) / 2, (winRC.bottom - winRC.top) / 2));
            }

        }
    }
}
#endif