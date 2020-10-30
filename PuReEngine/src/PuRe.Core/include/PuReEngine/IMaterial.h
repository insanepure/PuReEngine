#ifndef _IMATERIAL_H_
#define _IMATERIAL_H_

// PuReEngine specific includes
#include "Defines.h"
#include "Matrix.h"
#include "ITexture2D.h"
#include "Vector2.h"
#include "Vector3.h"
#include <string>

// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {
        /// @brief Base Interface for Materials
        ///
        struct IMaterial
        {
            /// @brief Destroyes an instance of IMaterial
            ///
            virtual ~IMaterial() {};
            /// @brief Append a Matrix to a Variable in the Material
            ///
            /// @param A Matrix
            /// @param Name of the Variable in the Material
            ///
            virtual void SetMatrix(Matrix<float32>& a_rMat, const char8* a_pName) = 0;

            /// @brief Append a CubeMap
            ///
            /// @param A Texture
            /// @param Name of the Variable in the Material
            /// @param Position of the texture
            ///
            virtual void SetCubeMap(ITexture2D* a_pTexture, const char8* a_pName, int32 a_Position) = 0;

            /// @brief Append a Texture to a Variable in the Material
            ///
            /// @param A Texture
            /// @param Name of the Variable in the Material
            /// @param Position of the texture
            ///
            virtual void SetTexture2D(ITexture2D* a_pTexture, const char8* a_pName,int32 a_Position) = 0;

            /// @brief Add a float to the Material
            ///
            /// @param A float
            /// @param Name of the Variable in the Material
            ///
            virtual void SetFloat(float32 a_Num, const char8* a_pName) = 0;

            /// @brief Add a Vector2 to the Material
            ///
            /// @param A Vector2
            /// @param Name of the Variable in the Material
            ///
            virtual void SetVector2(Vector2<float32> a_Vector, const char8* a_pName) = 0;

            /// @brief Add a Vector3 to the Material
            ///
            /// @param A Vector3
            /// @param Name of the Variable in the Material
            ///
            virtual void SetVector3(Vector3<float32> a_Vector, const char8* a_pName) = 0;

            /// @brief Add a Vector4 to the Material
            ///
            /// @param A Vector4
            /// @param Name of the Variable in the Material
            ///
            virtual void SetVector4(Vector4<float32> a_Vector, const char8* a_pName) = 0;

            /// @brief Add a Color to the Material
            ///
            /// @param A Color
            /// @param Name of the Variable in the Material
            ///
            virtual void SetColor(Color a_Color, const char8* a_pName) = 0;

            /// @brief Use Material for next calls
            ///
            virtual void Apply() = 0;
        };

    }
}

#endif /* _IMATERIAL_H_ */