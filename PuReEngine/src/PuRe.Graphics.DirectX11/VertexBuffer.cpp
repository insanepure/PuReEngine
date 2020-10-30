#include "include/PuReEngine/DirectX11/VertexBuffer.h"

namespace PuReEngine
{
    namespace Graphics
    {
        namespace DirectX11
        {
            // **************************************************************************
            // **************************************************************************
            CVertexBuffer::CVertexBuffer(ID3D11Device* a_pDevice, ID3D11DeviceContext* a_pDeviceContext, int32 a_Size, int32 a_Stride)
            {
                this->m_pDevice = a_pDevice;
                this->m_pDeviceContext = a_pDeviceContext;
                this->m_Size = a_Size;
                this->m_Stride = a_Stride;

                D3D11_BUFFER_DESC description;
                description.ByteWidth = a_Size;
                description.BindFlags = D3D11_BIND_VERTEX_BUFFER;
                description.Usage = D3D11_USAGE_DYNAMIC;
                description.MiscFlags = 0;
                description.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

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
                return this->m_Size/this->m_Stride;
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
                D3D11_MAPPED_SUBRESOURCE pdata;
                this->m_pDeviceContext->Map(this->m_pBuffer, 0, D3D11_MAP_WRITE_DISCARD, NULL, &pdata);

                return pdata.pData;
            }

            // **************************************************************************
            // **************************************************************************
            void CVertexBuffer::Unlock()
            {
                this->m_pDeviceContext->Unmap(this->m_pBuffer, 0);
            }

            // **************************************************************************
            // **************************************************************************
            SVertex* CVertexBuffer::GetVertices()
            {
                D3D11_BUFFER_DESC description;
                ID3D11Buffer* readBuffer;
                description.ByteWidth = this->m_Size;
                description.BindFlags = 0;
                description.Usage = D3D11_USAGE_STAGING;
                description.MiscFlags = 0;
                description.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

                this->m_pDevice->CreateBuffer(&description, 0, &readBuffer);
                //copy data from write buffer to read buffer
                this->m_pDeviceContext->CopyResource(readBuffer, this->m_pBuffer);

                D3D11_MAPPED_SUBRESOURCE pdata;
                this->m_pDeviceContext->Map(readBuffer, 0, D3D11_MAP_READ, NULL, &pdata);

                SVertex* data = new SVertex[this->m_Size];
                memcpy(data, pdata.pData, this->m_Size);

                this->m_pDeviceContext->Unmap(readBuffer, 0);
                SAFE_RELEASE(readBuffer);

                return data;
            }

        }
    }
}