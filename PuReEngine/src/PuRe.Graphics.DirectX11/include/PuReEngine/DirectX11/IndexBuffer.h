#ifndef _INDEXBUFFER_H_
#define _INDEXBUFFER_H_
// Direct3D specific includes
#include <D3D11.h>
#include <D3DX11.h>
// PuReEngine::Core specific includes
#include "PuReEngine/IIndexBuffer.h"

namespace PuReEngine
{
    namespace Graphics
    {
        namespace DirectX11
        {

            using ::PuReEngine::Core::IIndexBuffer;

            /// @brief Buffer to handle Index Data in DirectX11
            ///
            class CIndexBuffer : public IIndexBuffer
            {
            private:
                /// @brief Size of The Buffer
                ///
                int32 m_Size;
                /// @brief Pointer to the Device
                ///
                ID3D11Device* m_pDevice;
                /// @brief Pointer to the DeviceContext
                ///
                ID3D11DeviceContext* m_pDeviceContext;
                /// @brief Pointer to the Buffer
                ///
                ID3D11Buffer* m_pBuffer;
            public:

                /// @brief Constructor
                ///
                /// @param Pointer to the Device
                /// @param Pointer to the DeviceContext
                /// @param Size of the Buffer
                ///
                CIndexBuffer(ID3D11Device* a_pDevice, ID3D11DeviceContext* a_pDeviceContext, int32 a_Size);

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