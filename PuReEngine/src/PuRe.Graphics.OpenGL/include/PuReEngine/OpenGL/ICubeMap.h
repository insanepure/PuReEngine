#ifndef _CUBEMAP_H_
#define _CUBEMAP_H_
// OpenGL specific includes
#define GLEW_STATIC
#include <GL/glew.h>
// PuReEngine::Core specific includes
#include "PuReEngine/Defines.h"
#include "PuReEngine/ICubeMap.h"
#include <string>
#include <fstream>
#include <cstring>


namespace PuReEngine
{
    namespace Graphics
    {
        namespace OpenGL
        {

            using ::PuReEngine::Core::Color;
            using ::PuReEngine::Core::ICubeMap;

            /// @brief CubeMap Object within OpenGL
            ///
            class CCubeMap : public ICubeMap
            {
            private:
                /// @brief If the Texture is writable
                ///
                bool m_IsWriting;
                /// @brief Texture Data
                ///
                GLuint m_TextureID;
                /// @brief Pixel Array
                ///
                float32* m_pPixels;

            public:
                /// @brief Constructor
                ///
                CCubeMap();

                /// @brief Destructor
                ///
                ~CCubeMap();

                /// @brief Information of the CubeMap
                ///
                /// @returns The Data
                ///
                void* GetData();

                /// @brief Loads 6 Texture from Memory
                ///
                /// @param Pointer to the Pixel array used
                /// @param Width of the images
                /// @param Height of the images
                ///
                void LoadTextureFromMemory(unsigned char8** a_ppPixels, int32 a_Width, int32 a_Height);
            };

        }
    }
}

#endif /* _TEXTURE2D_H_ */