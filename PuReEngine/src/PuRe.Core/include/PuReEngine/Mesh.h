#ifndef _MESH_H_
#define _MESH_H_

// Engine specific includes
#include "Defines.h"
#include "Vector3.h"
#include "Matrix.h"
#include "Quaternion.h"
#include "IMaterial.h"
#include "IGraphics.h"
#include "ITexture2D.h"
#include "IIndexBuffer.h"
#include "IVertexBuffer.h"
#include "Camera.h"

#include <thread>





// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {

        /// @brief Mesh for 3d Rendering
        ///
        class CMesh
        {
        private:
            /// @brief Thread to load Textures and Models during runtime
            ///
            std::thread m_LoadThread;
            /// @brief Path to the Tetures
            ///
            std::string m_TexturePath;
            /// @brief Pixel Array 
            ///
            uint8* m_pPixels;
            /// @brief Width of the Image
            ///
            int32 m_Width;
            /// @brief Height of the Image
            ///
            int32 m_Height;
            /// @brief Whether the Image has been loaded
            ///
            bool m_Loaded;
            /// @brief Whether the Image is ready to draw
            ///
            bool m_Ready;
            /// @brief Graphic Object
            ///
            IGraphics* m_pGraphics;

            /// @brief Vertex-Buffer
            ///
            IVertexBuffer* m_pVertexBuffer;

            /// @brief Index-Buffer
            ///
            IIndexBuffer* m_pIndexBuffer;

            /// @brief Texture Object
            ///
            ITexture2D* m_pTexture;
        public:
            /// @brief Creates a new Instance of Mesh
            ///
            CMesh();

            /// @brief Destroys the Instance
            ///
            ~CMesh();
        public:

            /// @brief Join the Thread, makes the Main Thread wait for this Thread to end
            ///
            void JoinThread();
            /// @brief Returns the VertexBuffer
            ///
            /// @returns The VertexBuffer
            ///
            IVertexBuffer* GetVertices();


            /// @brief Returns the Texture
            ///
            /// @returns The Texture
            ///
            ITexture2D* GetTexture();

            /// @brief Sets the Graphics Pointer
            ///
            /// @param graphics pointer
            ///
            void SetGraphic(IGraphics* a_pGraphics);

            /// @brief Sets the Vertex Buffer
            ///
            /// @param Array of vertices
            /// @param size as int32
            ///
            void SetVertexBuffer(SVertex* a_pVertices, int32 a_Size);

            /// @brief Sets the Index Buffer
            ///
            /// @param Array of indices
            /// @param size as int32
            ///
            void SetIndexBuffer(int32* a_pIndices, int32 a_Size);

            /// @brief Sets Texture
            ///
            /// @param path to the texture
            ///
            void SetTexture(std::string a_Path);
            /// @brief Draw the object instanciated
            ///
            /// @param Camera Object
            /// @param used Material
            /// @param Primitive we use for drawing
            /// @param InstanceBuffer filled with data
            ///
            void DrawInstanced(CCamera* a_pCam, IMaterial* a_pMaterial, EPrimitive a_Primitive, IInstanceBuffer* a_pInstanceBuffer);

            /// @brief Draw the object
            ///
            /// @param Camera Pointer
            /// @param used Material
            /// @param Primitive we use for drawing
            /// @param Position of the Mesh
            /// @param Size of the Mesh
            /// @param Rotation of the Mesh
            /// @param Center of the Mesh
            /// @param Color of the Mesh
            ///
            void Draw(CCamera* a_pCamera, IMaterial* a_pMaterial, EPrimitive a_Primitive,
                Vector3<float32> a_Position = Vector3<float32>(0.0f, 0.0f, 0.0f),
                Vector3<float32> a_Size = Vector3<float32>(1.0f, 1.0f, 1.0f),
                Vector3<float32> a_Rotation = Vector3<float32>(0.0f, 0.0f, 0.0f),
                Vector3<float32> a_Center = Vector3<float32>(0.0f, 0.0f, 0.0f),
                Color a_Color = Color(1.0f, 1.0f, 1.0f,1.0f));
            /// @brief Draw the object
            ///
            /// @param Camera Pointer
            /// @param used Material
            /// @param Primitive we use for drawing
            /// @param Position of the Mesh
            /// @param Size of the Mesh
            /// @param Rotation of the Mesh
            /// @param Center of the Mesh
            /// @param Color of the Mesh
            ///
            void Draw(CCamera* a_pCamera, IMaterial* a_pMaterial, EPrimitive a_Primitive,
                Vector3<float32> a_Position,
                Vector3<float32> a_Size,
                Matrix<float32> a_Rotation,
                Vector3<float32> a_Center,
                Color a_Color);
        private:

            /// @brief Loads the texture as thread
            ///
            void LoadTexture();

            /// @brief Update the Texture, if finished, set graphic to initialize texture
            ///
            void Update();

        };
    }
}

#endif /* _MESH_H_ */