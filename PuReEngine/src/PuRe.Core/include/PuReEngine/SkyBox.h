#ifndef _SKYBOX_H_
#define _SKYBOX_H_

// Engine specific includes
#include "Defines.h"
#include "IMaterial.h"
#include "ITexture2D.h"
#include "Quad.h"
#include "IVertexBuffer.h"
#include "IIndexBuffer.h"

#include <thread>




// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {
        /// @brief SkyBox to display the sky
        ///
        class CSkyBox
        {
        private:
            /// @brief Thread to load Textures and Models during runtime
            ///
            std::thread m_LoadThread;
            /// @brief Container for the memory and width/height
            ///
            uint8** m_ppPixels;
            /// @brief Width of one image
            ///
            int32 m_Width;
            /// @brief Height of one image
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
            /// @brief Box to render
            ///
            Quad* m_pQuad;
            /// @brief Texture Object
            ///
            ITexture2D* m_pTexture;
        public:
            /// @brief Creates a new Instance of Sprite
            ///
            /// @param Graphic Object
            /// @param Material Object
            /// @param Path To the skybox
            ///
            CSkyBox(IGraphics* a_pGraphics, std::string a_pPath);

            /// @brief Destroys the Instance
            ///
            ~CSkyBox();
        public:
            /// @brief Join the Thread, makes the Main Thread wait for this Thread to end
            ///
            void JoinThread();
            /// @brief Returns the Texture
            ///
            /// @returns The Texture
            ///
            ITexture2D* GetTexture();
            /// @brief Draw the object
            ///
            /// @param Box's Material used to render
            /// @param Dome's Rotation
            ///
            void Draw(CCamera* a_pCam, IMaterial* a_pMaterial, Vector3<float32> a_Rotation = Vector3<float32>());
            /// @brief Draw the object
            ///
            /// @param Box's Material used to render
            /// @param Dome's Rotation
            ///
            void Draw(CCamera* a_pCam, IMaterial* a_pMaterial, Matrix<float32> a_Rotation);
        private:
            /// @brief Loads the texture as thread
            ///
            /// @param path to the textures
            ///
            void LoadTexture(std::string a_pPath);

            /// @brief Update the Textures, if finished, set graphic to initialize texture
            ///
            void Update();
        };
    }
}
#endif /* _SKYBOX_H_ */