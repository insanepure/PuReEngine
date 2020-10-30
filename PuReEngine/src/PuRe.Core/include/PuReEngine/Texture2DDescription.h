#ifndef _TEXTURE2DDESCRIPTION_H_
#define _TEXTURE2DDESCRIPTION_H_

// Engine specific includes
#include "Defines.h"

namespace PuReEngine 
{
    namespace Core 
    {

        /// @brief Description of a 2D Texture
        ///
        struct STexture2DDescription
        {
            /// @brief Width of the Texture
            ///
            int32 Width;
            
            /// @brief Height of the Texture
            ///
            int32 Height;
            
            /// @brief Bit per Pixel
            ///
            int32 Bpp;
        };

    }
}

#endif /* _TEXTURE2DDESCRIPTION_H_ */