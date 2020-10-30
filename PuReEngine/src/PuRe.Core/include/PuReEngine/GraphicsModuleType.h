#ifndef _GRAPHICSMODULETYPE_H_
#define _GRAPHICSMODULETYPE_H_

namespace PuReEngine
{
    namespace Core
    {
        /// @brief An enumeration of available graphics modules
        ///
        enum EGraphicsModuleType
        {
            /// @brief Direct3D10 graphics module
            ///
            Direct3D10,
            /// @brief Direct3D11 graphics module
            ///
            Direct3D11,
            /// @brief OpenGL graphics module
            ///
            OpenGL
        };
    }
}

#endif /* _GRAPHICSMODULETYPE_H_ */