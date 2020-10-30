#ifndef _INDEXBUFFER_H_
#define _INDEXBUFFER_H_
// OpenGL specific includes
#define GLEW_STATIC
#include <GL/glew.h>
// PuReEngine::Core specific includes
#include "PuReEngine/IIndexBuffer.h"

namespace PuReEngine
{
    namespace Graphics
    {
        namespace OpenGL
        {

            using ::PuReEngine::Core::IIndexBuffer;

            /// @brief Buffer to handle Vertex Data in OpenGL
            ///
            class CIndexBuffer : public IIndexBuffer
            {
            private:
                /// @brief Size of The Buffer
                ///
                int32 m_Size;
                /// @brief Buffer identifier
                ///
                GLuint m_Buffer;
                /// @brief Raw index buffer
                ///
                uint32* m_pData;
            public:
                /// @brief Constructor
                ///
                /// @param Size of the Buffer
                ///
                CIndexBuffer(int32 m_Size);

                /// @brief Destructor
                ///
                ~CIndexBuffer();
            public:

                /// @brief Get the Size of the Buffer
                ///
                /// @returns the Buffer Size
                ///
                int32 GetSize();

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

#endif /* _INDEXBUFFER_H_ */