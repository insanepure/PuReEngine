#include "include/Ground.h"

namespace Game
{

    CGround::CGround(PuRe_Sprite* a_pGroundSprite) : m_pGroundSprite(a_pGroundSprite)
    {

    }

    CGround::~CGround()
    {
        SAFE_DELETE(this->m_pGroundSprite);
    }

    void CGround::Draw(PuRe_Camera* a_pCamera,PuRe_Vector3F a_Position, PuRe_Vector3F a_Rotation, PuRe_Vector3F a_Size)
    {
        this->m_pGroundSprite->Draw(a_pCamera,a_Position,a_Size,a_Rotation,PuRe_Vector3F(0.5f,0.5f,0.5f));
    }
}