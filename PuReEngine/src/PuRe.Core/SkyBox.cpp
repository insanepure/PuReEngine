#include "include/PuReEngine/SkyBox.h"
#include <SOIL.h>

// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {
        void CSkyBox::LoadTexture(std::string a_pPath)
        {
            //lock it
            int32 channels;
            bool loaded[6];
            bool allwork = true;
            for (int32 i = 0; i < 6; i++)
            {
                std::string file = a_pPath;
                //set path
                switch (i)
                {
                case 0:
                    file += "posx";
                    break;
                case 1:
                    file += "negx";
                    break;
                case 2:
                    file += "posy";
                    break;
                case 3:
                    file += "negy";
                    break;
                case 4:
                    file += "posz";
                    break;
                case 5:
                    file += "negz";
                    break;
                }

                channels = 0;
                loaded[i] = false;
                //First check if png exists
                std::string endpath = file + ".png";

                this->m_ppPixels[i] = SOIL_load_image(endpath.c_str(), &this->m_Width, &this->m_Height, &channels, SOIL_LOAD_RGBA);
                
                if (this->m_Width != 0 && this->m_Height != 0 && channels != 0)
                    loaded[i] = true;
                else
                {
                    //doesn't exist, test if jpg exists
                    endpath = file + ".jpg";
                    this->m_ppPixels[i] = SOIL_load_image(endpath.c_str(), &this->m_Width, &this->m_Height, &channels, SOIL_LOAD_RGBA);
                    if (this->m_Width != 0 && this->m_Height != 0 && channels != 0)
                        loaded[i] = true;
                    else
                    {
                        printf("File %s .jpg/.png not found!\n", file.c_str());
                        allwork = false;
                    }
                }
            }
            if (allwork)
                this->m_Loaded = true;
            else
            {
                for (int32 i = 0; i < 6; i++)
                {
                    if (loaded[i])
                        SOIL_free_image_data(this->m_ppPixels[i]);
                }
                SAFE_DELETE(this->m_ppPixels);
            }
        }

        // **************************************************************************
        // **************************************************************************

        CSkyBox::CSkyBox(IGraphics* a_pGraphics, std::string a_pPath) : m_pGraphics(a_pGraphics)
        {
            this->m_pQuad = new Quad(a_pGraphics);
            this->m_pTexture = a_pGraphics->CreateCubeMap();
            //Set Threadsafe Variables
            this->m_Ready = false;
            this->m_Loaded = false;
            //Set Thread

            int32 size = 6;
            this->m_ppPixels = new uint8*[size];
            this->m_LoadThread = std::thread(&CSkyBox::LoadTexture, this, a_pPath);

        }
        // **************************************************************************
        // **************************************************************************
        void CSkyBox::JoinThread()
        {
            if (this->m_LoadThread.joinable())
                this->m_LoadThread.join();
        }
        // **************************************************************************
        // **************************************************************************
        ITexture2D* CSkyBox::GetTexture()
        {
            return this->m_pTexture;
        }
        // **************************************************************************
        // **************************************************************************
        void CSkyBox::Update()
        {
            if (!this->m_Ready&&this->m_Loaded)
            {
                this->m_pTexture->CreateCubeMapFromMemory(this->m_ppPixels,this->m_Width,this->m_Height);
                for (int32 i = 0; i < 6; i++)
                    SOIL_free_image_data(this->m_ppPixels[i]);
                this->m_Ready = true;
                SAFE_DELETE(this->m_ppPixels);
            }
        }


        // **************************************************************************
        // **************************************************************************

        CSkyBox::~CSkyBox()
        {
            this->JoinThread();
            SAFE_DELETE(this->m_pTexture);
            SAFE_DELETE(this->m_pQuad);
        }

        // **************************************************************************
        // **************************************************************************

        void CSkyBox::Draw(CCamera* a_pCam, IMaterial* a_pMaterial, Vector3<float32> a_Rotation)
        {
            this->Draw(a_pCam, a_pMaterial, Quaternion<float32>(a_Rotation).GetMatrix());
        }

        // **************************************************************************
        // **************************************************************************

        void CSkyBox::Draw(CCamera* a_pCam, IMaterial* a_pMaterial, Matrix<float32> a_Rotation)
        {
            this->Update();

            this->m_pGraphics->SetCulling(false);

            a_pMaterial->Apply();
            a_pCam->Apply(a_pMaterial);


            Matrix<float32> rot = a_Rotation;
            Matrix<float32> scale = Matrix<float32>::Scale(Vector3<float32>(1.0f, 1.0f, 1.0f));
            Matrix<float32> translate = Matrix<float32>::Translation(a_pCam->GetPosition());
            Matrix<float32> InvertViewModel = a_pCam->GetView() *(translate * rot * scale);
            InvertViewModel.M41 = 0;
            InvertViewModel.M42 = 0;
            InvertViewModel.M43 = 0;
            InvertViewModel = Matrix<float32>::Invert(InvertViewModel);
            Matrix<float32> InvertProjection = Matrix<float32>::Invert(a_pCam->GetProjection());

            a_pMaterial->SetMatrix(InvertViewModel, "InvertViewModel");
            a_pMaterial->SetMatrix(InvertProjection, "InvertProjection");
            a_pMaterial->SetVector2(Vector2<float32>(0.0f, 0.0f), "UVPosition");
            a_pMaterial->SetVector2(Vector2<float32>(1.0f, 1.0f), "UVSize");
            a_pMaterial->SetCubeMap(this->m_pTexture, "Diffuse", 0);
            IVertexBuffer* buffer = this->m_pQuad->GetBuffer();
            this->m_pGraphics->SetVertexBuffer(buffer);
            a_pMaterial->Apply();
            this->m_pGraphics->Draw(PuReEngine::Core::EPrimitive::Trianglestrip, buffer->GetSize());

            this->m_pGraphics->SetCulling(true);
        }
    }
}