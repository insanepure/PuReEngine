#include "include/PuReEngine/Font.h"

// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {

        // **************************************************************************
        // **************************************************************************

        CFont::CFont(IGraphics* a_pGraphics, const char8* a_pPath) : m_pGraphics(a_pGraphics)
        {
            this->m_pFont = new CSprite(a_pGraphics, a_pPath);

        }

        // **************************************************************************
        // **************************************************************************

        CFont::~CFont()
        {
            SAFE_DELETE(this->m_pFont);
        }

        // **************************************************************************
        // **************************************************************************

        void CFont::Draw(CCamera* a_pCam, IMaterial* a_pMaterial, const char8* a_Text)
        {
            Vector2<float32> textureSize = this->m_pFont->GetSize();
            for (uint32 i = 0; i < strlen(a_Text); i++)
            {
                char8 character = a_Text[i];
                Vector2<float32> UV_Size(textureSize.X / 16.0f, textureSize.Y / 16.0f);
                Vector2<float32> UV_Coord((character % 16) / 16.0f, (character / 16) / 16.0f);
                UV_Coord *= textureSize;
                Vector3<float32> Position(i*0.01f, 0.0f,1.0f);
                Vector3<float32> Size(0.01f, 0.01f, 1.0f);
                Vector3<float32> Rotation(0.0f, 0.0f, 0.0f);
                Vector3<float32> Center(0.0f, 0.0f, 0.0f);
                this->m_pFont->Draw(a_pCam, a_pMaterial, UV_Coord, UV_Size, Position, Size, Rotation, Center);
            }
        }

        // **************************************************************************
        // **************************************************************************

        void CFont::Draw(CCamera* a_pCam, IMaterial* a_pMaterial, const char8* a_pText, Vector3<float32> a_Position, Vector3<float32> a_Size, Vector3<float32> a_Rotation, float32 a_Offset,Color a_Color)
        {
            this->Draw(a_pCam,a_pMaterial,a_pText,a_Position,a_Size,Quaternion<float32>(a_Rotation).GetMatrix(),a_Offset,a_Color);
        }

        // **************************************************************************
        // **************************************************************************

        void CFont::Draw(CCamera* a_pCam, IMaterial* a_pMaterial, const char8* a_Text, Vector3<float32> a_Position, Vector3<float32> a_Size, Matrix<float32> a_Rotation, float32 a_Offset, Color a_Color)
        {
            Vector2<float32> textureSize = this->m_pFont->GetSize();
            Vector3<float32> Position = a_Position;
            for (uint32 i = 0; i < strlen(a_Text); i++)
            {
                char8 character = a_Text[i];
                Vector2<float32> UV_Size(textureSize.X / 16.0f, textureSize.Y / 16.0f);
                Vector2<float32> UV_Coord((character % 16) / 16.0f, (character / 16) / 16.0f);
                UV_Coord *= textureSize;
                Position.X += a_Offset;
                Vector3<float32> Center(0.0f, 0.0f, 0.0f);
                this->m_pFont->Draw(a_pCam, a_pMaterial, UV_Coord, UV_Size, Position, a_Size, a_Rotation, Center,a_Color);
            }
        }
    }
}