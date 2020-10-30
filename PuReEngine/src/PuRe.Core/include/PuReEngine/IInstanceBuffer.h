#ifndef _IINSTANCEBUFFER_H_
#define _IINSTANCEBUFFER_H_

// PuReEngine specific includes
#include "Matrix.h"
#include "Color.h"
#include "Defines.h"

// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {
        /// @brief Instance Structure
        ///
        struct SInstance
        {
            Matrix<float32> World;
            Color Color;
        };
        inline bool operator==(const SInstance& lhs, const SInstance& rhs)
        {
            return
                lhs.World == rhs.World && lhs.Color == rhs.Color;

        }
        /// @brief Base Interface for a Instance Buffer
        ///
        struct IInstanceBuffer
        {
            /// @brief Destroyes an Instance of InstanceBuffer
            ///
            virtual ~IInstanceBuffer() {};
            /// @brief Get the Data of the Buffer
            ///
            /// @returns the Buffer Data
            ///
            virtual void* GetData() = 0;

            /// @brief Get the Size of the Buffer
            ///
            /// @returns the Buffer Size
            ///
            virtual int32 GetSize() = 0;

            /// @brief Get the Amount of Stride of the Buffer
            ///
            /// @returns the Buffer Stride Amount
            ///
            virtual int32 GetStride() = 0;

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

#endif /* _IINSTANCEBUFFER_H_ */