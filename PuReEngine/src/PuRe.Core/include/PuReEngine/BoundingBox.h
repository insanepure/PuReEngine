#ifndef _BOUNDINGBOX_H_
#define _BOUNDINGBOX_H_

// Engine specific includes
#include "Defines.h"
#include "Vector3.h"


// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {
        /// @brief Bounding Box for Collision
        ///
        class CBoundingBox
        {
        public:
            /// @brief Position of the Box
            ///
            Vector3<float32> m_Position;
            /// @brief Size of the Box
            ///
            Vector3<float32> m_Size;
        public:
            /// @brief Initialize a Bounding Box
            ///
            CBoundingBox();
            /// @brief Initialize a Bounding Box
            ///
            /// @param Position of the Box
            /// @param Size of the Box
            ///
            CBoundingBox(Vector3<float32> a_Position, Vector3<float32> a_Size);
            /// @brief Destroyes a Bounding Box
            ///
            ~CBoundingBox();
        public:
            /// @brief Checks if a box intersects with this Box
            ///
            /// @param The other Box
            ///
            /// @returns true if collide, false if not
            ///
            bool Intersect(CBoundingBox& a_Box);
            /// @brief Checks if a Point intersects with this Box
            ///
            /// @param The Point
            ///
            /// @returns true if collide, false if not
            ///
            bool Intersect(Vector3<float32>& a_Point);


        };
    }
}
#endif /* _BOUNDINGBOX_H_ */