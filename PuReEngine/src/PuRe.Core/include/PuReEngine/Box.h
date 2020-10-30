#ifndef _BOX_H_
#define _BOX_H_

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

        /// @brief Box Vertex Buffer
        ///
        class Box
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
            Box(IGraphics* a_pGraphics);

            /// @brief Destroys the Instance
            ///
            ~Box();
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
#endif /* _BOX_H_ */