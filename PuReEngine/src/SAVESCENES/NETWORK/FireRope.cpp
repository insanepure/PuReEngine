#include "include/FireRope.h"

namespace Game
{
    CFireRope::CFireRope(int32 a_Count, float32 a_Speed, PuRe_Sprite* a_pFireSprite) : m_Count(a_Count), m_Speed(a_Speed), m_pFireSprite(a_pFireSprite)
    {
        m_ppFireParts = new CFirePart*[a_Count];
        for (int32 i = 0; i < a_Count; i++)
        {
            //create new Part
            PuRe_Vector3F partPosition(i*0.02f, 0.0f, 0.0f);
            this->m_ppFireParts[i] = new CFirePart(partPosition, i, a_Count - 1);
        }
    }

    CFireRope::~CFireRope()
    {
        for (int32 i = 0; i < this->m_Count; i++)
        {
            SAFE_DELETE(this->m_ppFireParts[i]);
        }
        SAFE_DELETE(this->m_pFireSprite);
    }

    void CFireRope::Rotate(float32 a_ElapsedTime)
    {
        for (int32 i = 0; i < this->m_Count; i++)
        {
            this->m_ppFireParts[i]->Rotate(a_ElapsedTime, this->m_Speed);
        }
        if ((sin(a_ElapsedTime*this->m_Speed) / 2.0f) < -0.49f)
        {
            this->m_CanHit = true;
        }
        else
            this->m_CanHit = false;
    }

    void CFireRope::IncreaseSpeed(float32 a_IncreaseSpeed)
    {
        this->m_Speed += a_IncreaseSpeed;
    }

    void CFireRope::Display(PuRe_Camera* a_Camera)
    {
        for (int32 i = 0; i < this->m_Count; i++)
        {
            this->m_ppFireParts[i]->Display(a_Camera,this->m_pFireSprite);
        }
    }
}