#ifndef _APPLICATIONDESCRIPTION_H_
#define _APPLICATIONDESCRIPTION_H_

// Engine specific includes
#include "WindowDescription.h"
#include "GraphicsDescription.h"

// Declare namespace PuReEngine::Core
namespace PuReEngine 
{
    namespace Core 
    {
    
        /// @brief Description of the Application Object
        ///
        struct SApplicationDescription
        {
            /// @brief The window description.
            ///
            SWindowDescription Window;
            
            ///// @brief The graphics description.
            /////
            SGraphicsDescription Graphics;
        };

    }
}

#endif /* _APPLICATIONDESCRIPTION_H_ */