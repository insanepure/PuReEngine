#ifndef _VERTEXBUFFER_H_
#define _VERTEXBUFFER_H_

// Direct3D specific includes
#include <D3D10.h>
#include <D3DX10.h>

// PuReEngine::Core specific includes
#include "PuReEngine/IVertexBuffer.h"

namespace PuReEngine
{
    namespace Graphics
    {
        namespace DirectX10
        {

            using ::PuReEngine::Core::IVertexBuffer;
            using ::PuReEngine::Core::SVertex;

            /// @brief Buffer to handle Vertex Data in DirectX10
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
                /// @brief Pointer to the Device
                ///
                ID3D10Device* m_pDevice;
                /// @brief Pointer to the Buffer
                ///
                ID3D10Buffer* m_pBuffer;

            public:
                /// @brief Constructor
                ///
                /// @param Pointer to the Device
                /// @param Size of the Buffer
                /// @param Amount of Strides
                ///
                CVertexBuffer(ID3D10Device* a_pDevice, int32 a_Size, int32 a_Stride);

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