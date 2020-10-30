#ifndef _SPRITE_H_
#define _SPRITE_H_

// Engine specific includes
#include "Defines.h"
#include "Vector3.h"
#include "Matrix.h"
#include "Quaternion.h"
#include "IMaterial.h"
#include "IGraphics.h"
#include "ITexture2D.h"
#include "Camera.h"
#include "Quad.h"

#include <thread>


// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {

        /// @brief Simple Sprite for 2D Games
        ///
        class CSprite
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

            /// @brief Quad-Vertex-Buffer
            ///
            Quad* m_pQuadBuffer;

            /// @brief Texture Object
            ///
            ITexture2D* m_pTexture;
        public:
            /// @brief Copy constructor
            ///
            /// @param Other Object
            ///
            CSprite(CSprite& rhs);
            /// @brief Creates a new Instance of Sprite and Copy the ITexture2D
            ///
            /// @param Graphic Object
            /// @param Texture to copy
            /// @param whether its a rendertarget's texture or not
            ///
            CSprite(IGraphics* a_pGraphics, ITexture2D* a_pTexture, bool a_Rendertarget);
            /// @brief Creates a new Instance of Sprite
            ///
            /// @param Graphic Object
            /// @param Path to the Sprite
            ///
            CSprite(IGraphics* a_pGraphics, std::string a_Path);

            /// @brief Destroys the Instance
            ///
            ~CSprite();
        public:
            /// @brief Assigment operator
            ///
            /// @param Other Object
            ///
            /// @returns this
            ///
            CSprite& operator=(CSprite& rhs);
        public:
            /// @brief Join the Thread, makes the Main Thread wait for this Thread to end
            ///
            void JoinThread();
            /// @brief Returns The Texture
            ///
            /// @returns The Textire
            ///
            ITexture2D* GetTexture();

            /// @brief Returns the Size of the Texture
            ///
            /// @returns Size as Vector2<float32>
            ///
            Vector2<float32> GetSize();

            /// @brief Draw the object
            ///
            /// @param Camera Object
            /// @param Material used
            ///
            void Draw(CCamera* a_pCam, IMaterial* a_pMaterial);
            /// @brief Draw the object instanciated
            ///
            /// @param Camera Object
            /// @param Material used
            /// @param Primitive we use for drawing
            /// @param InstanceBuffer filled with data
            ///
            void DrawInstanced(CCamera* a_pCam, IMaterial* a_pMaterial, IInstanceBuffer* a_pInstanceBuffer);
            /// @brief Draw the object instanciated
            ///
            /// @param Camera Object
            /// @param Material used
            /// @param Primitive we use for drawing
            /// @param InstanceBuffer filled with data
            ///
            void DrawInstanced(CCamera* a_pCam, IMaterial* a_pMaterial, Vector2<float32> a_UVPosition, Vector2<float32> a_UVSize, IInstanceBuffer* a_pInstanceBuffer);

            /// @brief Draw the object
            ///
            /// @param Camera Pointer
            /// @param Material used
            /// @param Position of the Sprite
            /// @param Size of the Sprite
            /// @param Rotation of the Sprite
            /// @param Center of the Sprite
            /// @param Color of the Sprite
            ///
            void Draw(CCamera* a_pCam, IMaterial* a_pMaterial,
                Vector3<float32> a_Position = Vector3<float32>(0.0f, 0.0f, 0.0f),
                Vector3<float32> a_Size = Vector3<float32>(1.0f, 1.0f, 1.0f),
                Vector3<float32> a_Rotation = Vector3<float32>(0.0f, 0.0f, 0.0f),
                Vector3<float32> a_Center = Vector3<float32>(0.0f, 0.0f, 0.0f),
                Color = Color(1.0f, 1.0f, 1.0f, 1.0f));
            /// @brief Draw the object
            ///
            /// @param Camera Pointer
            /// @param Material used
            /// @param Position of the Sprite
            /// @param Size of the Sprite
            /// @param Rotation of the Sprite
            /// @param Center of the Sprite
            /// @param Color of the Sprite
            ///
            void Draw(CCamera* a_pCam, IMaterial* a_pMaterial,
                Vector3<float32> a_Position = Vector3<float32>(0.0f, 0.0f, 0.0f),
                Vector3<float32> a_Size = Vector3<float32>(1.0f, 1.0f, 1.0f),
                Matrix<float32> a_Rotation = Matrix<float32>(),
                Vector3<float32> a_Center = Vector3<float32>(0.0f, 0.0f, 0.0f),
                Color = Color(1.0f, 1.0f, 1.0f, 1.0f));

            /// @brief Draw the object
            ///
            /// @param Camera Pointer
            /// @param Material used
            /// @param X+Y Position on the UV
            /// @param Width and Height on the UV
            /// @param Position of the Sprite
            /// @param Size of the Sprite
            /// @param Rotation of the Sprite
            /// @param Center of the Sprite
            /// @param Color of the Sprite
            ///
            void Draw(CCamera* a_pCam, IMaterial* a_pMaterial, Vector2<float32> a_UVPosition, Vector2<float32> a_UVSize,
                Vector3<float32> a_Position = Vector3<float32>(0.0f, 0.0f, 0.0f),
                Vector3<float32> a_Size = Vector3<float32>(1.0f, 1.0f, 1.0f),
                Vector3<float32> a_Rotation = Vector3<float32>(0.0f, 0.0f, 0.0f),
                Vector3<float32> a_Center = Vector3<float32>(0.0f, 0.0f, 0.0f),
                Color a_Color = Color(1.0f, 1.0f, 1.0f, 1.0f));

            /// @brief Draw the object
            ///
            /// @param Camera Pointer
            /// @param Material used
            /// @param X+Y Position on the UV
            /// @param Width and Height on the UV
            /// @param Position of the Sprite
            /// @param Size of the Sprite
            /// @param Rotation of the Sprite
            /// @param Center of the Sprite
            /// @param Color of the Sprite
            ///
            void Draw(CCamera* a_pCam, IMaterial* a_pMaterial, Vector2<float32> a_UVPosition, Vector2<float32> a_UVSize,
                Vector3<float32> a_Position = Vector3<float32>(0.0f, 0.0f, 0.0f),
                Vector3<float32> a_Size = Vector3<float32>(1.0f, 1.0f, 1.0f),
                Matrix<float32> a_Rotation = Matrix<float32>(),
                Vector3<float32> a_Center = Vector3<float32>(0.0f, 0.0f, 0.0f),
                Color a_Color = Color(1.0f, 1.0f, 1.0f, 1.0f));
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

#endif /* _SPRITE_H_ */