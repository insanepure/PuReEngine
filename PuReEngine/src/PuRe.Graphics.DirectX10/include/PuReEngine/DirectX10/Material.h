#ifndef _MATERIAL_H_
#define _MATERIAL_H_

// Direct3D specific includes
#include <D3D10.h>
#include <D3DX10.h>

// PuReEngine::Core specific includes
#include "PuReEngine/Defines.h"
#include "PuReEngine/IMaterial.h"
#include "PuReEngine/Matrix.h"
#include "PuReEngine/Vector2.h"
#include "PuReEngine/Vector3.h"
#include "PuReEngine/Vector4.h"
#include "PuReEngine/Color.h"
#include <string>

namespace PuReEngine 
{
    namespace Graphics 
    {
        namespace DirectX10 
        {
            using ::PuReEngine::Core::IMaterial;
            using ::PuReEngine::Core::Matrix;
            using ::PuReEngine::Core::ITexture2D;
            using ::PuReEngine::Core::Vector2;
            using ::PuReEngine::Core::Vector3;
            using ::PuReEngine::Core::Vector4;
            using ::PuReEngine::Core::Color;

            /// @brief Material Class for Shader within DirectX10
            ///
            class CMaterial : public IMaterial
            {
            private:

                /// @brief A Vertex Buffer
                ///
                ID3D10Buffer* m_pVertexBuffer;


                /// @brief The Effect/Shader
                ///
                ID3D10Effect* m_pEffect;

                /// @brief The Technique
                ///
                ID3D10EffectTechnique* m_pTechnique;

                /// @brief The Device
                ///
                ID3D10Device* m_pDevice;

                /// @brief The Input Layout
                ///
                ID3D10InputLayout* m_pInputLayout;
            public:
                /// @brief Constructor
                ///
                /// @param Pointer to the Device
                /// @param Path to the Material
                ///
                CMaterial(ID3D10Device* a_pDevice, const char8* a_pFile);
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