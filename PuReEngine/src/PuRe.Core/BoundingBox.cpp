#include "include/PuReEngine/BoundingBox.h"

namespace PuReEngine
{
    namespace Core
    {
        CBoundingBox::CBoundingBox()
        {

        }

        // **************************************************************************
        // **************************************************************************

        CBoundingBox::CBoundingBox(Vector3<float32> a_Position, Vector3<float32> a_Size) : m_Position(a_Position), m_Size(a_Size)
        {

        }

        // **************************************************************************
        // **************************************************************************
        CBoundingBox::~CBoundingBox()
        {

        }

        // **************************************************************************
        // **************************************************************************
        bool CBoundingBox::Intersect(CBoundingBox& a_Box)
        {
            return
                (
                this->m_Position.X + this->m_Size.X >= a_Box.m_Position.X &&
                this->m_Position.X <= a_Box.m_Position.X + a_Box.m_Size.X &&
                this->m_Position.Y + this->m_Size.Y >= a_Box.m_Position.Y &&
                this->m_Position.Y <= a_Box.m_Position.Y + a_Box.m_Size.Y &&
                this->m_Position.Z + this->m_Size.Z >= a_Box.m_Position.Z &&
                this->m_Position.Z <= a_Box.m_Position.Z + a_Box.m_Size.Z
                );
        }

        // **************************************************************************
        // **************************************************************************
        bool CBoundingBox::Intersect(Vector3<float32>& a_Point)
        {
            return
                (
                this->m_Position.X + this->m_Size.X >= a_Point.X &&
                this->m_Position.X <= a_Point.X &&
                this->m_Position.Y + this->m_Size.Y >= a_Point.Y &&
                this->m_Position.Y <= a_Point.Y &&
                this->m_Position.Z + this->m_Size.X >= a_Point.Z &&
                this->m_Position.Z <= a_Point.Z
                );
        }
    }
}