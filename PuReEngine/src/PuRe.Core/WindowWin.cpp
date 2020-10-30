#include "include/PuReEngine/WindowWin.h"
#ifdef _WIN32
namespace PuReEngine
{
    namespace Core
    {


        LRESULT CALLBACK WndProc(HWND a_HWND, unsigned int a_Message, WPARAM a_WParam, LPARAM a_LParam)
        {
            switch (a_Message)
            {
            case WM_CLOSE:
                DestroyWindow(a_HWND);
                break;
            case WM_DESTROY:
                PostQuitMessage(0);
                break;
            }

            return DefWindowProc(a_HWND, a_Message, a_WParam, a_LParam);
        }


        CWindowWin::CWindowWin(SWindowDescription& a_rDescription)
        {
            WNDCLASS wc;
            this->m_Description = a_rDescription;
            this->m_IsVisible = false;
            this->m_Instance = GetModuleHandle(NULL);

            wc.cbWndExtra = 0;
            wc.cbClsExtra = 0;
            wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
            wc.hCursor = LoadCursor(NULL, IDC_ARROW);
            wc.hIcon = 0;
            wc.hInstance = this->m_Instance;
            wc.lpszClassName = this->m_Description.Title;
            wc.lpfnWndProc = WndProc;
            wc.lpszMenuName = 0;
            wc.style = CS_VREDRAW | CS_HREDRAW;

            RegisterClass(&wc);
            this->m_HWND = CreateWindowEx(NULL, wc.lpszClassName, wc.lpszClassName, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
                0, 0, this->m_Description.Width, this->m_Description.Height, 0, 0, this->m_Instance, 0);

            //Set Cursor
            ShowCursor(a_rDescription.ShowCursor);
            this->m_IsVisible = true;
            this->ChangeDisplayMode(this->m_Description.DisplaySetting, Vector2<int32>(this->m_Description.Width, this->m_Description.Height), Vector2<int32>(this->m_Description.X, this->m_Description.Y));
        }

        CWindowWin::~CWindowWin()
        {
            if (this->m_Description.DisplaySetting == EDisplaySetting::Fullscreen)
            {
                ChangeDisplaySettings(NULL, 0);
                ShowCursor(TRUE);
            }
        }

        void CWindowWin::ChangeDisplayMode(EDisplaySetting a_Display, Vector2<int32> a_Size, Vector2<int32> a_Position)
        {
            DWORD   dwStyle;
            this->m_Description.DisplaySetting = a_Display;
            if (this->m_Description.DisplaySetting == EDisplaySetting::FullscreenWindowed)
            {
                dwStyle = WS_POPUPWINDOW;
                RECT desktop;
                const HWND hDesktop = GetDesktopWindow();
                GetWindowRect(hDesktop, &desktop);
                this->m_Description.X = -1;
                this->m_Description.Y = -1;
                this->m_Description.Width = desktop.right + 2;
                this->m_Description.Height = desktop.bottom + 2;
            }
            else if (this->m_Description.DisplaySetting == EDisplaySetting::Fullscreen)
            {
                DEVMODE dmScreenSettings;
                memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
                dmScreenSettings.dmSize = sizeof(dmScreenSettings);
                dmScreenSettings.dmPelsWidth = (unsigned long)1920;
                dmScreenSettings.dmPelsHeight = (unsigned long)1080;
                dmScreenSettings.dmBitsPerPel = 32;
                dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

                // Change the display settings to full screen.
                ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
                dwStyle = WS_POPUP;
                //set window to full
                RECT desktop;
                const HWND hDesktop = GetDesktopWindow();
                GetWindowRect(hDesktop, &desktop);
                this->m_Description.X = 0;
                this->m_Description.Y = 0;
                this->m_Description.Width = desktop.right;
                this->m_Description.Height = desktop.bottom;
            }
            else
            {
                this->m_Description.X = a_Position.X;
                this->m_Description.Y = a_Position.Y;
                this->m_Description.Width = a_Size.X;
                this->m_Description.Height = a_Size.Y;
                dwStyle = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
            }

            SetWindowLong(this->m_HWND, GWL_STYLE, dwStyle);
            //adjust the size
            MoveWindow(this->m_HWND, this->m_Description.X, this->m_Description.Y, this->m_Description.Width, this->m_Description.Height,true);

            SetWindowPos(this->m_HWND,0, this->m_Description.X, this->m_Description.Y, this->m_Description.Width, this->m_Description.Height, SWP_FRAMECHANGED | SWP_SHOWWINDOW);
            UpdateWindow(this->m_HWND);
            SetFocus(this->m_HWND);

            this->Update();
        }

        void CWindowWin::MakeDirectory(const char8* a_pDirectoryPath)
        {
            CreateDirectory(a_pDirectoryPath, NULL);
        }

        std::string CWindowWin::GetFileAtIndex(int32 a_Index, const char8* a_pDirectoryPath)
        {
            WIN32_FIND_DATA fileData;
            // Add * if it was not there before
            std::string path = a_pDirectoryPath;
            if (path[path.length() - 1] != '*')
                path += "*";

            HANDLE hFind = FindFirstFile(path.c_str(), &fileData);
            int32 index = 0;
            std::string returnValue = "";
            if (hFind != INVALID_HANDLE_VALUE)
            {
                returnValue = fileData.cFileName;
                while (index < 2||index-2 != a_Index)
                {
                    FindNextFile(hFind, &fileData);

                    if (returnValue == fileData.cFileName) //Don't go further than the index
                        returnValue = "";

                    else if (hFind != INVALID_HANDLE_VALUE) //If it is not invalid, set to new returnValue
                        returnValue = fileData.cFileName;
                    index++;
                }
            }
            FindClose(hFind);
            return returnValue;
        }

        SWindowDescription CWindowWin::GetDescription()
        {
            return this->m_Description;
        }

        void* CWindowWin::GetHandle()
        {
            return (void*)this->m_HWND;
        }

        void CWindowWin::Show()
        {
            ShowWindow(this->m_HWND, SW_NORMAL);
            UpdateWindow(this->m_HWND);
        }

        void CWindowWin::Hide()
        {
        }

        void CWindowWin::Update()
        {
            RECT clientRC,windowRC;
            //get the current client rect
            GetClientRect(this->m_HWND, &clientRC);
            GetWindowRect(this->m_HWND, &windowRC);
            //set Description to Client Size
            this->m_Description.Width = clientRC.right;
            this->m_Description.Height = clientRC.bottom;
            this->m_Description.X = windowRC.left;
            this->m_Description.Y = windowRC.top;
            //Set Cursor fixed to the screen
            if (GetForegroundWindow() == this->m_HWND)
            {
                RECT winRC;
                GetWindowRect(this->m_HWND, &winRC); //get the current window rect
                //Lock Cursor wthin the Window Boundaries
                if (this->m_Description.CursorInWindow)
                    ClipCursor(&winRC);
                else
                    ClipCursor(NULL);

                ShowCursor(this->m_Description.ShowCursor);
            }
            else
            {
                ShowCursor(true);
                ClipCursor(NULL);
            }
        }

    }
}
#endif
