#ifndef _VECTOR3_H_
#define _VECTOR3_H_

// PuReEngine specific includes
#include "Defines.h"
#include "Vector2.h"

// Standard C specific headers
#include <math.h>

namespace PuReEngine
{
    namespace Core
    {

        /*!
        * @brief Represents a three component vector of a specified type.
        *
        * @remarks There are predefined vectors you may use during development:
        *
        * Vector3F - A 32 bit float vector
        * Vector3D - A 64 bit float vector
        * Vector3B - A 8 bit integer vector
        * Vector3S - A 16 bit integer vector
        * Vector3I - A 32 bit integer vector
        * Vector3L - A 64 bit integer vector
        */
        template<class T>
        struct Vector3
        {
            // ------------------------------------------------------------------------
            // MEMBERS
            // ------------------------------------------------------------------------

            T X; // X-coordinate
            T Y; // Y-coordinate
            T Z; // Z-coordinate

            // ------------------------------------------------------------------------
            // METHODS
            // ------------------------------------------------------------------------

            /*!
            * @brief Creates an instance of Vector3<T>.
            */
            inline Vector3()
            {
                this->X = this->Y = this->Z = 0;
            }

            /*!
            * @brief Creates an instance of Vector3<T>.
            *
            * @param The x-coordinate.
            * @param The y-coordinate.
            * @param The z-coordinate.
            */
            inline Vector3(T x, T y, T z)
            {
                this->X = x;
                this->Y = y;
                this->Z = z;
            }

            /*!
            * @brief Creates an instance of Vector3<T>.
            *
            * @param A Vector2<T> instance.
            * @param The z-coordinate.
            */
            inline Vector3(const Vector2<T> & vec, T z)
            {
                this->X = vec.X;
                this->Y = vec.Y;
                this->Z = z;
            }

            /*!
            * @brief Returns the magnitude (length) of this Vector3<T>.
            *
            * @returns The magnitude (length) of this Vector3<T>.
            */
            inline T Length() const
            {
                return sqrt(this->X * this->X + this->Y * this->Y + this->Z * this->Z);
            }

            /*!
            * @brief Normalizes this instance of Vector3<T>.
            */
            inline void Normalize()
            {
                T length = this->Length();

                if (length > 0.000000000001f || length < -0.000000000001f)
                {
                    this->X /= length;
                    this->Y /= length;
                    this->Z /= length;
                }
            }

            // ------------------------------------------------------------------------
            // OPERATORS
            // ------------------------------------------------------------------------

            /*!
            * @brief Returns a pointer to the internal vector array.
            *
            * @returns A pointer to the internal vector array.
            */
            inline operator T*() const
            {
                return const_cast<T*>(&this->X);
            }

            /*!
            * @brief Calculates the negotiation of the Vector.
            *
            * @returns A negotiated Vector3<T>.
            */
            inline Vector3<T> operator-() const
            {
                return Vector3<T>(-this->X, -this->Y, -this->Z);
            }

            /*!
            * @brief Calculates the sum of this instance components' and the
            * specified vec components' and returns the result as a new Vector3<T> instance.
            *
            * @param A Vector3<T> instance.
            *
            * @returns A Vector3<T> containing the result of the sum operation.
            */
            inline Vector3<T> operator+(const Vector3<T> &vec) const
            {
                return Vector3<T>(this->X + vec.X, this->Y + vec.Y, this->Z + vec.Z);
            }

            /*!
            * @brief Calculates the sum of this instance components' and the
            * specified vec components' and returns the result as a new Vector3<T> instance.
            *
            * @param A Vector2<T> instance.
            *
            * @returns A Vector3<T> containing the result of the sum operation.
            */
            inline Vector3<T> operator+(const Vector2<T> &vec) const
            {
                return Vector3<T>(this->X + vec.X, this->Y + vec.Y, this->Z);
            }

            /*!
            * @brief Calculates the difference of this instance components' and the
            * specified vec components' and returns the result as a new Vector3<T> instance.
            *
            * @param A Vector3<T> instance.
            *
            * @returns A Vector3<T> containing the result of the difference operation.
            */
            inline Vector3<T> operator-(const Vector3<T> &vec) const
            {
                return Vector3<T>(this->X - vec.X, this->Y - vec.Y, this->Z - vec.Z);
            }

