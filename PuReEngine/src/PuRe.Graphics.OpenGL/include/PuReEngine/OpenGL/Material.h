#ifndef _MATERIAL_H_
#define _MATERIAL_H_

// OpenGL specific includes
#define GLEW_STATIC
#include <GL/glew.h>
// PuReEngine::Core specific includes
#include "PuReEngine/Defines.h"
#include "PuReEngine/IMaterial.h"
#include "PuReEngine/Matrix.h"
#include "PuReEngine/Vector2.h"
#include "PuReEngine/Vector3.h"
#include "PuReEngine/Vector4.h"
#include "PuReEngine/Color.h"
#include <string>
#include <fstream>
#include <cstdlib>


namespace PuReEngine
{
    namespace Graphics
    {
        namespace OpenGL
        {

            using ::PuReEngine::Core::IMaterial;
            using ::PuReEngine::Core::Matrix;
            using ::PuReEngine::Core::ITexture2D;
            using ::PuReEngine::Core::Vector2;
            using ::PuReEngine::Core::Vector3;
            using ::PuReEngine::Core::Vector4;
            using ::PuReEngine::Core::Color;

            /// @brief Material Class for Shader within OpenGL
            ///
            class CMaterial : public IMaterial
            {
                /// @brief combined Shader
                ///
                GLuint m_ProgramID;
                /// @brief Vertex Shader
                ///
                GLuint m_VertexID;
                /// @brief Fragment Shader
                ///
                GLuint m_FragmentID;
                /// @brief ID for the Texture variable
                ///
                GLint* m_pTextureID;
                /// @brief ID for the Projection variable
                ///
                GLuint m_ProjectionID;
                /// @brief ID for the View variable
                ///
                GLuint m_ViewID;
                /// @brief ID for the Model variable
                ///
                GLuint m_ModelID;
                /// @brief Counter that counts how many textures were used
                ///
                int32 n_TexturesUsed;
            public:
                /// @brief Constructor
                ///
                /// @param Pointer to the Device
                /// @param Path to the Material
                ///
                CMaterial(const char8* a_pFile);
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


            private:
                /// @brief Get the Errors of the Shader
                ///
                /// @param ShaderID
                ///
                void ShaderLog(GLuint a_Shader);
                /// @brief Get the Errors of the Program
                ///
                /// @param programID
                ///
                void ProgramLog(GLuint a_Program);
                /// @brief loads a Shader and returns the ID
                ///
                /// @param path to the shader
                /// @param Type of the Shader
                ///
                /// @returns the Shader ID
                ///
                GLuint loadShader(const char* a_pPath, GLenum a_ShaderType);
            };

        }
    }
}

#endif /* _MATERIAL_H_ */