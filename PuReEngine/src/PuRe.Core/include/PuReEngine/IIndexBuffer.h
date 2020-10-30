#ifndef _IINDEXBUFFER_H_
#define _IINDEXBUFFER_H_

// PuReEngine specific includes
#include "Defines.h"

// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {
        /// @brief Base Interface for a Index Buffer
        ///
        struct IIndexBuffer
        {
            /// @brief Destructor
            ///
            virtual ~IIndexBuffer() {};
            /// @brief Return the IndexBuffer
            ///
            /// @returns The Index Buffer
            ///
            virtual void* GetData() = 0;

            /// @brief Return the size of the Index
            ///
            /// @returns Size as unsigned int
            ///
            virtual int32 GetSize() = 0;

            /// @brief Lock the Buffer so it can be written on
            ///
            /// @returns the writable Data
            ///
            virtual void* Lock() = 0;

            /// @brief Unlock the Buffer and save the written Data
            ///
            virtual void Unlock() = 0;
        };
    }
}

#endif /* _IINDEXBUFFER_H_ */