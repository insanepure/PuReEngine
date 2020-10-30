#ifndef _VECTOR4_H_
#define _VECTOR4_H_

// PuReEngine specific includes
#include "Defines.h"
#include "Vector3.h"

// Standard C specific headers
#include <math.h>

namespace PuReEngine {
    namespace Core {

        /*!
        * @brief Represents a four component vector of a specified type.
        *
        * @remarks There are predefined vectors you may use during development:
        *
        * Vector4F - A 32 bit float vector
        * Vector4D - A 64 bit float vector
        * Vector4B - A 8 bit integer vector
        * Vector4S - A 16 bit integer vector
        * Vector4I - A 32 bit integer vector
        * Vector4L - A 64 bit integer vector
        */
        template<class T>
        struct Vector4
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
            * @brief Creates an instance of Vector4<T>.
            */
            inline Vector4()
            {
                this->X = this->Y = this->Z = 0;
                this->W = 1;
            }

            /*!
            * @brief Creates an instance of Vector4<T>.
            *
            * @param The x-coordinate.
            * @param The y-coordinate.
            * @param The z-coordinate.
            * @param The w-coordinate (default 1).
            */
            inline Vector4(T x, T y, T z, T w = 1)
            {
                this->X = x;
                this->Y = y;
                this->Z = z;
                this->W = w;
            }

            /*!
            * @brief Creates an instance of Vector4<T>.
            *
            * @param A Vector3<T> instance.
            * @param The w-coordinate.
            */
            inline Vector4(const Vector3<T> & vec, T w)
            {
                this->X = vec.X;
                this->Y = vec.Y;
                this->Z = vec.Z;
                this->W = w;
            }

            /*!
            * @brief Returns the magnitude (length) of this Vector4<T>.
            *
            * @returns The magnitude (length) of this Vector4<T>.
            */
            inline T Length() const
            {
                return sqrt(this->X * this->X + this->Y * this->Y + this->Z * this->Z);
            }

            /*!
            * @brief Normalizes this instance of Vector4<T>.
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
            * @brief Returns a Vector3<T> from this Vector4<T>.
            *
            * @returns A Vector3<T> containing the Values from the Vector4<T>.
            */
            inline operator Vector3<T>() const
            {
                return Vector3<T>(this->X,this->Y,this->Z);
            }
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
            * specified vec components' and returns the result as a new Vector4<T> instance.
            *
            * @param A Vector4<T> instance.
            *
            * @returns A Vector4<T> containing the result of the sum operation.
            */
            inline Vector4<T> operator+(const Vector4<T> &vec) const
            {
                return Vector4<T>(this->X + vec.X, this->Y + vec.Y, this->Z + vec.Z, this->W);
            }

            /*!
            * @brief Calculates the sum of this instance components' and the
            * specified vec components' and returns the result as a new Vector4<T> instance.
            *
            * @param A Vector3<T> instance.
            *
            * @returns A Vector4<T> containing the result of the sum operation.
            */
            inline Vector4<T> operator+(const Vector3<T> &vec) const
            {
                return Vector4<T>(this->X + vec.X, this->Y + vec.Y, this->Z + vec.Z, this->W);
            }

            /*!
            * @brief Calculates the difference of this instance components' and the
            * specified vec components' and returns the result as a new Vector4<T> instance.
            *
            * @param A Vector4<T> instance.
            *
            * @returns A Vector4<T> containing the result of the difference operation.
            */
            inline Vector4<T> operator-(const Vector4<T> &vec) const
            {
                return Vector4<T>(this->X - vec.X, this->Y - vec.Y, this->Z - vec.Z, this->W);
            }

            /*!
            * @brief Calculates the difference of this instance components' and the
            * specified vec components' and returns the result as a new Vector4<T> instance.
            *
            * @param A Vector3<T> instance.
            *
            * @returns A Vector4<T> containing the result of the difference operation.
            */
            inline Vector4<T> operator-(const Vector3<T> &vec) const
            {
                return Vector4<T>(this->X - vec.X, this->Y - vec.Y, this->Z - vec.Z, this->W);
            }

