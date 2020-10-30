#ifndef _MODEL_H_
#define _MODEL_H_

// Engine specific includes
#include "Defines.h"
#include "Vector3.h"
#include "Matrix.h"
#include "Quaternion.h"
#include "IGraphics.h"
#include "ITexture2D.h"
#include "IVertexBuffer.h"
#include "Camera.h"
#include "Mesh.h"
#include "BoundingBox.h"
#include "Box.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <assert.h>


#include <thread>





// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {

        /// @brief Model that contains different Meshes, Textures and Materials
        ///
        class CModel
        {
        private:

            /// @brief Scene struct we fill for multithreading
            ///
            struct SScene
            {
                int32 MeshCount;
                std::string* ppTexturePath; //texture path array
                int32* pVertexCount; //vertex count array
                int32* pIndexCount; // index count array
                SVertex** ppVertexArray; //vertex array - array
                int32** ppIndexArray; //index array - array

            };
        private:
            /// @brief Thread to load Textures and Models during runtime
            ///
            std::thread m_LoadThread;
            /// @brief Vertices for the Bounding Box (Visualisation only)
            ///
            IVertexBuffer* m_pBoundingVertices;
            /// @brief Bounding Box needed for Frustum Culling
            ///
            CBoundingBox m_BoundingBox;
            /// @brief Path to the Model
            ///
            std::string m_Path;
            /// @brief Graphic Object
            ///
            IGraphics* m_pGraphics;
            /// @brief Mesh Array
            ///
            CMesh** m_ppMeshes;
            /// @brief Mesh Count
            ///
            int32 m_Meshcount;
            /// @brief Scene where we load our data in for multithreading purpose
            ///
            SScene* m_pScene;
            /// @brief Whether the Image has been loaded
            ///
            bool m_Loaded;
            /// @brief Whether the Image is ready to draw
            ///
            bool m_Ready;
        public:
            /// @brief Creates a new Instance of Model
            ///
            /// @param Graphic Object
            /// @param Path to the Model
            ///
            CModel(IGraphics* a_pGraphics, std::string a_Path);

            /// @brief Destroys the Instance
            ///
            ~CModel();
        private:
            /// @brief Calculates the Boundings
            ///
            void CalculateBounding();
        public:
            /// @brief Join the Thread, makes the Main Thread wait for this Thread to end
            ///
            void JoinThread();
            /// @brief Load a Model using Assimp
            ///
            void LoadAssimp();

            /// @brief Load a Model using FBX
            ///
            /// @param Path to the Model
            ///
            void LoadFBX();

            /// @brief Returns the VertexBuffer
            ///
            /// @param Which Mesh to use
            ///
            /// @returns The VertexBuffer
            ///
            IVertexBuffer* GetVertices(int32 a_Mesh);


            /// @brief Returns the Texture
            ///
            /// @param Which Mesh to use
            ///
            /// @returns The Texture
            ///
            ITexture2D* GetTexture(int32 a_Mesh);


            /// @brief Returns The Num of Meshes
            ///
            /// @returns The Num of Meshes
            ///
            int GetMeshes();


            /// @brief Returns the BoundingBox
            ///
            /// @returns The BoundingBox
            ///
            CBoundingBox GetBoundingBox();

            /// @brief Update the Model, if finished, set graphic to initialize Model
            ///
            void Update();
            /// @brief Draw the object
            ///
            /// @param Camera Object
            /// @param used Material
            /// @param Primitive we use for drawing
            /// @param InstanceBuffer filled with data
            ///
            void DrawInstanced(CCamera* a_pCam, IMaterial* a_pMaterial, EPrimitive a_Primitive, IInstanceBuffer* a_pInstanceBuffer);

            /// @brief Draw the object
            ///
            /// @param Camera Object
            /// @param used Material
            /// @param Primitive we use for drawing
            /// @param Position of the Model
            /// @param Size of the Model
            /// @param Rotation of the Model
            /// @param Center of the Model
            /// @param Color of the Model
            ///
            void Draw(CCamera* a_pCam, IMaterial* a_pMaterial, EPrimitive a_Primitive,
                Vector3<float32> a_Position = Vector3<float32>(0.0f, 0.0f, 0.0f),
                Vector3<float32> a_Size = Vector3<float32>(1.0f, 1.0f, 1.0f),
                Vector3<float32> a_Rotation = Vector3<float32>(0.0f, 0.0f, 0.0f),
                Vector3<float32> a_Center = Vector3<float32>(0.0f, 0.0f, 0.0f),
                Color a_Color = Color(1.0f, 1.0f, 1.0f, 1.0f));

            /// @brief Draw the object
            ///
            /// @param Camera Object
            /// @param used Material
            /// @param Primitive we use for drawing
            /// @param Position of the Model
            /// @param Size of the Model
            /// @param Rotation of the Model
            /// @param Center of the Model
            /// @param Color of the Model
            ///
            void Draw(CCamera* a_pCam, IMaterial* a_pMaterial, EPrimitive a_Primitive,
                Vector3<float32> a_Position,
                Vector3<float32> a_Size,
                Matrix<float32> a_Rotation,
                Vector3<float32> a_Center,
                Color a_Color);



        };
    }
}

#endif /* _MODEL_H_ */