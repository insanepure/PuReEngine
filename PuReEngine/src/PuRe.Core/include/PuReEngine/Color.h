#ifndef _COLOR_H_
#define _COLOR_H_
// Engine specific includes
#include "Defines.h"

#include <cmath>

// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {

        /// @brief Class for Colors
        ///
        class Color
        {
            // ************************************************************************
            // PUBLIC MEMBERS
            // ************************************************************************

        public:

            /// @brief The Color packed
            ///

            /// @brief Red Value
            ///
            float32 R;
            /// @brief Green Value
            ///
            float32 G;
            /// @brief Blue Value
            ///
            float32 B;
            /// @brief Alpha Value
            ///
            float32 A;
            /*!
            * @brief Returns a pointer to the internal vector array.
            *
            * @returns A pointer to the internal vector array.
            */
            inline operator float32*() const
            {
                return const_cast<float32*>(&this->R);
            }

            /*!
            * @brief Indicates whether this instance equals to the specified Vector4<T> instance.
            *
            * @param A Vector4<T> instance.
            *
            * @returns boolean whether the param is the same as this.
            */
            inline bool operator==(const Color& c) const
            {
                if (this->R != c.R)
                    return false;

                if (this->G != c.G)
                    return false;

                if (this->B != c.B)
                    return false;

                return this->A == c.A;
            }

            /// @brief Creates an instance of Color
            ///
            Color()
            {
                this->R = 0.0f;
                this->G = 0.0f;
                this->B = 0.0f;
                this->A = 1.0f;
            }
            /// @brief Creates an instance of Color
            ///
            /// @param Red Amount
            /// @param Green Amount
            /// @param Blue Amount
            /// @param Alpha Amount
            ///
            Color(float32 r, float32 g, float32 b, float32 a = 1.0f)
            {
                this->R = r;
                this->G = g;
                this->B = b;
                this->A = a;
            }
            /// @brief Creates an instance of Color
            ///
            /// @param RGBA as Integer
            ///
            Color(int32 rgba)
            {
                this->R = (rgba >> 24 & 0xff) / 255.0f;
                this->G = (rgba >> 16 & 0xff) / 255.0f;
                this->B = (rgba >> 8 & 0xff) / 255.0f;
                this->A = (rgba & 0xff) / 255.0f;
            }
            /// @brief Duplicates an instance of Color
            ///
            /// @returns a RGBA Color
            ///
            Color(const Color& color)
            {
                this->R = color.R;
                this->G = color.G;
                this->B = color.B;
                this->A = color.A;
            }
            /// @brief Converts ARGB to RGBA
            ///
            /// @param ARGB Value
            ///
            /// @returns a RGBA Color
            ///
            static Color FromARGB(int32 argb)
            {
                return Color(((argb >> 16) & 0xff) / 255.0f,
                    ((argb >> 8) & 0xff) / 255.0f,
                    ((argb)& 0xff) / 255.0f,
                    ((argb >> 24) & 0xff) / 255.0f);
            }
            /// @brief Converts RGBA to RGBA
            ///
            /// @param RGBA Value
            ///
            /// @returns a RGBA Color
            ///
            static Color FromRGBA(int32 rgba)
            {
                return Color(((rgba >> 24) & 0xff) / 255.0f,
                    ((rgba >> 16) & 0xff) / 255.0f,
                    ((rgba >> 8) & 0xff) / 255.0f,
                    (rgba & 0xff) / 255.0f);
            }
            /// @brief Converts ARGB to RGBA
            ///
            /// @param ARGB Value
            ///
            /// @returns a RGBA Color
            ///
            static Color FromABGR(int32 abgr)
            {
                return Color((abgr & 0xff) / 255.0f,
                    ((abgr >> 8) & 0xff) / 255.0f,
                    ((abgr >> 16) & 0xff) / 255.0f,
                    ((abgr >> 24) & 0xff) / 255.0f);
            }
            /// @brief Converts BGRA to RGBA
            ///
            /// @param BGRA Value
            ///
            /// @returns a RGBA Color
            ///
            static Color FromBGRA(int32 bgra)
            {
                return Color(((bgra >> 8) & 0xff) / 255.0f,
                    ((bgra >> 16) & 0xff) / 255.0f,
                    ((bgra >> 24) & 0xff) / 255.0f,
                    (bgra & 0xff) / 255.0f);
            }
            /// @brief Converts HSV to RGBA
            ///
            /// @param HUE
            /// @param Saturation
            /// @param Value
            ///
            /// @returns a RGBA Color
            ///
            static Color FromHSV(float32 h, float32 s, float32 v)
            {
                float c = v * s;
                float x = c * (1 - std::abs(fmod((h / 60.0f), 2.0f) - 1));
                float m = v - c;

                if (h >= 0.0f && h < 60.0f)
                    return Color((c + m), (x + m), m);
                else if (h >= 60.0f && h < 120.0f)
                    return Color((x + m), (c + m), m);
                else if (h >= 120.0f && h < 180.0f)
                    return Color(m, (c + m), (x + m));
                else if (h >= 180.0f && h < 240.0f)
                    return Color(m, (x + m), (c + m));
                else if (h >= 240.0f && h < 300.0f)
                    return Color((x + m), m, (c + m));

                return Color((c + m), m, (x + m));
            }
            /// @brief Converts a Color to ARGB Integer
            ///
            /// @param a Color Object
            ///
            /// @returns ARGB as integer
            ///
            static uint32 ToARGB(const Color& color)
            {
                return (uint32)(255 * color.A) << 24 |
                    (uint32)(255.0f * color.R) << 16 |
                    (uint32)(255.0f * color.G) << 8 |
                    (uint32)(255.0f * color.B);
            }
            /// @brief Converts a Color to RGBA Integer
            ///
            /// @param a Color Object
            ///
            /// @returns RGBA as integer
            ///
            static uint32 ToRGBA(const Color& color)
            {
                uint32 value;

                value = (uint32)(255 * color.A) |
                    (uint32)(255 * color.R) << 24 |
                    (uint32)(255 * color.G) << 16 |
                    (uint32)(255 * color.B) << 8;

                return value;
            }
            /// @brief Converts a Color to ABGR Integer
            ///
            /// @param a Color Object
            ///
            /// @returns ABGR as integer
            ///
            static uint32 ToABGR(const Color& color)
            {
                return (uint32)(255 * color.A) << 24 |
                    (uint32)(255 * color.B) << 16 |
                    (uint32)(255 * color.G) << 8 |
                    (uint32)(255 * color.R);
            }
            /// @brief Converts a Color to BGRA Integer
            ///
            /// @param a Color Object
            ///
            /// @returns BGRA as integer
            ///
            static uint32 ToBGRA(const Color& color)
            {
                return (uint32)(255 * color.A) |
                    (uint32)(255 * color.R) << 8 |
                    (uint32)(255 * color.G) << 16 |
                    (uint32)(255 * color.B) << 24;
            }
            /// @brief Converts a Color to HSV Integer
            ///
            /// @param a Color Object
            /// @param the returned HUE
            /// @param the returned Saturation
            /// @param the returned Value
            ///
            static void ToHSV(const Color& color, float& h, float& s, float& v)
            {
                float r = color.R;
                float g = color.G;
                float b = color.B;

                float cPuRe_max = PuRe_max(PuRe_max(r, g), b);
                float cPuRe_min = PuRe_min(PuRe_min(r, g), b);
                float delta = cPuRe_max - cPuRe_min;

                uint8 z = PuRe_max(PuRe_max((uint8)(color.R * 255), (uint8)(color.G * 255)), (uint8)(color.B * 255));
                uint8 y = PuRe_min(PuRe_min((uint8)(color.R * 255), (uint8)(color.G * 255)), (uint8)(color.B * 255));
                int x = z - y;

                if (delta <= 0.0000001f || delta >= -0.0000001f)
                    h = 0.0f;
                else if (z == (uint8)(color.R * 255))
                    h = 60 * fmod((g - b) / delta, 6.0f);
                else if (z == (uint8)(color.G * 255))
                    h = 60 * (b - r) / delta + 2;
                else if (z == (uint8)(color.B * 255))
                    h = 60 * (r - g) / delta + 4;

                if (x == 0)
                    s = 0;
                else
                    s = delta / cPuRe_max;

                v = cPuRe_max;
            }

        };

    }
}

#endif /* _COLOR_H_ */