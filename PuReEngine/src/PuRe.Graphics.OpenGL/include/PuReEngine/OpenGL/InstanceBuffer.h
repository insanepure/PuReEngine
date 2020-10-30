#ifndef _INSTANCEBUFFER_H_
#define _INSTANCEBUFFER_H_
// OpenGL specific includes
#define GLEW_STATIC
#include <GL/glew.h>
// PuReEngine::Core specific includes
#include "PuReEngine/IInstanceBuffer.h"

namespace PuReEngine
{
    namespace Graphics
    {
        namespace OpenGL
        {

            using ::PuReEngine::Core::IInstanceBuffer;
            using ::PuReEngine::Core::SInstance;

            /// @brief Buffer to handle Instance Data in OpenGL
            ///
            class CInstanceBuffer : public IInstanceBuffer
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
                SInstance* m_pData;
            public:
                /// @brief Constructor
                ///
                /// @param Pointer to the Device
                /// @param Size of the Buffer
                /// @param Amount of Strides
                ///
                CInstanceBuffer(int32 a_Size, int32 a_Stride);

                /// @brief Destructor
                ///
                ~CInstanceBuffer();
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

            };

        }
    }
}

#endif /* _INSTANCEBUFFER_H_ */