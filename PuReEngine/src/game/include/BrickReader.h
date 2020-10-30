#ifndef _BRICKREADER_H_
#define _BRICKREADER_H_

// Framework specific includes
#include <PuReEngine/Core.h>
#include <PuReEngine/Defines.h>
#include <math.h>
#include <algorithm>
#include <cstring>

// Declare namespace Game
namespace Game
{
    class CBrickReader 
    {
    public:
        std::string currentFile;
        std::string BrickPath;
        FILE* file;
        std::string csv;
        std::string path;
        PuRe_IWindow* m_pWindow;
        int m_Index;
        int category = 0;
    public:
        CBrickReader(std::string a_Path,PuRe_IWindow* a_pWindow);
        ~CBrickReader();
    public:
        void Write(int RenderIndex);
        bool Next(int& RenderIndex);
    };
}
#endif /* _BRICKREADER_H_*/