            /*!
            * @brief Calculates the difference of this instance components' and the
            * specified vec components' and returns the result as a new Vector3<T> instance.
            *
            * @param A Vector2<T> instance.
            *
            * @returns A Vector3<T> containing the result of the difference operation.
            */
            inline Vector3<T> operator-(const Vector2<T> &vec) const
            {
                return Vector3<T>(this->X - vec.X, this->Y - vec.Y, this->Z);
            }

            /*!
            * @brief Calculates the multiplication of this instance components' and the
            * specified vec components' and returns the result as a new Vector3<T> instance.
            *
            * @param A Vector3<T> instance.
            *
            * @returns A Vector3<T> containing the result of the multiplication operation.
            */
            inline Vector3<T> operator*(const Vector3<T> &vec) const
            {
                return Vector3<T>(vec.X * this->X, vec.Y * this->Y, vec.Z * this->Z);
            }

            /*!
            * @brief Calculates the multiplication of this instance components' and the
            * specified vec components' and returns the result as a new Vector3<T> instance.
            *
            * @param A Vector2<T> instance.
            *
            * @returns A Vector3<T> containing the result of the multiplication operation.
            */
            inline Vector3<T> operator*(const Vector2<T> &vec) const
            {
                return Vector3<T>(vec.X * this->X, vec.Y * this->Y, this->Z);
            }

            /*!
            * @brief Calculates the multiplication of this instance components' and the
            * specified T component and returns the result as a new Vector3<T> instance.
            *
            * @param A T value.
            *
            * @returns A Vector3<T> containing the result of the multiplication operation.
            */
            inline Vector3<T> operator*(const T &val) const
            {
                return Vector3<T>(val * this->X, val * this->Y, val * this->Z);
            }

            /*!
            * @brief Adds the specified Vector3<T> instance to this instance.
            *
            * @param A Vector3<T> instance.
            *
            * @returns This Vector3<T> instance.
            */
            inline Vector3<T> operator+=(const Vector3<T> &vec)
            {
                this->X += vec.X; this->Y += vec.Y; this->Z += vec.Z;

                return *this;
            }

            /*!
            * @brief Adds the specified Vector2<T> instance to this instance.
            *
            * @param A Vector2<T> instance.
            *
            * @returns This Vector3<T> instance.
            */
            inline Vector3<T> operator+=(const Vector2<T> &vec)
            {
                this->X += vec.X; this->Y += vec.Y;

                return *this;
            }

            /*!
            * @brief Substracts the specified Vector3<T> instance from this instance.
            *
            * @param A Vector3<T> instance.
            *
            * @returns This Vector3<T> instance.
            */
            inline Vector3<T> operator-=(const Vector3<T> &vec)
            {
                this->X -= vec.X; this->Y -= vec.Y; this->Z -= vec.Z;

                return *this;
            }

            /*!
            * @brief Substracts the specified Vector2<T> instance from this instance.
            *
            * @param A Vector2<T> instance.
            *
            * @returns This Vector3<T> instance.
            */
            inline Vector3<T> operator-=(const Vector2<T> &vec)
            {
                this->X -= vec.X; this->Y -= vec.Y;

                return *this;
            }

            /*!
            * @brief Multiplies the specified Vector3<T> instance with this instance.
            *
            * @param A Vector3<T> instance.
            *
            * @returns This Vector3<T> instance.
            */
            inline Vector3<T> operator*=(const Vector3<T> &vec)
            {
                this->X *= vec.X; this->Y *= vec.Y; this->Z *= vec.Z;

                return *this;
            }

            /*!
            * @brief Multiplies the specified Vector2<T> instance with this instance.
            *
            * @param A Vector2<T> instance.
            *
            * @returns This Vector3<T> instance.
            */
            inline Vector3<T> operator*=(const Vector2<T> &vec)
            {
                this->X *= vec.X; this->Y *= vec.Y;

                return *this;
            }

            /*!
            * @brief Multiplies the specified T value with this instance.
            *
            * @param A Vector3<T> instance.
            *
            * @returns This Vector3<T> instance.
            */
            inline Vector3<T> operator*=(const T &val)
            {
                this->X *= val; this->Y *= val; this->Z *= val;

                return *this;
            }

            /*!
            * @brief Sets this instance equal to the specified Vector3<T> instance.
            *
            * @param A Vector3<T> instance.
            *
            * @returns This Vector3<T> instance.
            */
            inline Vector3<T> operator=(const Vector3<T> &vec)
            {
                this->X = vec.X; this->Y = vec.Y; this->Z = vec.Z;

                return *this;
            }

