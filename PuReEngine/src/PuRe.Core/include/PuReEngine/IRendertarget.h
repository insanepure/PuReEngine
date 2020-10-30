#ifndef _IRENDERTARGET_H_
#define _IRENDERTARGET_H_

// PuReEngine specific includes
#include "Defines.h"
#include "ITexture2D.h"
#include "Vector2.h"
#include "Vector3.h"
#include "IMaterial.h"

#include "Camera.h"

// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {
        /// @brief Base Interface for Rendertargets
        ///
        struct IRendertarget
        {
            /// @brief Destroyes an instance of IRendertarget
            ///
            virtual ~IRendertarget() {};
            /// @brief Draw on the Rendertarget's Gemoetry Buffers
            ///
            /// @param Color for the Background
            ///
            virtual void ApplyGeometryPass(Color a_Color) = 0;
            /// @brief Draw on the Rendertarget's Light Buffer
            ///
            /// @param Color for the Background
            ///
            virtual void ApplyLightPass(Color a_Color) = 0;
            /// @brief Draw on the Rendertarget's SSAO Buffer
            ///
            /// @param Color for the Background
            ///
            virtual void ApplySSAOPass(Color a_Color) = 0;

            /// @brief Copy the Content of this Target to another
            ///
            /// @param Target to copy into
            /// @param Position we copy it to
            /// @param Size we copy it to
            /// @param Position we copy from
            /// @param Size we copy from
            ///
            virtual void Copy(IRendertarget* a_pTarget,Vector2<int32> a_TargetPosition,Vector2<int32> a_TargetSize,Vector2<int32> a_SourcePosition,Vector2<int32> a_SourceSize) = 0;

            /// @brief Gets the Texture Element
            ///
            /// @param Which index of the texture we want to be returned
            ///
            /// @returns Pointer to an ITexture2D Instance
            ///
            virtual ITexture2D* GetTexture2D(int32 index) = 0;

            /// @brief Draw the object
            ///
            /// @param Camera for the View and Projection Matrix
            /// @param Material used to draw
            ///
            virtual void Draw(CCamera* a_pCamera, IMaterial* a_pMaterial) = 0;

            /// @brief Draw the object
            ///
            /// @param Camera for the View and Projection Matrix
            /// @param Material used to draw
            /// @param Position of the Quad
            /// @param Size of the Quad
            ///
            virtual void Draw(CCamera* a_pCamera, IMaterial* a_pMaterial, Vector3<float32> a_Position, Vector3<float32> a_Size) = 0;

            /// @brief Draw the object
            ///
            /// @param Camera for the View and Projection Matrix
            /// @param Material used to draw
            /// @param X+Y Position on the UV
            /// @param Width and Height on the UV
            /// @param Position of the Quad
            /// @param Size of the Quad
            ///
            virtual void Draw(CCamera* a_pCamera,IMaterial* a_pMaterial, Vector2<float32> a_UVPosition, Vector2<float32> a_UVSize, Vector3<float32> a_Position, Vector3<float32> a_Size) = 0;
        };

    }
}

#endif /* _IRENDERTARGET_H_ */