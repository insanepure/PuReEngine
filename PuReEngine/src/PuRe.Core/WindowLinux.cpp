#include "include/PuReEngine/WindowLinux.h"
#ifdef __linux__
#include <X11/Xlib.h>
namespace PuReEngine 
{
    namespace Core 
    {

        CWindowLinux::CWindowLinux(WindowDescription& a_rDescription)
        {
            this->m_Description = a_rDescription;
            this->m_IsVisible = false;
            this->m_pDisplay = XOpenDisplay(NULL);

            this->hwnd = XCreateSimpleWindow(this->m_pDisplay,XRootWindow(this->m_pDisplay,0),
            this->m_Description.X,m_Description.Y,this->m_Description.Width,this->m_Description.Height,5,0,0);
            XMoveWindow(this->m_pDisplay,this->hwnd,description.X,description.Y);

            if (this->m_Description.Fullscreen)
            {

            }


            XStoreName(this->m_pDisplay,this->m_HWND,this->m_Description.Title);
            XMapWindow(this->m_pDisplay,this->m_HWND);
            XFlush(this->m_pDisplay);
        }

        CWindowLinux::~CWindowLinux()
        {
            if (this->m_Description.Fullscreen)
            {
            }
        }

        void CWindowLinux::MakeDirectory(const char8* a_pDirectoryPath)
        {
            mkdir(a_pDirectoryPath, 777);
        }

        std::string CWindowWin::GetFileAtIndex(int32 a_Index, const char8* a_pDirectoryPath)
        {
            DIR* dirp = opendir(a_pDirectoryPath);
            dirent* dp = readdir(dirp);
            int32 index = 0;
            std::string returnValue = "";
            if (dp != NULL)
            {
                while (index < 2||index-2 != a_Index)
                {
                    dp = readdir(dirp);

                    if (returnValue == dp->d_name) //Don't go further than the index
                        returnValue = "";

                    else if (dp != NULL) //If it is not invalid, set to new returnValue
                        returnValue = dp->d_name;
                    index++;
                }
            }
            return returnValue;
        }

        SWindowDescription CWindowLinux::GetDescription()
        {
            return this->description;
        }

        void* CWindowLinux::GetHandle()
        {
            return (void*)this->hdisplay;
        }

        void CWindowLinux::Show()
        {
        }

        void CWindowLinux::Hide()
        {
        }

        void CWindowLinux::Update()
        {
        }

    }
}
#endif