            /*!
            * @brief Calculates the multiplication of this instance components' and the
            * specified vec components' and returns the result as a new Vector4<T> instance.
            *
            * @param A Vector4<T> instance.
            *
            * @returns A Vector4<T> containing the result of the multiplication operation.
            */
            inline Vector4<T> operator*(const Vector4<T> &vec) const
            {
                return Vector4<T>(vec.X * this->X, vec.Y * this->Y, vec.Z * this->Z, this->W);
            }

            /*!
            * @brief Calculates the multiplication of this instance components' and the
            * specified vec components' and returns the result as a new Vector4<T> instance.
            *
            * @param A Vector3<T> instance.
            *
            * @returns A Vector4<T> containing the result of the multiplication operation.
            */
            inline Vector4<T> operator*(const Vector3<T> &vec) const
            {
                return Vector4<T>(vec.X * this->X, vec.Y * this->Y, vec.Z * this->Z, this->W);
            }

            /*!
            * @brief Calculates the multiplication of this instance components' and the
            * specified T component and returns the result as a new Vector4<T> instance.
            *
            * @param A T value.
            *
            * @returns A Vector4<T> containing the result of the multiplication operation.
            */
            inline Vector4<T> operator*(const T &val) const
            {
                return Vector4<T>(val * this->X, val * this->Y, val * this->Z, this->W);
            }

            /*!
            * @brief Adds the specified Vector4<T> instance to this instance.
            *
            * @param A Vector4<T> instance.
            *
            * @returns This Vector4<T> instance.
            */
            inline Vector4<T> operator+=(const Vector4<T> &vec)
            {
                this->X += vec.X; this->Y += vec.Y; this->Z += vec.Z;

                return *this;
            }

            /*!
            * @brief Adds the specified Vector3<T> instance to this instance.
            *
            * @param A Vector3<T> instance.
            *
            * @returns This Vector4<T> instance.
            */
            inline Vector4<T> operator+=(const Vector3<T> &vec)
            {
                this->X += vec.X; this->Y += vec.Y; this->Z += vec.Z;

                return *this;
            }

            /*!
            * @brief Substracts the specified Vector4<T> instance from this instance.
            *
            * @param A Vector4<T> instance.
            *
            * @returns This Vector4<T> instance.
            */
            inline Vector4<T> operator-=(const Vector4<T> &vec)
            {
                this->X -= vec.X; this->Y -= vec.Y; this->Z -= vec.Z;

                return *this;
            }

            /*!
            * @brief Substracts the specified Vector3<T> instance from this instance.
            *
            * @param A Vector3<T> instance.
            *
            * @returns This Vector4<T> instance.
            */
            inline Vector4<T> operator-=(const Vector3<T> &vec)
            {
                this->X -= vec.X; this->Y -= vec.Y; this->Z -= vec.Z;

                return *this;
            }

            /*!
            * @brief Multiplies the specified Vector4<T> instance with this instance.
            *
            * @param A Vector4<T> instance.
            *
            * @returns This Vector4<T> instance.
            */
            inline Vector4<T> operator*=(const Vector4<T> &vec)
            {
                this->X *= vec.X; this->Y *= vec.Y; this->Z *= vec.Z;

                return *this;
            }

            /*!
            * @brief Multiplies the specified Vector3<T> instance with this instance.
            *
            * @param A Vector3<T> instance.
            *
            * @returns This Vector4<T> instance.
            */
            inline Vector4<T> operator*=(const Vector3<T> &vec)
            {
                this->X *= vec.X; this->Y *= vec.Y; this->Z *= vec.Z;

                return *this;
            }

            /*!
            * @brief Multiplies the specified T value with this instance.
            *
            * @param A Vector4<T> instance.
            *
            * @returns This Vector4<T> instance.
            */
            inline Vector4<T> operator*=(const T &val)
            {
                this->X *= val; this->Y *= val; this->Z *= val; this->W *= val;

                return *this;
            }

            /*!
            * @brief Sets this instance equal to the specified Vector4<T> instance.
            *
            * @param A Vector4<T> instance.
            *
            * @returns This Vector4<T> instance.
            */
            inline Vector4<T> operator=(const Vector4<T> &vec)
            {
                this->X = vec.X; this->Y = vec.Y; this->Z = vec.Z; this->W = vec.W;

                return *this;
            }

            /*!
            * @brief Sets this instance equal to the specified Vector3<T> instance.
            *
            * @param A Vector3<T> instance.
            *
            * @returns This Vector4<T> instance.
            */
            inline Vector4<T> operator=(const Vector3<T> &vec)
            {
                this->X = vec.X; this->Y = vec.Y; this->Z = vec.Z;

                return *this;
            }

