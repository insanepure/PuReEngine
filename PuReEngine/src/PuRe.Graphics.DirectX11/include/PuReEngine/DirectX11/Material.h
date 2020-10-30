#ifndef _MATERIAL_H_
#define _MATERIAL_H_

// Direct3D specific includes
#include <D3D11.h>
#include <D3DX11.h>

// PuReEngine::Core specific includes
#include "PuReEngine/Defines.h"
#include "PuReEngine/IMaterial.h"
#include "PuReEngine/Matrix.h"
#include "PuReEngine/Vector2.h"
#include "PuReEngine/Vector3.h"
#include "PuReEngine/Vector4.h"
#include "PuReEngine/Color.h"
#include <string>

// PuReEngine::DirectX11 specific include
#include "ShaderO.h"

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
            using ::PuReEngine::Core::Vector4;
            using ::PuReEngine::Core::Color;

            /// @brief Material Class for Shader within DirectX11
            ///
            class CMaterial : public IMaterial
            {
            private:
                /// @brief pointer to the sampler State
                ///
                ID3D11SamplerState* m_pSamplerState;
                /// @brief A Vertex Buffer
                ///
                ID3D11Buffer* m_pVertexBuffer;

                /// @brief The Vertex Shader needed for DX11
                ///
                ID3D11VertexShader* m_pVertexShader;
                /// @brief The Vertex Shader Data
                ///
                CShader* m_pVertexShaderData;
                /// @brief The Pixel Shader needed for DX11
                ///
                ID3D11PixelShader* m_pPixelShader;
                /// @brief The Pixel Shader Data
                ///
                CShader* m_pPixelShaderData;

                /// @brief The Device
                ///
                ID3D11Device* m_pDevice;

                /// @brief The DeviceContext
                ///
                ID3D11DeviceContext* m_pDeviceContext;

                /// @brief The Input Layout
                ///
                ID3D11InputLayout* m_pInputLayout;
            public:
                /// @brief Constructor
                ///
                /// @param Pointer to the Device
                /// @param Pointer to the DeviceContext
                /// @param Path to the Material
                ///
                CMaterial(ID3D11Device* a_pDevice, ID3D11DeviceContext* a_pDeviceContext, const char8* a_pFile);
                /// @brief Destructor
                ///
                ~CMaterial();
            public:
                /// @brief Append a Matrix to a Variable in the Material
                ///
                /// @param A Matrix
                /// @param Name of the Variable in the Material
                ///
                void SetMatrix(Matrix<float32>& a_rMatrix, const char8* a_pName);

                /// @brief Append a CubeMap
                ///
                /// @param A Texture
                /// @param Name of the Variable in the Material
                /// @param Position of the texture
                ///
                void SetCubeMap(ITexture2D* a_pTexture, const char8* a_pName, int32 a_Position);

                /// @brief Append a Texture to a Variable in the Material
                ///
                /// @param A Texture
                /// @param Name of the Variable in the Material
                /// @param Position of the texture
                ///
                void SetTexture2D(ITexture2D* a_pTexture, const char8* a_pName, int32 a_Position);

                /// @brief Add a float to the Material
                ///
                /// @param A float
                /// @param Name of the Variable in the Material
                ///
                void SetFloat(float32 a_Value, const char8* a_pName);

                /// @brief Add a Vector2 to the Material
                ///
                /// @param A Vector2
                /// @param Name of the Variable in the Material
                ///
                void SetVector2(Vector2<float32> a_Vector, const char8* a_pName);

                /// @brief Add a Vector3 to the Material
                ///
                /// @param A Vector3
                /// @param Name of the Variable in the Material
                ///
                void SetVector3(Vector3<float32> a_Vector, const char8* a_pName);

                /// @brief Add a Vector4 to the Material
                ///
                /// @param A Vector4
                /// @param Name of the Variable in the Material
                ///
                void SetVector4(Vector4<float32> a_Vector, const char8* a_pName);

                /// @brief Add a Color to the Material
                ///
                /// @param A Color
                /// @param Name of the Variable in the Material
                ///
                void SetColor(Color a_Value, const char8* a_pName);

                /// @brief Use Material
                ///
                void Apply();
            };

        }
    }
}
#endif /* _MATERIAL_H_ */