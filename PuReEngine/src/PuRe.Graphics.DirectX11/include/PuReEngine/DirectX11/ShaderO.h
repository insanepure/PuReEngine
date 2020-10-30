#ifndef _SHADERO_H_
#define _SHADERO_H_
// Direct3D specific includes
#include <D3D11.h>
#include <D3DX11.h>
#include <d3dcompiler.h>

// PuReEngine::Core specific includes
#include "PuReEngine/Defines.h"
#include "PuReEngine/IMaterial.h"
#include "PuReEngine/Matrix.h"
#include "PuReEngine/Vector2.h"
#include "PuReEngine/Vector3.h"
#include <string>
#include <vector>

namespace PuReEngine
{
    namespace Graphics
    {
        namespace DirectX11
        {

            using ::PuReEngine::Core::IMaterial;
            using ::PuReEngine::Core::Matrix;
            using ::PuReEngine::Core::ITexture2D;
            using ::PuReEngine::Core::Vector2;
            using ::PuReEngine::Core::Vector3;

            /// @brief Data of the Constant Buffer
            ///
            struct SConstantBufferData
            {
                /// @brief Destructor
                ///
                ~SConstantBufferData()
                {
                    if (data)
                        free(data);
                    constantBuffer->Release();
                }

                /// @brief indes
                ///
                int idx;
                /// @brief size
                ///
                int size;
                /// @brief the raw memory data
                ///
                void* data;
                /// @brief buffer which is given to the shader later on
                ///
                ID3D11Buffer* constantBuffer;
                /// @brief if true, remap the constantBuffer
                ///
                bool changed;
            };

            /// @brief TextureOptions
            ///
            struct STextureBind
            {
                /// @brief Dunno
                ///
                int bindPoint;
                /// @brief Name of the Texture
                ///
                const char8* name;
                /// @brief Raw Texture Data
                ///
                ID3D11ShaderResourceView* pResource;
            };

            /// @brief Shader Class to read Pixel and Vertex Shader
            ///
            class CShader
            {
            private:
                /// @brief Textures and their Data
                ///
                std::vector<STextureBind> m_Textures;
                /// @brief Constant Buffers and their Data
                ///
                SConstantBufferData* m_pConstBuffers;
                /// @brief Reflection needed to get the constant buffer data
                ///
                ID3D11ShaderReflection* m_pVertexReflection;
                /// @brief The Device
                ///
                ID3D11Device* m_pDevice;
                /// @brief The DeviceContext
                ///
                ID3D11DeviceContext* m_pDeviceContext;
            public:
                /// @brief Constructor
                ///
                /// @param Pointer to the Device
                /// @param Pointer to the DeviceContext
                /// @param Path to the Material
                ///
                CShader(ID3D11Device* a_pDevice, ID3D11DeviceContext* a_pDeviceContext);
                /// @brief Destructor
                ///
                ~CShader();
            public:
                /// @brief Compile a shader
                ///
                /// @param filepath to the shaderfile
                /// @param name of the function within the shader
                /// @param name of the profile used within the shader
                ///
                /// @returns a DX11 Blob
                ///
                ID3DBlob* compile(const char8* a_pFilePath, const char8* a_pFunctionName, const char8* a_pProfile);
                /// @brief Append a Variable to a Variable in the Material
                ///
                /// @param A Variable
                /// @param Name of the Variable in the Material
                ///
                void setVar(void* a_pData, const char8* a_pName);

                /// @brief Append a Texture to a Variable in the Material
                ///
                /// @param A Texture
                /// @param Name of the Variable in the Material
                ///
                void SetTexture2D(ITexture2D* a_pTexture, const char8* a_pName);

                /// @brief Returns a constant buffer
                ///
                /// @param index of the buffer
                ///
                /// @returns a DX11 Buffer
                ///
                ID3D11Buffer* getConstantBuffer(int a_Index);
                /// @brief Returns amount of const buffers
                ///
                /// @returns integer as amount of buffers
                ///
                int getNumBuffers();

                /// @brief Returns the texture as resource
                ///
                /// @param index of the texture
                ///
                /// @returns a DX11 Resource
                ///
                ID3D11ShaderResourceView* getTexture(int a_Index);
                /// @brief Returns Bind Point
                ///
                /// @param index of the textur
                ///
                /// @returns integer as bind point
                ///
                int getTextureBindPoint(int a_Index);
                /// @brief Returns amount of textures
                ///
                /// @returns integer as amount of textures
                ///
                int getNumTextures();

            };
        }
    }
}

#endif /* _SHADERO_H_ */