#ifndef _QUATERNION_H_
#define _QUATERNION_H_

// PuReEngine specific includes
#include "Defines.h"
#include "Vector3.h"
#include "Matrix.h"

// Standard C specific headers
#include <math.h>

namespace PuReEngine
{
    namespace Core
    {

        /*!
        * @brief Represents a four component quaternion of a specified type.
        *
        * @remarks There are predefined Quaternions you may use during development:
        *
        * QuaternionF - A 32 bit float Quaternion
        * QuaternionD - A 64 bit float Quaternion
        * QuaternionB - A 8 bit integer Quaternion
        * QuaternionS - A 16 bit integer Quaternion
        * QuaternionI - A 32 bit integer Quaternion
        * QuaternionL - A 64 bit integer Quaternion
        */
        template<class T>
        struct Quaternion
        {
            // ------------------------------------------------------------------------
            // MEMBERS
            // ------------------------------------------------------------------------

            T X; // X-coordinate
            T Y; // Y-coordinate
            T Z; // Z-coordinate
            T W; // W-coordinate

            // ------------------------------------------------------------------------
            // METHODS
            // ------------------------------------------------------------------------

            /*!
            * @brief Creates an instance of Quaternion<T>.
            */
            inline Quaternion()
            {
                this->X = this->Y = this->Z = 0;
                this->W = 1;
            }

            /*!
            * @brief Creates an instance of Quaternion<T>.
            *
            * @param The x value.
            * @param The y value.
            * @param The z value.
            * @param The w value.
            */
            inline Quaternion(T x, T y, T z, T w)
            {
                this->X = x;
                this->Y = y;
                this->Z = z;
                this->W = w;
            }

            /*!
            * @brief Creates an instance of Quaternion<T>.
            *
            * @param The x value.
            * @param The y value.
            * @param The z value.
            * @param The w value.
            */
            inline Quaternion(Vector3<T> vec, T w)
            {
                this->X = vec.X;
                this->Y = vec.Y;
                this->Z = vec.Z;
                this->W = w;
            }

            /*!
            * @brief Creates an instance of Quaternion<T> from Euler Angles in Radians.
            *
            * @param The x-Angle.
            * @param The y-Angle.
            * @param The z-Angle.
            */
            inline Quaternion(T x, T y, T z)
            {
                this->Set(x, y, z);
                this->Normalize();
            }

            /*!
            * @brief Creates an instance of Quaternion<T> from EulerAngles in Radians.
            *
            * @param The Euler Angles.
            */
            inline Quaternion(Vector3<T> vec)
            {
                this->Set(vec.X, vec.Y, vec.Z);
                this->Normalize();
            }

            inline Vector3<T> operator *(const Vector3<T>& vec) const
            {
                Matrix<T> mat = GetMatrix();
                return Vector3<T>(
                    vec.X * mat.M11 + vec.Y * mat.M21 + vec.Z * mat.M31 + mat.M41,
                    vec.X * mat.M12 + vec.Y * mat.M22 + vec.Z * mat.M32 + mat.M42,
                    vec.X * mat.M13 + vec.Y * mat.M23 + vec.Z * mat.M33 + mat.M43);
            }

            inline friend Vector3<T> operator *(const Vector3<T>& vec, Quaternion<T>& m)
            {
                Matrix<T> mat = m.GetMatrix();
                return Vector3<T>(
                    vec.X * mat.M11 + vec.Y * mat.M21 + vec.Z * mat.M31 + mat.M41,
                    vec.X * mat.M12 + vec.Y * mat.M22 + vec.Z * mat.M32 + mat.M42,
                    vec.X * mat.M13 + vec.Y * mat.M23 + vec.Z * mat.M33 + mat.M43);
            }

            inline friend Vector3<T> operator *=(Vector3<T>& vec, Quaternion<T>& m)
            {
                Matrix<T> mat = m.GetMatrix();
                vec.X = vec.X * mat.M11 + vec.Y * mat.M21 + vec.Z * mat.M31 + mat.M41;
                vec.Y = vec.X * mat.M12 + vec.Y * mat.M22 + vec.Z * mat.M32 + mat.M42;
                vec.Z = vec.X * mat.M13 + vec.Y * mat.M23 + vec.Z * mat.M33 + mat.M43;
                return vec;
            }

