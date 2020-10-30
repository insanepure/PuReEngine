#ifndef _PLANE_H_
#define _PLANE_H_

// PuReEngine specific includes
#include "Defines.h"
#include "Vector3.h"

// Standard C specific headers
#include <math.h>

namespace PuReEngine
{
    namespace Core
    {

        /*!
        * @brief Represents a Plane using a Point and a Normal.
        *
        * @remarks There are predefined Planes you may use during development:
        *
        * QuaternionF - A 32 bit float Plane
        * QuaternionD - A 64 bit float Plane
        * QuaternionB - A 8 bit integer Plane
        * QuaternionS - A 16 bit integer Plane
        * QuaternionI - A 32 bit integer Plane
        * QuaternionL - A 64 bit integer Plane
        */
        template<class T>
        struct Plane
        {
            // ------------------------------------------------------------------------
            // MEMBERS
            // ------------------------------------------------------------------------

            Vector3<T> Point; // Point
            Vector3<T> Normal; // Normal
            T Coefficient;

            // ------------------------------------------------------------------------
            // METHODS
            // ------------------------------------------------------------------------

            /*!
            * @brief Creates an instance of Plane<T>.
            */
            inline Plane()
            {
                Point = Normal = Vector3<T>();
                this->Coefficient = -Vector3<T>::Dot(this->Normal, this->Point);
            }
            /*!
            * @brief Creates an instance of Plane<T>.
            *
            * @param p1 address to the first Vector.
            * @param p2 address to the second Vector.
            * @param p3 address to the third Vector.
            */
            inline Plane(Vector3<T> &a_rP1, Vector3<T> &a_rP2, Vector3<T> &a_rP3)
            {
                Vector3<T> aux1 = a_rP1 - a_rP2;
                Vector3<T> aux2 = a_rP3 - a_rP2;

                this->Normal = Vector3<T>::Normalize(Vector3<T>::Cross(a_rP1 - a_rP2, a_rP3 - a_rP3));

                this->Point = a_rP2;

                this->Coefficient = -Vector3<T>::Dot(this->Normal, this->Point);
            }
            /*!
            * @brief Creates an instance of Plane<T>.
            *
            * @param p1 address to the Normal.
            * @param p2 address to the Point
            */
            inline Plane(Vector3<T> &a_rNormal, Vector3<T> &a_rPoint)
            {
                this->Normal = Vector3<T>::Normalize(a_rNormal);
                this->Point = a_rPoint;
                this->Coefficient = -Vector3<T>::Dot(this->Normal, this->Point);
            }
            /*!
            * @brief Calculates the Distance of the Plane
            *
            * @param p1 address to the Plane.
            * @param p2 address to the Point.
            */
            inline static T Distance(Plane<T> &a_rPlane, Vector3<T> &a_rPoint)
            {
                return a_rPlane.Coefficient + Vector3<T>::Dot(a_rPlane.Normal, a_rPoint);
            }
        };
    }
}
#endif /* _PLANE_H_ */