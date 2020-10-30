#ifndef _DIRECTIONALLIGHT_H_
#define _DIRECTIONALLIGHT_H_

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
        /// @brief Directional Light
        ///
        class CDirectionalLight
        {
        private:
            /// @brief Quad used to draw
            ///
            Quad* m_pQuad;
        public:
            /// @brief Create a Directional Light
            ///
            /// @param Graphics Object
            ///
            CDirectionalLight(IGraphics* a_pGraphics);
            /// @brief Destroyes a Directional Light
            ///
            ~CDirectionalLight();
        public:
            /// @brief Draw a Directional Light
            ///
            /// @param Graphics Object
            /// @param Camera used
            /// @param Rendertarget used for Normal/Position
            ///
            void Draw(IGraphics* a_pGraphics, IMaterial* a_pMaterial, CCamera* a_pViewCamera, CCamera* a_pPostCamera, IRendertarget* a_pRendertarget);
            /// @brief Draw a Directional Light
            ///
            /// @param Graphics Object
            /// @param Camera used
            /// @param Rendertarget used for Normal/Position
            /// @param Direction of the Directional Light
            /// @param Color of the Directional Light
            ///
            void Draw(IGraphics* a_pGraphics, IMaterial* a_pMaterial, CCamera* a_pViewCamera, CCamera* a_pPostCamera, IRendertarget* a_pRendertarget, Vector3<float32> a_Direction, Color a_Color);

        };
    }
}
#endif /* _DIRECTIONALLIGHT_H_ */