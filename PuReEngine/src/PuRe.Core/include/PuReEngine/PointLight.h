#ifndef _POINTLIGHT_H_
#define _POINTLIGHT_H_

// Engine specific includes
#include "Defines.h"
#include "Vector3.h"
#include "IMaterial.h"
#include "IRendertarget.h"
#include "Quad.h"


// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {
        /// @brief Point Light
        ///
        class CPointLight
        {
        private:
            /// @brief Quad used to draw
            ///
            Quad* m_pQuad;
        public:
            /// @brief Create a PointLight
            ///
            /// @param Graphics Object
            /// @param Material used
            ///
            CPointLight(IGraphics* a_pGraphics);
            /// @brief Destroyes a PointLight
            ///
            ~CPointLight();
        public:
            /// @brief Draw a PointLight
            ///
            /// @param Graphics Object
            /// @param Camera used from which the light is seen
            /// @param Camera used for drawing the quad
            /// @param Rendertarget used for Normal/Position
            /// @param Position of the Point Light
            /// @param Color of the Point Light
            ///
            void Draw(IGraphics* a_pGraphics, IMaterial* a_pMaterial, CCamera* a_pViewCamera, CCamera* a_pPostCamera, IRendertarget* a_pRendertarget, Vector3<float32> a_Position = Vector3<float32>(0.0f,0.0f,0.0f), Color a_Color = Color(1.0f,1.0f,1.0f),float32 a_Radius = 1.0f,float32 a_Intensity = 1.0f);

            
        };
    }
}
#endif /* _POINTLIGHT_H_ */