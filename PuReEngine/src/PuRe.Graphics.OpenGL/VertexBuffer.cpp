#include "include/PuReEngine/OpenGL/VertexBuffer.h"

namespace PuReEngine
{
    namespace Graphics
    {
        namespace OpenGL
        {

            // **************************************************************************
            // **************************************************************************
            CVertexBuffer::CVertexBuffer(int32 a_Size, int32 a_Stride)
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
            CVertexBuffer::~CVertexBuffer()
            {
                SAFE_DELETE(this->m_pData);
                this->m_pData = NULL;
                glDeleteBuffers(1, &this->m_Buffer);
                glDeleteVertexArrays(1, &this->m_VertexArray);
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
                return (void*)this->m_Buffer;
            }

            // **************************************************************************
            // **************************************************************************
            void* CVertexBuffer::Lock()
            {
                this->m_pData = new SVertex[this->m_Size];
                glBindBuffer(GL_ARRAY_BUFFER, this->m_Buffer);
                return m_pData;
            }

            // **************************************************************************
            // **************************************************************************
            void CVertexBuffer::Unlock()
            {
                glBufferData(GL_ARRAY_BUFFER, this->m_Size * sizeof(SVertex), &this->m_pData[0], GL_STATIC_DRAW);
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                SAFE_DELETE(this->m_pData);
                this->m_pData = NULL;
            }

            // **************************************************************************
            // **************************************************************************
            SVertex* CVertexBuffer::GetVertices()
            {
                SVertex* data = new SVertex[this->m_Size];
                glBindBuffer(GL_ARRAY_BUFFER, this->m_Buffer);
                glGetBufferSubData(GL_ARRAY_BUFFER,0,this->m_Size*sizeof(SVertex),data);
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                return data;
            }

        }
    }
}