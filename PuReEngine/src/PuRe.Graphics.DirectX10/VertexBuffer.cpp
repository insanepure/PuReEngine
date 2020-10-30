#include "include/PuReEngine/DirectX10/VertexBuffer.h"

namespace PuReEngine
{
    namespace Graphics
    {
        namespace DirectX10
        {

            // **************************************************************************
            // **************************************************************************
            CVertexBuffer::CVertexBuffer(ID3D10Device* m_pDevice, int32 a_Size, int32 a_Stride)
            {
                this->m_pDevice = m_pDevice;
                this->m_Size = a_Size;
                this->m_Stride = a_Stride;

                D3D10_BUFFER_DESC description;
                description.ByteWidth = a_Size;
                description.BindFlags = D3D10_BIND_VERTEX_BUFFER;
                description.Usage = D3D10_USAGE_DYNAMIC;
                description.MiscFlags = 0;
                description.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;

                this->m_pDevice->CreateBuffer(&description, 0, &this->m_pBuffer);
            }

            // **************************************************************************
            // **************************************************************************
            CVertexBuffer::~CVertexBuffer()
            {
                SAFE_RELEASE(this->m_pBuffer);
            }

            // **************************************************************************
            // **************************************************************************
            int32 CVertexBuffer::GetSize()
            {
                return this->m_Size / this->m_Stride;
            }

            // **************************************************************************
            // **************************************************************************
            int32 CVertexBuffer::GetStride()
            {
                return this->m_Stride;
            }

            // **************************************************************************
            // **************************************************************************
            void* CVertexBuffer::GetData()
            {
                return this->m_pBuffer;
            }

            // **************************************************************************
            // **************************************************************************
            void* CVertexBuffer::Lock()
            {
                void* data;

                this->m_pBuffer->Map(D3D10_MAP_WRITE_DISCARD, NULL, &data);

                return data;
            }

            // **************************************************************************
            // **************************************************************************
            void CVertexBuffer::Unlock()
            {
                this->m_pBuffer->Unmap();
            }

            // **************************************************************************
            // **************************************************************************
            SVertex* CVertexBuffer::GetVertices()
            {
                D3D10_BUFFER_DESC description;
                ID3D10Buffer* readBuffer;
                description.ByteWidth = this->m_Size;
                description.BindFlags = 0;
                description.Usage = D3D10_USAGE_STAGING;
                description.MiscFlags = 0;
                description.CPUAccessFlags = D3D10_CPU_ACCESS_READ;

                this->m_pDevice->CreateBuffer(&description, 0, &readBuffer);
                //copy data from write buffer to read buffer
                this->m_pDevice->CopyResource(readBuffer, this->m_pBuffer);

                void* pdata;

                readBuffer->Map(D3D10_MAP_READ, NULL, &pdata);

                SVertex* data = new SVertex[this->m_Size];
                memcpy(data, pdata, this->m_Size);

                readBuffer->Unmap();
                SAFE_RELEASE(readBuffer);

                return data;
            }

        }
    }
}