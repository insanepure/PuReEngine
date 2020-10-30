#ifndef _SPHERE_H_
#define _SPHERE_H_

// Engine specific includes
#include "Defines.h"
#include "Vector3.h"
#include "IGraphics.h"
#include "IVertexBuffer.h"


// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {

        /// @brief Sphere Vertex Buffer
        ///
        class Sphere
        {
        private:
            /// @brief Graphic Object
            ///
            IGraphics* m_pGraphics;

            /// @brief Pointer to the Vertex Buffer
            ///
            IVertexBuffer* m_pVertexBuffer;
        public:
            /// @brief Creates a new Instance of Sprite
            ///
            /// @param Graphic Object
            ///
            Sphere(IGraphics* a_pGraphics);

            /// @brief Destroys the Instance
            ///
            ~Sphere();
        public:

            /// @brief Returns the Vertex Buffer
            ///
            /// @returns Vertex Buffer Pointer
            ///
            IVertexBuffer* GetBuffer();

            /// @brief Returns the Vertices
            ///
            /// @param changed Vertex Array
            ///
            static void GetVertices(SVertex* a_pVertex);

        };
    }
}
#endif /* _SPHERE_H_ */