#include "include/PuReEngine/OpenGL/IndexBuffer.h"

namespace PuReEngine
{
    namespace Graphics
    {
        namespace OpenGL
        {

            // **************************************************************************
            // **************************************************************************
            CIndexBuffer::CIndexBuffer(int32 a_Size)
            {
                this->m_Size = a_Size;
                this->m_pData = NULL;

                glGenBuffers(1, &this->m_Buffer);

            }

            // **************************************************************************
            // **************************************************************************
            CIndexBuffer::~CIndexBuffer()
            {
                SAFE_DELETE(this->m_pData);
                this->m_pData = NULL;
                glDeleteBuffers(1, &this->m_Buffer);
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
                return (void*)this->m_Buffer;
            }

            // **************************************************************************
            // **************************************************************************
            void* CIndexBuffer::Lock()
            {
                this->m_pData = new uint32[this->m_Size];
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_Buffer);
                return this->m_pData;
            }

            // **************************************************************************
            // **************************************************************************
            void CIndexBuffer::Unlock()
            {
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->m_Size * sizeof(uint32), &this->m_pData[0], GL_STATIC_DRAW);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
                SAFE_DELETE(this->m_pData);
                this->m_pData = NULL;
            }

        }
    }
}