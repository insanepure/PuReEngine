#ifndef _QUAD_H_
#define _QUAD_H_

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

        /// @brief Quad Vertex Buffer
        ///
        class Quad
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
            Quad(IGraphics* a_pGraphics);

            /// @brief Destroys the Instance
            ///
            ~Quad();
        public:

            /// @brief Returns the Vertex Buffer
            ///
            /// @param Vertex Buffer Pointer
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

#endif /* _QUAD_H_ */