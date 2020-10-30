#include "include/PuReEngine/Quad.h"

// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {

        // **************************************************************************
        // **************************************************************************

        Quad::Quad(IGraphics* a_pGraphics) : m_pGraphics(a_pGraphics)
        {
            int stride = sizeof(SVertex);
            this->m_pVertexBuffer = this->m_pGraphics->CreateVertexBuffer(stride * 4, stride); //5 Floats (3 Position, 2 UV) * 4 Vertices
            //Lock it
            SVertex* pdata = (SVertex*)this->m_pVertexBuffer->Lock();
            //copy data into it
            this->GetVertices(pdata);
            //unlock it
            this->m_pVertexBuffer->Unlock();
        }

        // **************************************************************************
        // **************************************************************************

        Quad::~Quad()
        {
            SAFE_DELETE(this->m_pVertexBuffer);
        }

        // **************************************************************************
        // **************************************************************************

        void Quad::GetVertices(SVertex* a_pVertex)
        {
            a_pVertex[0].Position = Vector3<float32>(-1.0f, 1.0f, 0.0f);
            a_pVertex[0].Color = Vector3<float32>(1.0f, 0.0f, 0.0f);
            a_pVertex[0].UV = Vector2<float32>(0.0f, 0.0f);
            a_pVertex[0].Normal = Vector3<float32>(0.0f, 0.0f, -1.0f);

            a_pVertex[1].Position = Vector3<float32>(1.0f, 1.0f, 0.0f);
            a_pVertex[1].Color = Vector3<float32>(0.0f, 1.0f, 0.0f);
            a_pVertex[1].UV = Vector2<float32>(1.0f, 0.0f);
            a_pVertex[1].Normal = Vector3<float32>(0.0f, 0.0f, -1.0f);

            a_pVertex[2].Position = Vector3<float32>(-1.0f, -1.0f, 0.0f);
            a_pVertex[2].Color = Vector3<float32>(0.0f, 0.0f, 1.0f);
            a_pVertex[2].UV = Vector2<float32>(0.0f, 1.0f);
            a_pVertex[2].Normal = Vector3<float32>(0.0f, 0.0f, -1.0f);

            a_pVertex[3].Position = Vector3<float32>(1.0f, -1.0f, 0.0f);
            a_pVertex[3].Color = Vector3<float32>(1.0f, 1.0f, 1.0f);
            a_pVertex[3].UV = Vector2<float32>(1.0f, 1.0f);
            a_pVertex[3].Normal = Vector3<float32>(0.0f, 0.0f, -1.0f);
        }

        // **************************************************************************
        // **************************************************************************

        IVertexBuffer* Quad::GetBuffer()
        {
            return this->m_pVertexBuffer;
        }
    }
}