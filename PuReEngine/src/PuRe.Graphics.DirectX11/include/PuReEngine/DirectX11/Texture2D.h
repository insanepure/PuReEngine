#ifndef _TEXTURE2D_H_
#define _TEXTURE2D_H_

// Direct3D specific includes
#include <D3D11.h>
#include <D3DX11.h>

// PuReEngine::Core specific includes
#include "PuReEngine/Defines.h"
#include "PuReEngine/ITexture2D.h"
#include <string>

namespace PuReEngine
{
    namespace Graphics
    {
        namespace DirectX11
        {

            using ::PuReEngine::Core::Color;
            using ::PuReEngine::Core::ITexture2D;
            using ::PuReEngine::Core::STexture2DDescription;

            /// @brief 2D Texture Object within DirectX11
            ///
            class CTexture2D : public ITexture2D
            {
            private:

                /// @brief If the Texture is writable
                ///
                bool m_IsWriting;
                /// @brief Texture Information
                ///
                D3D11_MAPPED_SUBRESOURCE m_MappedTex;
                /// @brief Pointer to the Device
                ///
                ID3D11Device* m_pDevice;
                /// @brief Pointer to the DeviceContextz
                ///
                ID3D11DeviceContext* m_pDeviceContext;
                /// @brief Texture to Write on
                ///
                ID3D11Texture2D* m_pTexture;
                /// @brief Shader Information
                ///
                ID3D11ShaderResourceView* m_pShaderView;
                /// @brief Texture Description
                ///
                STexture2DDescription m_Description;
            public:
                /// @brief Constructor
                ///
                /// @param Pointer to the Device
                /// @param Pointer to the DeviceContext
                ///
                CTexture2D(ID3D11Device* a_pDevice, ID3D11DeviceContext* a_pDeviceContext);
                /// @brief Constructor
                ///
                /// @param Pointer to the Device
                /// @param Pointer to the DeviceContext
                /// @param Adress of the Texture Description
                ///
                CTexture2D(ID3D11Device* a_pDevice, ID3D11DeviceContext* a_pDeviceContext, const STexture2DDescription& a_rDescription);

                /// @brief Destructor
                ///
                ~CTexture2D();

                /// @brief Coppy this Resource to the Target's Resource
                ///
                /// @param Target we copy our Data to
                /// @param Whether the Target is froma  Rendertarget or not
                ///
                void Copy(ITexture2D* a_Target, bool a_Rendertarget);

                /// @brief Get the Description of a Texture
                ///
                /// @returns the Texture2DDescription
                ///
                STexture2DDescription GetDescription();

                /// @brief Information of the Texture
                ///
                /// @returns The Data
                ///
                void* GetData();

                /// @brief Loads a Texture from Memory
                ///
                /// @param Pointer to the Pixels used
                /// @param Width of the image
                /// @param Height of the image
                ///
                void LoadTextureFromMemory(uint8* a_pPixels, int32 a_Width, int32 a_Height);

                /// @brief Save a Texture to File
                ///
                /// @param Path where its saved
                ///
                void SaveTextureToFile(const char8* a_pPath);

                /// @brief Creates a CubeMap Texture, cannot be an editable Texture
                ///
                /// @param Pointer to the Pixels array used
                /// @param Width of the image
                /// @param Height of the image
                ///
                void CreateCubeMapFromMemory(uint8** a_ppPixels, int32 Width, int32 Height);

                /// @brief Creates a CubeMap Texture, cannot be an editable Texture
                ///
                /// @param Pointer to the Pixels array used
                ///
                void CreateCubeMap(uint8** a_ppPixels);

                /// @brief Creates a editable Texture
                ///
                void CreateTexture();

                /// @brief Creates a Rendertarget Texture, cannot be an editable Texture
                ///
                void CreateRendertarget();

                /// @brief Creates a Depth Texture, cannot be an editable Texture
                ///
                void CreateDepth();

                /// @brief Set the Pixels of a Texture
                ///
                /// @param Pixels as Array
                ///
                void SetPixels(uint8* a_pPixels);
            };

        }
    }
}
#endif /* _TEXTURE2D_H_ */