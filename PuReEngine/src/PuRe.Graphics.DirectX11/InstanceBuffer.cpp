#include "include/PuReEngine/DirectX11/InstanceBuffer.h"

namespace PuReEngine
{
    namespace Graphics
    {
        namespace DirectX11
        {
            // **************************************************************************
            // **************************************************************************
            CInstanceBuffer::CInstanceBuffer(ID3D11Device* a_pDevice, ID3D11DeviceContext* a_pDeviceContext, int32 a_Size, int32 a_Stride)
            {
                this->m_pDevice = a_pDevice;
                this->m_pDeviceContext = a_pDeviceContext;
                this->m_Size = a_Size;
                this->m_Stride = a_Stride;

                D3D11_BUFFER_DESC description;
                description.ByteWidth = a_Size*a_Stride;
                description.BindFlags = D3D11_BIND_VERTEX_BUFFER;
                description.Usage = D3D11_USAGE_DYNAMIC;
                description.MiscFlags = 0;
                description.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

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
                D3D11_MAPPED_SUBRESOURCE pdata;
                this->m_pDeviceContext->Map(this->m_pBuffer, 0, D3D11_MAP_WRITE_DISCARD, NULL, &pdata);

                return pdata.pData;
            }

            // **************************************************************************
            // **************************************************************************
            void CInstanceBuffer::Unlock()
            {
                this->m_pDeviceContext->Unmap(this->m_pBuffer, 0);
            }

        }
    }
}