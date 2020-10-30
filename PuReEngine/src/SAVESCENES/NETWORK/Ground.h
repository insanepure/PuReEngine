#ifndef _GROUND_H_
#define _GROUND_H_

// Framework specific includes
#include <PuReEngine/Core.h>
#include <PuReEngine/Defines.h>


namespace Game
{
    class CGround
    {
    public:
        /// @brief Sprite we use
        ///
        PuRe_Sprite* m_pGroundSprite;
    public:
        CGround(PuRe_Sprite* a_pGroundSprite);
        ~CGround();
    public:
        void Draw(PuRe_Camera* a_pCamera, PuRe_Vector3F a_Position, PuRe_Vector3F a_Rotation, PuRe_Vector3F a_Size);
    };
}

#endif /*_GROUND_H_*/