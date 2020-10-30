#ifndef _VECTOR2_H_
#define _VECTOR2_H_

// PuReEngine specific includes
#include "Defines.h"

// Standard C specific headers
#include <math.h>

namespace PuReEngine
{
    namespace Core
    {

        /*!
        * @brief Represents a two component vector of a specified type.
        *
        * @remarks There are predefined vectors you may use during development:
        *
        * Vector2F - A 32 bit float vector
        * Vector2D - A 64 bit float vector
        * Vector2B - A 8 bit integer vector
        * Vector2S - A 16 bit integer vector
        * Vector2I - A 32 bit integer vector
        * Vector2L - A 64 bit integer vector
        */
        template<class T>
        struct Vector2
        {
            // ------------------------------------------------------------------------
            // MEMBERS
            // ------------------------------------------------------------------------

            T X; // X-coordinate
            T Y; // Y-coordinate

            // ------------------------------------------------------------------------
            // METHODS
            // ------------------------------------------------------------------------

            /*!
            * @brief Creates an instance of Vector2<T>.
            */
            inline Vector2()
            {
                this->X = this->Y = 0;
            }

            /*!
            * @brief Creates an instance of Vector2<T>.
            *
            * @param The x-coordinate.
            * @param The y-coordinate.
            */
            inline Vector2(T x, T y)
            {
                this->X = x;
                this->Y = y;
            }


            /*!
            * @brief Returns the magnitude (length) of this Vector2<T>.
            *
            * @returns The magnitude (length) of this Vector2<T>.
            */
            inline T Length() const
            {
                return sqrt(this->X * this->X + this->Y * this->Y);
            }

            /*!
            * @brief Normalizes this instance of Vector2<T>.
            */
            inline void Normalize()
            {
                T length = this->Length();

                if (length > 0.000000000001f || length < -0.000000000001f)
                {
                    this->X /= length;
                    this->Y /= length;
                }
            }

