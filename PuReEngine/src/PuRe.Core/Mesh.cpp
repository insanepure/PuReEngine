#define _CRT_SECURE_NO_WARNINGS
#include "include/PuReEngine/Mesh.h"
#include <SOIL.h>

// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {

        // **************************************************************************
        // **************************************************************************

        CMesh::CMesh()
        {
            this->m_pVertexBuffer = nullptr;
            this->m_pTexture = nullptr;
        }

        // **************************************************************************
        // **************************************************************************

        CMesh::~CMesh()
        {
            this->JoinThread();
            SAFE_DELETE(this->m_pVertexBuffer);
            SAFE_DELETE(this->m_pIndexBuffer);
            SAFE_DELETE(this->m_pTexture);
        }
        // **************************************************************************
        // **************************************************************************
        void CMesh::JoinThread()
        {
            if (this->m_LoadThread.joinable())
                this->m_LoadThread.join();
        }
        // **************************************************************************
        // **************************************************************************

        IVertexBuffer* CMesh::GetVertices()
        {
            return this->m_pVertexBuffer;
        }

        // **************************************************************************
        // **************************************************************************

        ITexture2D* CMesh::GetTexture()
        {
            this->Update();
            return this->m_pTexture;
        }

        // **************************************************************************
        // **************************************************************************

        void CMesh::SetGraphic(IGraphics* a_pGraphics)
        {
            this->m_pGraphics = a_pGraphics;
        }

        // **************************************************************************
        // **************************************************************************

        void CMesh::SetVertexBuffer(SVertex* a_pVertices, int32 a_Size)
        {
            this->m_pVertexBuffer = this->m_pGraphics->CreateVertexBuffer(a_Size*sizeof(SVertex), sizeof(SVertex));
            SVertex* vdata = (SVertex*)this->m_pVertexBuffer->Lock();
            memcpy(vdata, a_pVertices, a_Size*sizeof(SVertex));
            this->m_pVertexBuffer->Unlock();
        }

        // **************************************************************************
        // **************************************************************************

        void CMesh::SetIndexBuffer(int32* a_pIndices, int32 a_Size)
        {
            this->m_pIndexBuffer = this->m_pGraphics->CreateIndexBuffer(a_Size);
            int32* vdata = (int32*)this->m_pIndexBuffer->Lock();
            memcpy(vdata, a_pIndices, a_Size*sizeof(int32));
            this->m_pIndexBuffer->Unlock();
        }

        // **************************************************************************
        // **************************************************************************

        void CMesh::SetTexture(std::string a_Path)
        {
            this->m_TexturePath = a_Path;
            //Create Texture
            this->m_pTexture = this->m_pGraphics->CreateTexture2D();
            //Set Threadsafe Variables
            this->m_Ready = false;
            this->m_Loaded = false;
            if (a_Path != "")
            {
                //Set Thread
                this->m_LoadThread = std::thread(&CMesh::LoadTexture, this);
            }
        }

        void CMesh::LoadTexture()
        {
            //lock it
            int32 channels;
            this->m_pPixels = SOIL_load_image(this->m_TexturePath.c_str(), &this->m_Width, &this->m_Height, &channels, SOIL_LOAD_RGBA);
            if (this->m_Width != 0 && this->m_Height != 0 && channels != 0)
                this->m_Loaded = true;
            else if (this->m_TexturePath != "")
                printf("File %s not found!\n", this->m_TexturePath.c_str());
        }

        void CMesh::Update()
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

        void CMesh::DrawInstanced(CCamera* a_pCamera, IMaterial* a_pMaterial, EPrimitive a_Primitive, IInstanceBuffer* a_pInstanceBuffer)
        {
            this->Update();
            a_pMaterial->Apply();
            a_pCamera->Apply(a_pMaterial);
            a_pMaterial->SetTexture2D(this->m_pTexture, "Diffuse", 0);
            this->m_pGraphics->SetInstanceBuffer(this->m_pVertexBuffer, a_pInstanceBuffer);
            a_pMaterial->Apply();
            this->m_pGraphics->DrawInstanced(a_Primitive, this->m_pVertexBuffer->GetSize(), a_pInstanceBuffer->GetSize());
        }

        // **************************************************************************
        // **************************************************************************

        void CMesh::Draw(CCamera* a_pCamera, IMaterial* a_pMaterial, EPrimitive a_Primitive, Vector3<float32> a_Position, Vector3<float32> a_Size, Vector3<float32> a_Rotation, Vector3<float32> a_Center, Color a_Color)
        {
            this->Draw(a_pCamera, a_pMaterial, a_Primitive, a_Position, a_Size, Quaternion<float32>(a_Rotation).GetMatrix(),a_Center,a_Color);
        }

        // **************************************************************************
        // **************************************************************************

        void CMesh::Draw(CCamera* a_pCamera, IMaterial* a_pMaterial, EPrimitive a_Primitive, Vector3<float32> a_Position, Vector3<float32> a_Size, Matrix<float32> a_Rotation, Vector3<float32> a_Center, Color a_Color)
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
            a_pCamera->Apply(a_pMaterial);
            a_pMaterial->SetMatrix(scale, "Scale");
            a_pMaterial->SetMatrix(rot, "Rotation");
            a_pMaterial->SetMatrix(translate, "Translation");
            a_pMaterial->SetColor(a_Color, "Color");
            a_pMaterial->SetTexture2D(this->m_pTexture, "Diffuse", 0);
            this->m_pGraphics->SetVertexBuffer(this->m_pVertexBuffer);
            if (this->m_pIndexBuffer != NULL)
                this->m_pGraphics->SetIndexBuffer(this->m_pIndexBuffer);
            a_pMaterial->Apply();
            if (this->m_pIndexBuffer != NULL)
                this->m_pGraphics->DrawIndexed(a_Primitive, this->m_pIndexBuffer->GetSize());
            else
                this->m_pGraphics->Draw(a_Primitive, this->m_pVertexBuffer->GetSize());
        }

    }
}