#ifndef _VERTEXBUFFER_H_
#define _VERTEXBUFFER_H_
// OpenGL specific includes
#define GLEW_STATIC
#include <GL/glew.h>
// PuReEngine::Core specific includes
#include "PuReEngine/Vector2.h"
#include "PuReEngine/Vector3.h"
#include "PuReEngine/IVertexBuffer.h"
#include <cstdlib>

namespace PuReEngine
{
    namespace Graphics
    {
        namespace OpenGL
        {

            using ::PuReEngine::Core::IVertexBuffer;
            using ::PuReEngine::Core::Vector3;
            using ::PuReEngine::Core::Vector2;
            using ::PuReEngine::Core::SVertex;

            /// @brief Buffer to handle Vertex Data in OpenGL
            ///
            class CVertexBuffer : public IVertexBuffer
            {

            private:
                /// @brief Size of The Buffer
                ///
                int32 m_Size;
                /// @brief Amount of Strides
                ///
                int32 m_Stride;
                /// @brief Buffer identifier
                ///
                GLuint m_Buffer;
                /// @brief Vertex Array
                ///
                GLuint m_VertexArray;
                /// @brief Vertex Data
                ///
                SVertex* m_pData;
            public:
                /// @brief Constructor
                ///
                /// @param Pointer to the Device
                /// @param Size of the Buffer
                /// @param Amount of Strides
                ///
                CVertexBuffer(int32 a_Size, int32 a_Stride);

                /// @brief Destructor
                ///
                ~CVertexBuffer();
            public:

                /// @brief Get the Size of the Buffer
                ///
                /// @returns the Buffer Size
                ///
                int32 GetSize();

                /// @brief Get the Amount of Stride of the Buffer
                ///
                /// @returns the Buffer Stride Amount
                ///
                int32 GetStride();

                /// @brief Lock the Buffer so it can be written on
                ///
                /// @returns the writable Data
                ///
                void* Lock();

                /// @brief Unlock the Buffer and save the written Data
                ///
                void Unlock();

                /// @brief Get the Data of the Buffer
                ///
                /// @returns the Buffer Data
                ///
                void* GetData();

                /// @brief Return the Vertices from the GPU.
                ///
                SVertex* GetVertices();
            };

        }
    }
}
#endif /* _VERTEXBUFFER_H_ */