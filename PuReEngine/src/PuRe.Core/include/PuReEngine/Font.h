#ifndef _FONT_H_
#define _FONT_H_

// Engine specific includes
#include "Defines.h"
#include "Sprite.h"


// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {

        /// @brief Simple Font for Text Display
        ///
        class CFont
        {
        private:
            /// @brief Graphic Object
            ///
            IGraphics* m_pGraphics;
            /// @brief To display our Font we use a simple Sprite
            ///
            CSprite* m_pFont;
        public:
            /// @brief Creates a new Instance of Font
            ///
            /// @param Graphic Object
            /// @param Path to the Model
            ///
            CFont(IGraphics* a_pGraphics, const char8* a_pPath);

            /// @brief Destroys the Instance
            ///
            ~CFont();
        public:

            /// @brief Draw the object
            ///
            /// @param Camera Pointer
            /// @param Material used
            /// @param Text drawn
            ///
            void Draw(CCamera* a_pCam, IMaterial* a_pMaterial, const char8* a_pText);

            /// @brief Draw the object
            ///
            /// @param Camera Pointer
            /// @param Material used
            /// @param Text drawn
            /// @param Position of the Font
            /// @param Size of the Font
            /// @param Rotation of the Font
            ///
            void Draw(CCamera* a_pCam, IMaterial* a_pMaterial, const char8* a_pText, Vector3<float32> a_Position, Vector3<float32> a_Size, Vector3<float32> a_Rotation, float32 a_Offset,Color a_Color);

            /// @brief Draw the object
            ///
            /// @param Camera Pointer
            /// @param Material used
            /// @param Text drawn
            /// @param Position of the Font
            /// @param Size of the Font
            /// @param Rotation of the Font
            ///
            void Draw(CCamera* a_pCam, IMaterial* a_pMaterial, const char8* a_pText, Vector3<float32> a_Position, Vector3<float32> a_Size, Matrix<float32> a_Rotation, float32 a_Offset, Color a_Color);
        };
    }
}
#endif /* _FONT_H_ */
