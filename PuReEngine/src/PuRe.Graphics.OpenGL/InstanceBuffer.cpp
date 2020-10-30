#include "include/PuReEngine/OpenGL/InstanceBuffer.h"

namespace PuReEngine
{
    namespace Graphics
    {
        namespace OpenGL
        {

            // **************************************************************************
            // **************************************************************************
            CInstanceBuffer::CInstanceBuffer(int32 a_Size, int32 a_Stride)
            {
                this->m_Size = a_Size;
                this->m_Stride = a_Stride;
                this->m_pData = NULL;

                glGenBuffers(1, &this->m_Buffer);

                glGenVertexArrays(1, &this->m_VertexArray);
                glBindVertexArray(this->m_VertexArray);


            }

            // **************************************************************************
            // **************************************************************************
            CInstanceBuffer::~CInstanceBuffer()
            {
                SAFE_DELETE(this->m_pData);
                this->m_pData = NULL;
                glDeleteBuffers(1, &this->m_Buffer);
                glDeleteVertexArrays(1, &this->m_VertexArray);
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
                return (void*)this->m_Buffer;
            }

            // **************************************************************************
            // **************************************************************************
            void* CInstanceBuffer::Lock()
            {
                this->m_pData = new SInstance[this->m_Size];
                glBindBuffer(GL_ARRAY_BUFFER, this->m_Buffer);
                return m_pData;
            }

            // **************************************************************************
            // **************************************************************************
            void CInstanceBuffer::Unlock()
            {
                glBufferData(GL_ARRAY_BUFFER, this->m_Size * sizeof(SInstance), &this->m_pData[0], GL_STATIC_DRAW);
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                SAFE_DELETE(this->m_pData);
                this->m_pData = NULL;
            }

        }
    }
}