#ifndef _INSTANCEBUFFER_H_
#define _INSTANCEBUFFER_H_

// Direct3D specific includes
#include <D3D10.h>
#include <D3DX10.h>

// PuReEngine::Core specific includes
#include "PuReEngine/IInstanceBuffer.h"

namespace PuReEngine
{
    namespace Graphics
    {
        namespace DirectX10
        {

            using ::PuReEngine::Core::IInstanceBuffer;

            /// @brief Buffer to handle Vertex Data in DirectX11
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
                CInstanceBuffer(ID3D10Device* a_pDevice, int32 a_Size, int32 a_Stride);

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