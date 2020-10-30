#include "include/PuReEngine/Sprite.h"
#include <SOIL.h>

// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {
        void CSprite::LoadTexture()
        {
            //lock it
            int32 channels;
            this->m_pPixels = SOIL_load_image(this->m_TexturePath.c_str(), &this->m_Width, &this->m_Height, &channels, SOIL_LOAD_RGBA);
            if (this->m_Width != 0 && this->m_Height != 0 && channels != 0)
                this->m_Loaded = true;
            else if (this->m_TexturePath != "")
                printf("File %s not found!\n", this->m_TexturePath.c_str());
        }

        // **************************************************************************
        // **************************************************************************

        CSprite::CSprite(CSprite& rhs)
        {
            this->m_pTexture = NULL;
            this->m_pQuadBuffer = NULL;
            *this = rhs;
        }


        // **************************************************************************
        // **************************************************************************

        CSprite& CSprite::operator=(CSprite& rhs)
        {
            //Delete this
            this->JoinThread();
            SAFE_DELETE(this->m_pTexture);
            SAFE_DELETE(this->m_pQuadBuffer);
            //Create new
            rhs.Update();
            this->m_TexturePath = rhs.m_TexturePath;
            this->m_pGraphics = rhs.m_pGraphics;
            STexture2DDescription tdesc = rhs.m_pTexture->GetDescription();
            this->m_Width = tdesc.Width;
            this->m_Height = tdesc.Height;
            this->m_pTexture = rhs.m_pGraphics->CreateTexture2D(tdesc);
            rhs.m_pTexture->Copy(this->m_pTexture,false);
            this->m_Ready = true;
            this->m_Loaded = true;
            return *this;
        }

        // **************************************************************************
        // **************************************************************************

        CSprite::CSprite(IGraphics* a_pGraphics,ITexture2D* a_pTexture, bool a_Rendertarget) : m_pGraphics(a_pGraphics)
        {
            this->m_pQuadBuffer = new Quad(a_pGraphics);
            STexture2DDescription tdesc = a_pTexture->GetDescription();
            this->m_Width = tdesc.Width;
            this->m_Height = tdesc.Height;
            tdesc.Bpp = 32;
            this->m_pTexture = a_pGraphics->CreateTexture2D(tdesc);
            a_pTexture->Copy(this->m_pTexture, a_Rendertarget);
            this->m_Ready = true;
            this->m_Loaded = true;
        }

        // **************************************************************************
        // **************************************************************************

        CSprite::CSprite(IGraphics* a_pGraphics, std::string a_Path) : m_pGraphics(a_pGraphics), m_TexturePath(a_Path)
        {
            this->m_pQuadBuffer = new Quad(a_pGraphics);
            this->m_pTexture = a_pGraphics->CreateTexture2D();
            //Set Threadsafe Variables
            this->m_Ready = false;
            this->m_Loaded = false;
            //Set Thread
            this->m_LoadThread = std::thread(&CSprite::LoadTexture, this);

        }

        void CSprite::Update()
        {
            if (!this->m_Ready&&this->m_Loaded)
            {
                this->m_pTexture->LoadTextureFromMemory(this->m_pPixels, this->m_Width, this->m_Height);
                SOIL_free_image_data(this->m_pPixels);
                this->m_Ready = true;
            }
        }


        // **************************************************************************
        // **************************************************************************

        CSprite::~CSprite()
        {
            this->JoinThread();
            SAFE_DELETE(this->m_pTexture);
            SAFE_DELETE(this->m_pQuadBuffer);
        }
        // **************************************************************************
        // **************************************************************************
        void CSprite::JoinThread()
        {
            if (this->m_LoadThread.joinable())
                this->m_LoadThread.join();
        }

        // **************************************************************************
        // **************************************************************************

        ITexture2D* CSprite::GetTexture()
        {
            this->Update();
            return this->m_pTexture;
        }

        // **************************************************************************
        // **************************************************************************

        Vector2<float32> CSprite::GetSize()
        {
            this->Update();
            STexture2DDescription desc = this->m_pTexture->GetDescription();
            return Vector2<float32>((float32)desc.Width, (float32)desc.Height);
        }

        // **************************************************************************
        // **************************************************************************

        void CSprite::Draw(CCamera* a_pCam, IMaterial* a_pMaterial)
        {
            Vector3<float32> Position = Vector3<float32>(0.0f, 0.0f, 0.0f);
            Vector3<float32> Scale = Vector3<float32>(1.0f, 1.0f, 1.0f);
            Vector3<float32> Rotation = Vector3<float32>(0.0f, 0.0f, 0.0f);
            Vector3<float32> Center = Vector3<float32>(0.0f, 0.0f, 0.0f);
            Vector2<float32> uvPosition = Vector2<float32>(0.0f, 0.0f);
            Vector2<float32> uvScale = Vector2<float32>((float32)this->m_Width, (float32)this->m_Height);
            this->Draw(a_pCam, a_pMaterial, uvPosition, uvScale, Position, Scale, Rotation, Center);;
        }

        // **************************************************************************
        // **************************************************************************

        void CSprite::DrawInstanced(CCamera* a_pCam, IMaterial* a_pMaterial, IInstanceBuffer* a_pInstanceBuffer)
        {
            Vector2<float32> uvPosition = Vector2<float32>(0.0f, 0.0f);
            Vector2<float32> uvScale = Vector2<float32>((float32)this->m_Width, (float32)this->m_Height);
            this->DrawInstanced(a_pCam, a_pMaterial, uvPosition, uvScale, a_pInstanceBuffer);
        }

        // **************************************************************************
        // **************************************************************************

        void CSprite::DrawInstanced(CCamera* a_pCam, IMaterial* a_pMaterial, Vector2<float32> a_UVPosition, Vector2<float32> a_UVSize, IInstanceBuffer* a_pInstanceBuffer)
        {
            this->Update();
            a_pMaterial->Apply();
            a_pCam->Apply(a_pMaterial);

            STexture2DDescription desc = this->m_pTexture->GetDescription();
            a_UVPosition = Vector2<float32>(a_UVPosition.X / desc.Width, a_UVPosition.Y / desc.Height);
            a_UVSize = Vector2<float32>(a_UVSize.X / desc.Width, a_UVSize.Y / desc.Height);

            a_pMaterial->SetVector2(a_UVPosition, "UVPosition");
            a_pMaterial->SetVector2(a_UVSize, "UVSize");

            a_pMaterial->SetTexture2D(this->m_pTexture, "Diffuse", 0);
            this->m_pGraphics->SetInstanceBuffer(this->m_pQuadBuffer->GetBuffer(), a_pInstanceBuffer);
            a_pMaterial->Apply();
            this->m_pGraphics->DrawInstanced(PuReEngine::Core::EPrimitive::Trianglestrip, this->m_pQuadBuffer->GetBuffer()->GetSize(), a_pInstanceBuffer->GetSize());
        }

        // **************************************************************************
        // **************************************************************************

        void CSprite::Draw(CCamera* a_pCam, IMaterial* a_pMaterial, Vector3<float32> a_Position, Vector3<float32> a_Size, Vector3<float32> a_Rotation, Vector3<float32> a_Center, Color a_Color)
        {
            Vector2<float32> uvPosition = Vector2<float32>(0.0f, 0.0f);
            Vector2<float32> uvScale = Vector2<float32>((float32)this->m_Width, (float32)this->m_Height);
            this->Draw(a_pCam, a_pMaterial, uvPosition, uvScale, a_Position, a_Size, Quaternion<float32>(a_Rotation).GetMatrix(), a_Center, a_Color);
        }

        // **************************************************************************
        // **************************************************************************

        void CSprite::Draw(CCamera* a_pCam, IMaterial* a_pMaterial, Vector3<float32> a_Position, Vector3<float32> a_Size, Matrix<float32> a_Rotation, Vector3<float32> a_Center, Color a_Color)
        {
            Vector2<float32> uvPosition = Vector2<float32>(0.0f, 0.0f);
            Vector2<float32> uvScale = Vector2<float32>((float32)this->m_Width, (float32)this->m_Height);
            this->Draw(a_pCam, a_pMaterial, uvPosition, uvScale, a_Position, a_Size, a_Rotation, a_Center,a_Color);
        }

        // **************************************************************************
        // **************************************************************************

        void CSprite::Draw(CCamera* a_pCam, IMaterial* a_pMaterial, Vector2<float32> a_UVPosition, Vector2<float32> a_UVSize, Vector3<float32> a_Position,
            Vector3<float32> a_Size, Vector3<float32> a_Rotation, Vector3<float32> a_Center, Color a_Color)
        {
            this->Draw(a_pCam, a_pMaterial, a_UVPosition, a_UVSize, a_Position, a_Size, Quaternion<float32>(a_Rotation).GetMatrix(),a_Center,a_Color);
        }

        // **************************************************************************
        // **************************************************************************

        void CSprite::Draw(CCamera* a_pCam, IMaterial* a_pMaterial, Vector2<float32> a_UVPosition, Vector2<float32> a_UVSize, Vector3<float32> a_Position,
            Vector3<float32> a_Size, Matrix<float32> a_Rotation, Vector3<float32> a_Center, Color a_Color)
        {
            this->Update();
            //because we start in the middle
            Vector3<float32> size = Vector3<float32>(a_Size.X, a_Size.Y, a_Size.Z);
            Vector3<float32> center = Vector3<float32>(a_Center.X, a_Center.Y, a_Center.Z);
            Vector3<float32> mCenter = Vector3<float32>(-center.X, -center.Y, -center.Z);

            Matrix<float32> rot = Matrix<float32>::Translation(mCenter)*a_Rotation*Matrix<float32>::Translation(center);
            Matrix<float32> scale = Matrix<float32>::Scale(size);
            Matrix<float32> translate = Matrix<float32>::Translation(a_Position);

            a_pMaterial->Apply();
            a_pCam->Apply(a_pMaterial);

            a_pMaterial->SetMatrix(scale, "Scale");
            a_pMaterial->SetMatrix(rot, "Rotation");
            a_pMaterial->SetMatrix(translate, "Translation");
            a_pMaterial->SetColor(a_Color,"Color");
            a_pMaterial->SetTexture2D(this->m_pTexture, "Diffuse", 0);

            STexture2DDescription desc = this->m_pTexture->GetDescription();
            a_UVPosition = Vector2<float32>(a_UVPosition.X / desc.Width, a_UVPosition.Y / desc.Height);
            a_UVSize = Vector2<float32>(a_UVSize.X / desc.Width, a_UVSize.Y / desc.Height);

            a_pMaterial->SetVector2(a_UVPosition, "UVPosition");
            a_pMaterial->SetVector2(a_UVSize, "UVSize");
            this->m_pGraphics->SetVertexBuffer(this->m_pQuadBuffer->GetBuffer());
            a_pMaterial->Apply();
            this->m_pGraphics->Draw(PuReEngine::Core::EPrimitive::Trianglestrip, 4);
        }
    }
}