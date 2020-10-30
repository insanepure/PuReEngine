#include "include/PuReEngine/DirectX10/InstanceBuffer.h"

namespace PuReEngine
{
    namespace Graphics
    {
        namespace DirectX10
        {
            // **************************************************************************
            // **************************************************************************
            CInstanceBuffer::CInstanceBuffer(ID3D10Device* a_pDevice, int32 a_Size, int32 a_Stride)
            {
                this->m_pDevice = a_pDevice;
                this->m_Size = a_Size;
                this->m_Stride = a_Stride;

                D3D10_BUFFER_DESC description;
                description.ByteWidth = a_Size*a_Stride;
                description.BindFlags = D3D10_BIND_VERTEX_BUFFER;
                description.Usage = D3D10_USAGE_DYNAMIC;
                description.MiscFlags = 0;
                description.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;

                this->m_pDevice->CreateBuffer(&description, 0, &this->m_pBuffer);
            }

            // **************************************************************************
            // **************************************************************************
            CInstanceBuffer::~CInstanceBuffer()
            {
                SAFE_RELEASE(this->m_pBuffer);
            }

            // **************************************************************************
            // **************************************************************************
            int32 CInstanceBuffer::GetSize()
            {
                return this->m_Size;
            }

            // **************************************************************************
            // **************************************************************************
            int32 CInstanceBuffer::GetStride()
            {
                return this->m_Stride;
            }

            // **************************************************************************
            // **************************************************************************
            void* CInstanceBuffer::GetData()
            {
                return this->m_pBuffer;
            }

            // **************************************************************************
            // **************************************************************************
            void* CInstanceBuffer::Lock()
            {
                void* data;

                this->m_pBuffer->Map(D3D10_MAP_WRITE_DISCARD, NULL, &data);

                return data;
            }

            // **************************************************************************
            // **************************************************************************
            void CInstanceBuffer::Unlock()
            {
                this->m_pBuffer->Unmap();
            }

        }
    }
}