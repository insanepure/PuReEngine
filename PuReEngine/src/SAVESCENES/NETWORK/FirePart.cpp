#include "include/FirePart.h"

namespace Game
{
    CFirePart::CFirePart(PuRe_Vector3F a_Position, int32 a_Count, int32 a_MaxCount) : m_Position(a_Position), m_Count(a_Count), m_MaxCount(a_MaxCount)
    {

    }

    void CFirePart::Rotate(float32 a_ElapsedTime, float32 a_Speed)
    {
        PuRe_Vector3F addRotation = this->m_Position;
        float32 Diff = sin((((float32)this->m_Count / (float32)this->m_MaxCount))*PuRe_PI) / 4;

        addRotation.Y = (sin(a_ElapsedTime*a_Speed) / 2.0f)*Diff;
        addRotation.Z = (cos(a_ElapsedTime*a_Speed) / 2.0f)*Diff;
        this->m_Position = addRotation;
    }

    void CFirePart::Display(PuRe_Camera* a_Camera, PuRe_Sprite* a_pFireSprite)
    {
        PuRe_Vector3F size(0.02f,0.02f,1.0f);
        if (this->m_Count == 0||this->m_Count == this->m_MaxCount)
        {
            size.X *= 2;
            size.Y *= 2;
        }
        a_pFireSprite->Draw(a_Camera, this->m_Position, size, PuRe_Vector3F(), PuRe_Vector3F());
    }
}