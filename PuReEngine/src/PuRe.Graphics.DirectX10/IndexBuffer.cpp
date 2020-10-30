#include "include/PuReEngine/DirectX10/IndexBuffer.h"

namespace PuReEngine
{
    namespace Graphics
    {
        namespace DirectX10
        {

            // **************************************************************************
            // **************************************************************************
            CIndexBuffer::CIndexBuffer(ID3D10Device* a_pDevice, int32 a_Size)
            {
                this->m_pDevice = a_pDevice;
                this->m_Size = a_Size;

                D3D10_BUFFER_DESC description;
                description.ByteWidth = a_Size;
                description.BindFlags = D3D10_BIND_INDEX_BUFFER;
                description.Usage = D3D10_USAGE_DYNAMIC;
                description.MiscFlags = 0;
                description.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;

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
                void* pdata;

                this->m_pBuffer->Map(D3D10_MAP_WRITE_DISCARD, NULL, &pdata);

                return pdata;
            }

            // **************************************************************************
            // **************************************************************************
            void CIndexBuffer::Unlock()
            {
                this->m_pBuffer->Unmap();
            }

        }
    }
}