            /*!
            * @brief Indicates whether this instance equals to the specified Vector4<T> instance.
            *
            * @param A Vector4<T> instance.
            *
            * @returns boolean whether the param is the same as this.
            */
            inline bool operator==(const Vector4<T>& vec) const
            {
                if (this->X != vec.X)
                    return false;

                if (this->Y != vec.Y)
                    return false;

                if (this->Z != vec.Z)
                    return false;

                return this->W == vec.W;
            }

            /*!
            * @brief Indicates whether this instance equals to the specified Vector3<T> instance.
            *
            * @param A Vector3<T> instance.
            *
            * @returns boolean whether the param is the same as this.
            */
            inline bool operator==(const Vector3<T>& vec) const
            {
                if (this->X != vec.X)
                    return false;

                if (this->Y != vec.Y)
                    return false;

                return this->Z == vec.Z;
            }

            // ------------------------------------------------------------------------
            // STATIC METHODS
            // ------------------------------------------------------------------------

            /*!
            * @brief Creates a new Vector4<T> instance which components are set to zero.
            *
            * @returns A new Vector4<T> instance.
            */
            inline static Vector4<T> Zero() { return Vector4<T>(); }

            /*!
            * @brief Creates a new Vector4<T> instance which components are set to one.
            *
            * @returns A new Vector4<T> instance.
            */
            inline static Vector4<T> One() { return Vector4<T>(1, 1, 1); }

            /*!
            * @brief Creates a new Vector4<T> instance which x-component is set to one
            * and the others to zero.
            *
            * @returns A new Vector4<T> instance.
            */
            inline static Vector4<T> UnitX() { return Vector4<T>(1, 0, 0); }

            /*!
            * @brief Creates a new Vector4<T> instance which y-component is set to one
            * and the others to zero.
            *
            * @returns A new Vector4<T> instance.
            */
            inline static Vector4<T> UnitY() { return Vector4<T>(0, 1, 0); }

            /*!
            * @brief Creates a new Vector4<T> instance which z-component is set to one
            * and the others to zero.
            *
            * @returns A new Vector4<T> instance.
            */
            inline static Vector4<T> UnitZ() { return Vector4<T>(0, 0, 1); }

            /*!
            * @brief Calculates the cross-product of the specified Vector4<T> instances.
            *
            * @param vec1 The first vector.
            * @param vec2 The second vector.
            *
            * @returns The cross-product of the specified Vector4<T> instances.
            */
            inline static Vector4<T> Cross(const Vector4<T>& vec1, const Vector4<T>& vec2)
            {
                return Vector4<T>(vec1.Y * vec2.Z - vec1.Z * vec2.Y,
                    vec1.Z * vec2.X - vec1.X * vec2.Z,
                    vec1.X * vec2.Y - vec1.Y * vec2.X);
            }

            /*!
            * @brief Calculates the distance between the specified Vector4<T> instances.
            *
            * @param vec1 The first vector.
            * @param vec2 The second vector.
            *
            * @returns The distance between vec1 and vec2.
            */
            inline static T Distance(const Vector4<T>& vec1, const Vector4<T>& vec2)
            {
                return ((Vector4<T>)(vec2 - vec1)).Length();
            }

            /*!
            * @brief Calculates the dot-product of the specified Vector4<T> instances.
            *
            * @param vec1 The first vector.
            * @param vec2 The second vector.
            *
            * @returns The dot-product of the specified Vector4<T> instances.
            */
            inline static T Dot(const Vector4<T>& vec1, const Vector4<T>& vec2)
            {
                return vec1.X * vec2.X + vec1.Y * vec2.Y + vec1.Z * vec2.Z;
            }

            /*!
            * @brief Normalizes the specified Vector4<T> instance.
            *
            * @param vec The Vector4<T> instance to normalize.
            *
            * @returns A normalized Vector4<T> instance of the specified Vector4<T> instance.
            */
            inline static Vector4<T> Normalize(const Vector4<T>& vec)
            {
                Vector4<T> result(vec.X, vec.Y, vec.Z);

                result.Normalize();

                return result;
            }
        };

    }
}

#endif /* _VECTOR4_H_ */