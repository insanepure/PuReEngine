#ifndef _ICUBEMAP_H_
#define _ICUBEMAP_H_

// PuReEngine specific includes
#include "Defines.h"
#include "Color.h"
#include <string>

// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {
        /// @brief Base Interface for CubeMap Textures
        ///
        struct ICubeMap
        {
            /// @brief Destroyes an Instance of ICubeMap
            ///
            virtual ~ICubeMap() {};

            /// @brief Information of the CubeMap
            ///
            /// @returns The Data
            ///
            virtual void* GetData() = 0;

            /// @brief Loads 6 Texture from Memory
            ///
            /// @param Pointer to the Pixel array used
            /// @param Width of the images
            /// @param Height of the images
            ///
            virtual void LoadTextureFromMemory(unsigned char8** a_ppPixels, int32 a_Width, int32 a_Height) = 0;
        };

    }
}

#endif /* _ICUBEMAP_H_ */
