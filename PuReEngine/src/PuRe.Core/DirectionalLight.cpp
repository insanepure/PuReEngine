#include "include/PuReEngine/DirectionalLight.h"

// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {
        // **************************************************************************
        // **************************************************************************

        CDirectionalLight::CDirectionalLight(IGraphics* a_pGraphics)
        {
            this->m_pQuad = new Quad(a_pGraphics);
        }

        // **************************************************************************
        // **************************************************************************

        CDirectionalLight::~CDirectionalLight()
        {
            SAFE_DELETE(this->m_pQuad);
        }

        // **************************************************************************
        // **************************************************************************

        void CDirectionalLight::Draw(IGraphics* a_pGraphics, IMaterial* a_pMaterial, CCamera* a_pViewCamera, CCamera* a_pPostCamera, IRendertarget* a_pRendertarget)
        {
            this->Draw(a_pGraphics, a_pMaterial, a_pViewCamera, a_pPostCamera, a_pRendertarget, Vector3<float32>(1.0f, 0.0f, 0.0f), Color(1, 0, 0, 1));
        }

        // **************************************************************************
        // **************************************************************************

        void CDirectionalLight::Draw(IGraphics* a_pGraphics, IMaterial* a_pMaterial, CCamera* a_pViewCamera, CCamera* a_pPostCamera, IRendertarget* a_pRendertarget, Vector3<float32> a_Direction, Color a_Color)
        {
            STexture2DDescription desc = a_pRendertarget->GetTexture2D(0)->GetDescription();
            a_pMaterial->Apply();
            a_pPostCamera->Apply(a_pMaterial);
            a_pViewCamera->Update();
            Matrix<float32> InvertViewProjection = a_pViewCamera->GetInvertViewProjection();
            a_pMaterial->SetMatrix(InvertViewProjection, "InvertViewProjection");
            a_pMaterial->SetVector3(a_pViewCamera->GetPosition(), "CameraPosition");
            a_pMaterial->SetVector3(a_Direction, "LightDirection");
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