#include "include/PuReEngine/DirectX11/IndexBuffer.h"

namespace PuReEngine
{
    namespace Graphics
    {
        namespace DirectX11
        {

            // **************************************************************************
            // **************************************************************************
            CIndexBuffer::CIndexBuffer(ID3D11Device* a_pDevice, ID3D11DeviceContext* a_pDeviceContext, int32 a_Size)
            {
                this->m_pDevice = a_pDevice;
                this->m_pDeviceContext = a_pDeviceContext;
                this->m_Size = a_Size;

                D3D11_BUFFER_DESC description;
                description.ByteWidth = a_Size;
                description.BindFlags = D3D11_BIND_INDEX_BUFFER;
                description.Usage = D3D11_USAGE_DYNAMIC;
                description.MiscFlags = 0;
                description.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

                this->m_pDevice->CreateBuffer(&description, 0, &this->m_pBuffer);
            }

            // **************************************************************************
            // **************************************************************************
            CIndexBuffer::~CIndexBuffer()
            {
                SAFE_RELEASE(this->m_pBuffer);
            }

            // **************************************************************************
            // **************************************************************************
            int32 CIndexBuffer::GetSize()
            {
                return this->m_Size;
            }

            // **************************************************************************
            // **************************************************************************
            void* CIndexBuffer::GetData()
            {
                return this->m_pBuffer;
            }

            // **************************************************************************
            // **************************************************************************
            void* CIndexBuffer::Lock()
            {
                D3D11_MAPPED_SUBRESOURCE* pdata = new D3D11_MAPPED_SUBRESOURCE();
                this->m_pDeviceContext->Map(this->m_pBuffer, 0, D3D11_MAP_WRITE_DISCARD, NULL, pdata);

                return pdata->pData;
            }

            // **************************************************************************
            // **************************************************************************
            void CIndexBuffer::Unlock()
            {
                this->m_pDeviceContext->Unmap(this->m_pBuffer, 0);
            }

        }
    }
}