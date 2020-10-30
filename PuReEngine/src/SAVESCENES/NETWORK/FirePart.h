#ifndef _FIREPART_H_
#define _FIREPART_H_

// Framework specific includes
#include <PuReEngine/Core.h>
#include <PuReEngine/Defines.h>


namespace Game
{
    class CFirePart
    {
    public:
        /// @brief Position of this Part
        ///
        PuRe_Vector3F m_Position;
        /// @brief Index of the FirePart in Rope
        ///
        int32 m_Count;
        /// @brief May FireParts
        ///
        int32 m_MaxCount;
    public:
        CFirePart(PuRe_Vector3F a_Position, int32 a_Count, int32 a_MaxCount);
    public:
        void Rotate(float32 a_ElapsedTime, float32 a_Speed);
        void Display(PuRe_Camera* a_Camera, PuRe_Sprite* a_pFireSprite);

    };
}
#endif /* _FIREPART_H_ */