#ifndef _ITEXTURE2D_H_
#define _ITEXTURE2D_H_

// PuReEngine specific includes
#include "Defines.h"
#include "Texture2DDescription.h"
#include "Color.h"
#include <string>

// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {
        /// @brief Base Interface for 2D Textures
        ///
        struct ITexture2D
        {
            /// @brief Destroyes an Instance of ITexture2D
            ///
            virtual ~ITexture2D() {};
            /// @brief Get the Description of a Texture
            ///
            /// @returns a Texture2DDescription
            ///
            virtual STexture2DDescription GetDescription() = 0;

            /// @brief Coppy this Resource to the Target's Resource
            ///
            /// @param Target we copy our Data to
                /// @param Whether the Target is froma  Rendertarget or not
            ///
            virtual void Copy(ITexture2D* a_Target, bool a_Rendertarget) = 0;

            /// @brief Information of the Texture
            ///
            /// @returns The Data
            ///
            virtual void* GetData() = 0;

            /// @brief Creates a CubeMap Texture, cannot be an editable Texture
            ///
            /// @param Pointer to the Pixels Array used
            /// @param Width of the image
            /// @param Height of the image
            ///
            virtual void CreateCubeMapFromMemory(uint8** a_ppPixels, int32 Width, int32 Height) = 0;

            /// @brief Loads a Texture from Memory
            ///
            /// @param Pointer to the Pixels used
            /// @param Width of the image
            /// @param Height of the image
            ///
            virtual void LoadTextureFromMemory(uint8* a_pPixels, int32 a_Width, int32 a_Height) = 0;

            /// @brief Save a Texture to File
            ///
            /// @param Path where its saved
            ///
            virtual void SaveTextureToFile(const char8* a_pPath) = 0;

            /// @brief Set the Pixels of a Texture
            ///
            /// @param Pixels as Array
            ///
            virtual void SetPixels(uint8* a_pPixels) = 0;
        };

    }
}

#endif /* _ITEXTURE2D_H_ */
