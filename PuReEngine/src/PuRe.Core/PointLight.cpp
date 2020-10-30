#include "include/PuReEngine/PointLight.h"

// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {
        // **************************************************************************
        // **************************************************************************

        CPointLight::CPointLight(IGraphics* a_pGraphics)
        {
            this->m_pQuad = new Quad(a_pGraphics);
        }

        // **************************************************************************
        // **************************************************************************

        CPointLight::~CPointLight()
        {
            SAFE_DELETE(this->m_pQuad);
        }

        // **************************************************************************
        // **************************************************************************

        void CPointLight::Draw(IGraphics* a_pGraphics, IMaterial* a_pMaterial, CCamera* a_pViewCamera, CCamera* a_pPostCamera, IRendertarget* a_pRendertarget, Vector3<float32> a_Position, Color a_Color, float32 a_Radius, float32 a_Intensity)
        {
            STexture2DDescription desc = a_pRendertarget->GetTexture2D(0)->GetDescription();
            a_pMaterial->Apply();
            a_pPostCamera->Apply(a_pMaterial);
            a_pViewCamera->Update();
            Matrix<float32> InvertViewProjection = a_pViewCamera->GetInvertViewProjection();
            a_pMaterial->SetMatrix(InvertViewProjection, "InvertViewProjection");
            a_pMaterial->SetFloat(a_Intensity, "LightIntensity");
            a_pMaterial->SetFloat(a_Radius, "LightRadius");
            a_pMaterial->SetVector3(a_Position, "LightPos");
            a_pMaterial->SetColor(a_Color, "LightColor");
            a_pMaterial->SetVector2(Vector2<float32>((float32)desc.Width, (float32)desc.Height), "Resolution");
            a_pMaterial->SetTexture2D(a_pRendertarget->GetTexture2D(1), "NormalMap", 1);
            a_pMaterial->SetTexture2D(a_pRendertarget->GetTexture2D(4), "DepthMap", 2);
            IVertexBuffer* buffer = this->m_pQuad->GetBuffer();
            a_pGraphics->SetVertexBuffer(buffer);
            a_pMaterial->Apply();
            a_pGraphics->Draw(PuReEngine::Core::EPrimitive::Trianglestrip, buffer->GetSize());
        }
    }
}