            /*!
            * @brief Returns the side vector which is perpendicular to this instance of Vector2<T>.
            *
            * @returns The side vector which is perpendicular to this instance of Vector2<T>.
            */
            inline Vector2 Side()
            {
                return Vector2<T>(this->Y, -this->X);
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
            * @brief Calculates the sum of this instance components' and the
            * specified vec components' and returns the result as a new Vector2<T> instance.
            *
            * @param A Vector2<T> instance.
            *
            * @returns A Vector2<T> containing the result of the sum operation.
            */
            inline Vector2<T> operator+(const Vector2<T>& vec) const
            {
                return Vector2<T>(this->X + vec.X, this->Y + vec.Y);
            }

            /*!
            * @brief Calculates the difference of this instance components' and the
            * specified vec components' and returns the result as a new Vector2<T> instance.
            *
            * @param A Vector2<T> instance.
            *
            * @returns A Vector2<T> containing the result of the difference operation.
            */
            inline Vector2<T> operator-(const Vector2<T>& vec) const
            {
                return Vector2<T>(this->X - vec.X, this->Y - vec.Y);
            }

            /*!
            * @brief Calculates the multiplication of this instance components' and the
            * specified vec components' and returns the result as a new Vector2<T> instance.
            *
            * @param A Vector2<T> instance.
            *
            * @returns A Vector2<T> containing the result of the multiplication operation.
            */
            inline Vector2<T> operator*(const Vector2<T>& vec) const
            {
                return Vector2<T>(vec.X * this->X, vec.Y * this->Y);
            }

            /*!
            * @brief Calculates the multiplication of this instance components' and the
            * specified T component and returns the result as a new Vector2<T> instance.
            *
            * @param A T value.
            *
            * @returns A Vector2<T> containing the result of the multiplication operation.
            */
            inline Vector2<T> operator*(const T& val) const
            {
                return Vector2<T>(val * this->X, val * this->Y);
            }

            /*!
            * @brief Adds the specified Vector2<T> instance to this instance.
            *
            * @param A Vector2<T> instance.
            *
            * @returns This Vector2<T> instance.
            */
            inline Vector2<T> operator+=(const Vector2<T>& vec)
            {
                this->X += vec.X; this->Y += vec.Y;

                return *this;
            }

            /*!
            * @brief Substracts the specified Vector2<T> instance from this instance.
            *
            * @param A Vector2<T> instance.
            *
            * @returns This Vector2<T> instance.
            */
            inline Vector2<T> operator-=(const Vector2<T>& vec)
            {
                this->X -= vec.X; this->Y -= vec.Y;

                return *this;
            }

            /*!
            * @brief Multiplies the specified Vector2<T> instance with this instance.
            *
            * @param A Vector2<T> instance.
            *
            * @returns This Vector2<T> instance.
            */
            inline Vector2<T> operator*=(const Vector2<T>& vec)
            {
                this->X *= vec.X; this->Y *= vec.Y;

                return *this;
            }

            /*!
            * @brief Multiplies the specified T value with this instance.
            *
            * @param A Vector2<T> instance.
            *
            * @returns This Vector2<T> instance.
            */
            inline Vector2<T> operator*=(const T& val)
            {
                this->X *= val; this->Y *= val;

                return *this;
            }

            /*!
            * @brief Sets this instance equal to the specified Vector2<T> instance.
            *
            * @param A Vector2<T> instance.
            *
            * @returns This Vector2<T> instance.
            */
            inline Vector2<T> operator=(const Vector2<T>& vec)
            {
                this->X = vec.X; this->Y = vec.Y;

                return *this;
            }

            /*!
            * @brief Indicates whether this instance equals to the specified Vector2<T> instance.
            *
            * @param A Vector2<T> instance.
            *
            * @returns This Vector2<T> instance.
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
            * @brief Creates a new Vector2<T> instance which components are set to zero.
            *
            * @returns A new Vector2<T> instance.
            */
            inline static Vector2<T> Zero() { return Vector2<T>(); }

            /*!
            * @brief Creates a new Vector2<T> instance which components are set to one.
            *
            * @returns A new Vector2<T> instance.
            */
            inline static Vector2<T> One() { return Vector2<T>(1, 1); }

            /*!
            * @brief Creates a new Vector2<T> instance which x-component is set to one
            * and the others to zero.
            *
            * @returns A new Vector2<T> instance.
            */
            inline static Vector2<T> UnitX() { return Vector2<T>(1, 0); }

            /*!
            * @brief Creates a new Vector2<T> instance which y-component is set to one
            * and the others to zero.
            *
            * @returns A new Vector2<T> instance.
            */
            inline static Vector2<T> UnitY() { return Vector2<T>(0, 1); }

            /*!
            * @brief Calculates the distance between the specified Vector2<T> instances.
            *
            * @param vec1 The first vector.
            * @param vec2 The second vector.
            *
            * @returns The distance between vec1 and vec2.
            */
            inline static T Distance(const Vector2<T>& vec1, const Vector2<T>& vec2)
            {
                return ((Vector2<T>)(vec2 - vec1)).Length();
            }

            /*!
            * @brief Calculates the dot-product of the specified Vector2<T> instances.
            *
            * @param vec1 The first vector.
            * @param vec2 The second vector.
            *
            * @returns The dot-product of the specified Vector2<T> instances.
            */
            inline static T Dot(const Vector2<T>& vec1, const Vector2<T>& vec2)
            {
                return vec1.X * vec2.X + vec1.Y * vec2.Y;
            }

            /*!
            * @brief Normalizes the specified Vector2<T> instance.
            *
            * @param vec The Vector2<T> instance to normalize.
            *
            * @returns A normalized Vector2<T> instance of the specified Vector2<T> instance.
            */
            inline static Vector2<T> Normalize(const Vector2<T>& vec)
            {
                Vector2<T> result(vec.X, vec.Y);

                result.Normalize();

                return result;
            }
        };

    }
}


#endif /* _VECTOR2_H_ */