#ifndef _FIREROPE_H_
#define _FIREROPE_H_

// Framework specific includes
#include <PuReEngine/Core.h>
#include <PuReEngine/Defines.h>

// Game specific includes
#include "FirePart.h"

namespace Game
{
    class CFireRope
    {
    public:
        /// @brief Pointer to the FireSprite we initialized before
        ///
        PuRe_Sprite* m_pFireSprite;
        /// @brief Our FirePart Array
        ///
        CFirePart** m_ppFireParts;
        /// @brief Amount of Fire Parts
        ///
        int32 m_Count;
        /// @brief Speed the Rope moves
        ///
        float32 m_Speed;
        /// @brief If Player can be hit
        ///
        bool m_CanHit;
    public:
        CFireRope(int32 a_Count, float32 a_Speed, PuRe_Sprite* a_pFireSprite);
        ~CFireRope();
    public:
        void Rotate(float32 a_ElapsedTime);
        void IncreaseSpeed(float32 a_IncreaseSpeed);
        void Display(PuRe_Camera* a_Camera);
    };
}
#endif /* _FIREROPE_H_ */