            /*!
            * @brief Returns the magnitude (length) of this Quaternion<T>.
            *
            * @returns The magnitude (length) of this Quaternion<T>.
            */
            inline T Length() const
            {
                return sqrt(this->W * this->W + this->X * this->X + this->Y * this->Y + this->Z * this->Z);
            }

            /*!
            * @brief Normalizes this instance of Quaternion<T>.
            */
            inline void Normalize()
            {
                T length = this->Length();

                if (length > 0.000000000001f || length < -0.000000000001f)
                {
                    this->W /= length;
                    this->X /= length;
                    this->Y /= length;
                    this->Z /= length;
                }
            }


            /*!
            * @brief Calculates the Matrix of this instance components' and return it.
            *
            * @returns A Matrix<T> containing the result of the calculation.
            */
            inline Matrix<T> GetMatrix()
            {
                Matrix<T> Mat;

                T W2 = 2.0f * this->W;
                T X2 = 2.0f * this->X;
                T Y2 = 2.0f * this->Y;
                T Z2 = 2.0f * this->Z;

                T YY2 = Y*Y2;
                T XX2 = X*X2;
                T ZZ2 = Z*Z2;

                T XY2 = X*Y2;
                T ZW2 = Z*W2;
                T XZ2 = X*Z2;
                T YW2 = Y*W2;
                T ZY2 = Z*Y2;
                T XW2 = X*W2;

                Mat.M11 = 1.0f - YY2 - ZZ2;
                Mat.M12 = XY2 + ZW2;
                Mat.M13 = XZ2 - YW2;
                Mat.M14 = 0;

                Mat.M21 = XY2 - ZW2;
                Mat.M22 = 1.0f - XX2 - ZZ2;
                Mat.M23 = ZY2 + XW2;
                Mat.M24 = 0;

                Mat.M31 = XZ2 + YW2;
                Mat.M32 = ZY2 - XW2;
                Mat.M33 = 1.0f - XX2 - YY2;
                Mat.M34 = 0;

                Mat.M41 = Mat.M42 = Mat.M43 = 0;
                Mat.M44 = 1;

                return Mat;
            }

            /*!
            * @brief Returns the Axis Angles of the Quaternion
            *
            * @returns A Vector3<T> containing the result of the calculation.
            */
            inline Vector3<T> GetAxisAngles()
            {
                Vector3<T> axisAngles;
                axisAngles.X = this->X / sqrt(1 - this->W*this->W);
                axisAngles.Y = this->Y / sqrt(1 - this->W*this->W);
                axisAngles.Z = this->Z / sqrt(1 - this->W*this->W);
                axisAngles *= 2 * acos(this->W);
                return axisAngles;
            }

            /*!
            * @brief Calculates a Quaternion based on the given angles (radians)
            *
            * @param The x-Angle.
            * @param The y-Angle.
            * @param The z-Angle.
            */
            inline void Set(T x, T y, T z)
            {
                T angle;

                angle = x * 0.5f;
                T sr = sin(angle);
                T cr = cos(angle);

                angle = y * 0.5f;
                T sp = sin(angle);
                T cp = cos(angle);

                angle = z * 0.5f;
                T sy = sin(angle);
                T cy = cos(angle);

                T cpcy = cp * cy;
                T spcy = sp * cy;
                T cpsy = cp * sy;
                T spsy = sp * sy;

                this->X = (T)(sr * cpcy - cr * spsy);
                this->Y = (T)(cr * spcy + sr * cpsy);
                this->Z = (T)(cr * cpsy - sr * spcy);
                this->W = (T)(cr * cpcy + sr * spsy);
            }

            /*!
            * @brief Calculates the subtraction of this instance components' and the
            * specified Quaternion components' and returns the result as a new Quaternion<T> instance.
            *
            * @param A Quaternion<T> instance.
            *
            * @returns A Quaternion<T> containing the result of the subtraction operation.
            */
            inline Quaternion<T> operator-(const Quaternion<T> &quat) const
            {
                Quaternion<T> Q;
                Q.X = this->X - quat.X;
                Q.Y = this->Y - quat.Y;
                Q.Z = this->Z - quat.Z;
                Q.W = this->W - quat.W;
                return Q;
            }

