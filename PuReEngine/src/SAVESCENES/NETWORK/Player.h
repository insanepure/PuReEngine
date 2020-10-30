#ifndef _PLAYER_H_
#define _PLAYER_H_

// Framework specific includes
#include <PuReEngine/Core.h>
#include <PuReEngine/Defines.h>


namespace Game
{
    class CPlayer
    {
    public:
        /// @brief Model for this Player
        ///
        PuRe_Model* m_pModel;
        /// @brief isJumping
        ///
        bool m_IsJumping;
        /// @brief Jump Height
        ///
        PuRe_Vector3F m_JumpHeight;
        /// @brief Jump Time
        ///
        float32 m_JumpTime;
        /// @brief If he is Playing
        ///
        bool m_IsPlaying;
        /// @brief If he is dead
        ///
        bool m_isDead;
    public:
        /// @brief address
        ///
        sockaddr_in sockaddr;
    public:
        CPlayer(PuRe_Model* a_pModel);
    public:
        void Draw(PuRe_Camera* a_pCamera, PuRe_Vector3F a_Position, PuRe_Vector3F a_Rotation);
        void Jump();
        void Update(float32 a_DeltaTime);
        bool isHit();
    };
}
#endif /* _PLAYER_H_ */