#define _CRT_SECURE_NO_WARNINGS
#include "include/BrickReader.h"
namespace Game
{
    CBrickReader::CBrickReader(std::string a_Path, PuRe_IWindow* a_pWindow)
    {
        this->BrickPath = a_Path;
        this->m_pWindow = a_pWindow;
        path = "../data/models/Models/brick/";
        std::string fileName = a_pWindow->GetFileAtIndex(this->m_Index, path.c_str());
        while (fileName.substr(fileName.find_last_of(".") + 1) != "obj")
        {
            this->m_Index++;
            fileName = a_pWindow->GetFileAtIndex(this->m_Index, path.c_str());
        }
        printf("Loading File: %s \n", fileName.c_str());

        fileName = path + fileName;
        this->currentFile = fileName;
        auto error = fopen_s(&this->file,(a_Path + "Brick.csv").c_str(), "w");
        error = 0;
        std::string text = "First Column has to be set!\n";
        fwrite(text.c_str(), sizeof(char), text.length(), this->file);
        text = "ID;File\n";
        fwrite(text.c_str(), sizeof(char), text.length(), this->file);
    }
    CBrickReader::~CBrickReader()
    {
        fclose(this->file);
    }
    void CBrickReader::Write(int RenderIndex)
    {
        bool writeout = true;
        if (writeout)
        {
            std::string text = std::to_string(RenderIndex) + ";" + this->m_pWindow->GetFileAtIndex(this->m_Index, path.c_str()) + "\n";
            fwrite(text.c_str(), sizeof(char), text.length(), this->file);

        }
    }
    bool CBrickReader::Next(int& RenderIndex)
    {
        if (this->category == 0 && RenderIndex == 26)
        {
            path = "../data/models/Models/bow bricks/";
            this->m_Index = -1;
            this->category = 1;
            RenderIndex = (this->category * 100);
        }
        else if (this->category == 1 && RenderIndex == 117)
        {
            path = "../data/models/Models/Cockpits/";
            this->m_Index = -1;
            this->category = 2;
            RenderIndex = (this->category * 100);
        }
        else if (this->category == 2 && RenderIndex == 205)
        {
            path = "../data/models/Models/Plates/";
            this->m_Index = -1;
            this->category = 3;
            RenderIndex = (this->category * 100);
        }
        else if (this->category == 3 && RenderIndex == 351)
        {
            path = "../data/models/Models/Roof bricks/";
            this->m_Index = -1;
            this->category = 4;
            RenderIndex = (this->category * 100);
        }
        else if (this->category == 4 && RenderIndex == 421)
        {
            path = "../data/models/Models/Special/";
            this->m_Index = -1;
            this->category = 5;
            RenderIndex = (this->category * 100);
        }
        else if (this->category == 5 && RenderIndex == 527)
        {
            path = "../data/models/Models/Wall Elements/";
            this->m_Index = -1;
            this->category = 6;
            RenderIndex = (this->category * 100);
        }
        else if (this->category == 6 && RenderIndex == 607)
        {
            path = "../data/models/Models/Engine/";
            this->m_Index = -1;
            this->category = 7;
            RenderIndex = (this->category * 100);
        }
        else if (this->category == 7 && RenderIndex == 703)
        {
            path = "../data/models/Models/Weapons/";
            this->m_Index = -1;
            this->category = 8;
            RenderIndex = (this->category * 100);
        }

        int startindex = this->m_Index;

        this->m_Index++;
        std::string fileName = this->m_pWindow->GetFileAtIndex(this->m_Index, path.c_str());
        while (fileName.substr(fileName.find_last_of(".") + 1) != "obj")
        {
            this->m_Index++;
            fileName = this->m_pWindow->GetFileAtIndex(this->m_Index, path.c_str());
            if (fileName == "")
            {
                this->m_Index = startindex;
                break;
            }
        }
        if (fileName != "")
        {
            printf("Loading File: %s \n", fileName.c_str());
            fileName = path + fileName;
            this->currentFile = fileName;
            return true;
        }
        return false;
    }
}