            /*!
            * @brief Sets this instance equal to the specified Vector2<T> instance.
            *
            * @param A Vector2<T> instance.
            *
            * @returns This Vector3<T> instance.
            */
            inline Vector3<T> operator=(const Vector2<T> &vec)
            {
                this->X = vec.X; this->Y = vec.Y;

                return *this;
            }

            /*!
            * @brief Indicates whether this instance equals to the specified Vector3<T> instance.
            *
            * @param A Vector3<T> instance.
            *
            * @returns This Vector3<T> instance.
            */
            inline bool operator==(const Vector3<T>& vec) const
            {
                if (this->X != vec.X)
                    return false;

                if (this->Y != vec.Y)
                    return false;

                return this->Z == vec.Z;
            }

            /*!
            * @brief Indicates whether this instance equals to the specified Vector2<T> instance.
            *
            * @param A Vector2<T> instance.
            *
            * @returns This Vector3<T> instance.
            */
            inline bool operator==(const Vector2<T>& vec) const
            {
                if (this->X != vec.X)
                    return false;

                return this->Y == vec.Y;
            }

            // ------------------------------------------------------------------------
            // STATIC METHODS
            // ------------------------------------------------------------------------

            /*!
            * @brief Creates a new Vector3<T> instance which components are set to zero.
            *
            * @returns A new Vector3<T> instance.
            */
            inline static Vector3<T> Zero() { return Vector3<T>(); }

            /*!
            * @brief Creates a new Vector3<T> instance which components are set to one.
            *
            * @returns A new Vector3<T> instance.
            */
            inline static Vector3<T> One() { return Vector3<T>(1, 1, 1); }

            /*!
            * @brief Creates a new Vector3<T> instance which x-component is set to one
            * and the others to zero.
            *
            * @returns A new Vector3<T> instance.
            */
            inline static Vector3<T> UnitX() { return Vector3<T>(1, 0, 0); }

            /*!
            * @brief Creates a new Vector3<T> instance which y-component is set to one
            * and the others to zero.
            *
            * @returns A new Vector3<T> instance.
            */
            inline static Vector3<T> UnitY() { return Vector3<T>(0, 1, 0); }

            /*!
            * @brief Creates a new Vector3<T> instance which z-component is set to one
            * and the others to zero.
            *
            * @returns A new Vector3<T> instance.
            */
            inline static Vector3<T> UnitZ() { return Vector3<T>(0, 0, 1); }

            /*!
            * @brief Calculates the cross-product of the specified Vector3<T> instances.
            *
            * @param vec1 The first vector.
            * @param vec2 The second vector.
            *
            * @returns The cross-product of the specified Vector3<T> instances.
            */
            inline static Vector3<T> Cross(const Vector3<T>& vec1, const Vector3<T>& vec2)
            {
                return Vector3<T>(vec1.Y * vec2.Z - vec1.Z * vec2.Y,
                    vec1.Z * vec2.X - vec1.X * vec2.Z,
                    vec1.X * vec2.Y - vec1.Y * vec2.X);
            }

            /*!
            * @brief Calculates the distance between the specified Vector3<T> instances.
            *
            * @param vec1 The first vector.
            * @param vec2 The second vector.
            *
            * @returns The distance between vec1 and vec2.
            */
            inline static T Distance(const Vector3<T>& vec1, const Vector3<T>& vec2)
            {
                return ((Vector3<T>)(vec2 - vec1)).Length();
            }

            /*!
            * @brief Calculates the dot-product of the specified Vector3<T> instances.
            *
            * @param vec1 The first vector.
            * @param vec2 The second vector.
            *
            * @returns The dot-product of the specified Vector3<T> instances.
            */
            inline static T Dot(const Vector3<T>& vec1, const Vector3<T>& vec2)
            {
                return vec1.X * vec2.X + vec1.Y * vec2.Y + vec1.Z * vec2.Z;
            }

            /*!
            * @brief Normalizes the specified Vector3<T> instance.
            *
            * @param vec The Vector3<T> instance to normalize.
            *
            * @returns A normalized Vector3<T> instance of the specified Vector3<T> instance.
            */
            inline static Vector3<T> Normalize(const Vector3<T>& vec)
            {
                Vector3<T> result(vec.X, vec.Y, vec.Z);

                result.Normalize();

                return result;
            }
        };

    }
}

#endif /* _VECTOR3_H_ */