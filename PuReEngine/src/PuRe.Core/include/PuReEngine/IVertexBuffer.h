#ifndef _IVERTEXBUFFER_H_
#define _IVERTEXBUFFER_H_

// PuReEngine specific includes
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Defines.h"

// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {
        /// @brief Vertex Structure
        ///
        struct SVertex
        {
            Vector3<float32> Position;
            Vector2<float32> UV;
            Vector3<float32> Color;
            Vector3<float32> Normal;
        };
        inline bool operator==(const SVertex& lhs, const SVertex& rhs)
        {
            return
                lhs.Position == rhs.Position &&
                lhs.UV == rhs.UV &&
                lhs.Normal == rhs.Normal &&
                lhs.Color == rhs.Color;

        }
        /// @brief Base Interface for a Vertex Buffer
        ///
        struct IVertexBuffer
        {
            /// @brief Destroyes an Instance of IVertexBuffer
            ///
            virtual ~IVertexBuffer() {};
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

            /// @brief Return the Vertices from the GPU.
            ///
            virtual SVertex* GetVertices() = 0;
        };

    }
}

#endif /* _IVERTEXBUFFER_H_ */