            /*!
            * @brief Subtracts the specified Quaternion<T> instance with this instance.
            *
            * @param A Quaternion<T> instance.
            *
            * @returns This Quaternion<T> instance.
            */
            inline Quaternion<T> operator -=(const Quaternion<T>& quat)
            {
                *this = *this - quat;
                return *this;
            }

            /*!
            * @brief Calculates the addition of this instance components' and the
            * specified Quaternion components' and returns the result as a new Quaternion<T> instance.
            *
            * @param A Quaternion<T> instance.
            *
            * @returns A Quaternion<T> containing the result of the addition operation.
            */
            inline Quaternion<T> operator+(const Quaternion<T> &quat) const
            {
                Quaternion<T> Q;
                Q.X = this->X + quat.X;
                Q.Y = this->Y + quat.Y;
                Q.Z = this->Z + quat.Z;
                Q.W = this->W + quat.W;
                return Q;
            }

            /*!
            * @brief Addition the specified Quaternion<T> instance with this instance.
            *
            * @param A Quaternion<T> instance.
            *
            * @returns This Quaternion<T> instance.
            */
            inline Quaternion<T> operator +=(const Quaternion<T>& quat)
            {
                *this = *this + quat;
                return *this;
            }

            /*!
            * @brief Calculates the multiplication of this instance components' and the
            * specified Quaternion components' and returns the result as a new Quaternion<T> instance.
            *
            * @param A Quaternion<T> instance.
            *
            * @returns A Quaternion<T> containing the result of the multiplication operation.
            */
            inline Quaternion<T> operator*(const Quaternion<T> &quat) const
            {
                Quaternion<T> Q;
                Q.W = (this->W * quat.W - this->X * quat.X - this->Y * quat.Y - this->Z * quat.Z);
                Q.X = (this->W * quat.X + this->X * quat.W + this->Y * quat.Z - this->Z * quat.Y);
                Q.Y = (this->W * quat.Y - this->X * quat.Z + this->Y * quat.W + this->Z * quat.X);
                Q.Z = (this->W * quat.Z + this->X * quat.Y - this->Y * quat.X + this->Z * quat.W);
                return Q;
            }

            /*!
            * @brief Multiplies the specified Quaternion<T> instance with this instance.
            *
            * @param A Quaternion<T> instance.
            *
            * @returns This Quaternion<T> instance.
            */
            inline Quaternion<T> operator *=(const Quaternion<T>& quat)
            {
                *this = *this * quat;
                return *this;
            }

            /*!
            * @brief Sets this instance equal to the specified Quaternion<T> instance.
            *
            * @param A Quaternion<T> instance.
            *
            * @returns This Quaternion<T> instance.
            */
            inline Quaternion<T> operator=(const Quaternion<T> &quat)
            {
                this->X = quat.X; this->Y = quat.Y; this->Z = quat.Z; this->W = quat.W;

                return *this;
            }

            /*!
            * @brief Indicates whether this instance equals to the specified Quaternion<T> instance.
            *
            * @param A Quaternion<T> instance.
            *
            * @returns boolean whether the param is the same as this.
            */
            inline bool operator==(const Quaternion<T>& quat) const
            {
                if (this->X != quat.X)
                    return false;

                if (this->Y != quat.Y)
                    return false;

                if (this->Z != quat.Z)
                    return false;

                return this->W == quat.W;
            }

            /*!
            * @brief Indicates whether this instance does not equals to the specified Quaternion<T> instance.
            *
            * @param A Quaternion<T> instance.
            *
            * @returns boolean whether the param is not the same as this.
            */
            inline bool operator!=(const Quaternion<T>& quat) const
            {
                if (this->X == quat.X&&this->Y == quat.Y&&this->Z == quat.Z&&this->W == quat.W)
                    return false;
                return true;
            }

        };

    }

}

#endif /* _QUATERNION_H_ */