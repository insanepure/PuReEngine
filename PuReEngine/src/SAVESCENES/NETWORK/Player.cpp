#include "include/Player.h"
namespace Game
{
    CPlayer::CPlayer(PuRe_Model* a_pModel) : m_pModel(a_pModel)
    {
    }
    void CPlayer::Draw(PuRe_Camera* a_pCamera, PuRe_Vector3F a_Position, PuRe_Vector3F a_Rotation)
    {
        if (this->m_IsPlaying)
        {
            PuRe_Vector3F scalev = PuRe_Vector3F(0.01f, 0.01f, 0.01f);
            PuRe_Vector3F origin = PuRe_Vector3F(scalev.X / 2.0f, scalev.Y / 2.0f, scalev.Z / 2.0f);
            a_Position += this->m_JumpHeight;
            if (this->m_isDead)
                a_Rotation.Z = -90.0f*0.0174532925f;
            this->m_pModel->Draw(a_pCamera,PuRe_Primitive::Triangles, a_Position, scalev, a_Rotation, origin);
        }
    }
    void CPlayer::Jump()
    {
        if (!this->m_IsJumping&&this->m_IsPlaying&&!this->m_isDead)
        {
            this->m_IsJumping = true;
            this->m_JumpTime = 0.0f;
        }
    }
    void CPlayer::Update(float32 a_DeltaTime)
    {
        if (this->m_IsJumping&&this->m_IsPlaying)
        {
            this->m_JumpTime += a_DeltaTime;
            this->m_JumpHeight.Y = sin(this->m_JumpTime*PuRe_PI*1.5f) / 10.0f;
            if (this->m_JumpHeight.Y < 0.0f)
            {
                this->m_IsJumping = false;
                this->m_JumpHeight.Y = 0.0f;
            }
        }
    }
    bool CPlayer::isHit()
    {
        if (this->m_IsPlaying)
            return this->m_JumpHeight.Y < 0.0001f;
        else
            return false;
    }
}