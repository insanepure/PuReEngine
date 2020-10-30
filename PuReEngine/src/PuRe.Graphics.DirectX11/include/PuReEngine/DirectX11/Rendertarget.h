#ifndef _RENDERTARGET_H_
#define _RENDERTARGET_H_

// Direct3D specific includes
#include <D3D11.h>
#include <D3DX11.h>

// PuReEngine::Core specific includes
#include "PuReEngine/Defines.h"
#include "PuReEngine/IRendertarget.h"
#include "PuReEngine/IMaterial.h"
#include "PuReEngine/IGraphics.h"
#include "PuReEngine/Vector3.h"
#include "PuReEngine/Vector2.h"
#include "PuReEngine/Matrix.h"
#include "PuReEngine/Color.h"
#include "PuReEngine/Quad.h"
#include "PuReEngine/Camera.h"
#include "PuReEngine/BoundingBox.h"

#include "Texture2D.h"

namespace PuReEngine
{
    namespace Graphics
    {
        namespace DirectX11
        {

            using ::PuReEngine::Core::IRendertarget;
            using ::PuReEngine::Core::IMaterial;
            using ::PuReEngine::Core::IGraphics;
            using ::PuReEngine::Core::Vector3;
            using ::PuReEngine::Core::Vector2;
            using ::PuReEngine::Core::Matrix;
            using ::PuReEngine::Core::Color;
            using ::PuReEngine::Core::Quad;
            using ::PuReEngine::Core::CCamera;
            using ::PuReEngine::Core::CBoundingBox;

            /// @brief Rendertarget within DirectX11
            ///
            class CRendertarget : public IRendertarget
            {
            private:
                /// @brief Graphic object
                ///
                IGraphics* m_pGraphics;
                /// @brief Buffer to draw on
                ///
                ID3D11RenderTargetView** m_ppBuffer;
                /// @brief Buffer to draw on
                ///
                ID3D11DepthStencilView* m_pDepthBuffer;
                /// @brief Pointer to the DephtSTencilState
                ///
                ID3D11DepthStencilState* m_pDepthStencilState;
                /// @brief Pointer to the DephtSTencilState for Lighting
                ///
                ID3D11DepthStencilState* m_pLightDepthStencilState;
                /// @brief Blend State for Alpha Channels
                ///
                ID3D11BlendState* m_pBlendState;
                /// @brief Blend State for Alpha Channels
                ///
                ID3D11BlendState* m_pBlendStateBlend;
                /// @brief Pointer to the Device
                ///
                ID3D11Device* m_pDevice;
                /// @brief Pointer to the Device
                ///
                ID3D11DeviceContext* m_pDeviceContext;
                /// @brief ITexture Element for Color
                ///
                CTexture2D** m_ppTexture;
                /// @brief Our Texture Count
                ///
                int32 m_TextureCount;
                /// @brief ITexture Element for Depth
                ///
                CTexture2D* m_pDepthTexture;
                /// @brief Our Quad Vertex Buffer
                ///
                Quad* m_pQuadBuffer;

            public:
                /// @brief Constructor
                ///
                /// @param Graphics object we save for later use
                /// @param Device object we save for later use
                /// @param DeviceContext object we save for later use
                /// @param Description of the Rendertarget
                /// @param QuadBuffer
                ///
                CRendertarget(IGraphics* a_pGraphics, ID3D11Device* a_pDevice, ID3D11DeviceContext* a_pDeviceContext, const STexture2DDescription& a_rDescription, Quad* a_pQuadBuffer);

                /// @brief Destructor
                ///
                ~CRendertarget();
            public:
                /// @brief Draw on the Rendertarget's Gemoetry Buffers
                ///
                /// @param Color for the Background
                ///
                void ApplyGeometryPass(Color a_Color);
                /// @brief Draw on the Rendertarget's Light Buffer
                ///
                /// @param Color for the Background
                ///
                void ApplyLightPass(Color a_Color);
                /// @brief Draw on the Rendertarget's SSAO Buffer
                ///
                /// @param Color for the Background
                ///
                void ApplySSAOPass(Color a_Color);

                /// @brief Copy the Content of this Target to another
                ///
                /// @param Target to copy into
                /// @param Position we copy it to
                /// @param Size we copy it to
                /// @param Position we copy from
                /// @param Size we copy from
                ///
                void Copy(IRendertarget* a_pTarget, Vector2<int32> a_TargetPosition, Vector2<int32> a_TargetSize, Vector2<int32> a_SourcePosition, Vector2<int32> a_SourceSize);

                /// @brief Gets the Texture Element
                ///
                /// @param Which index of the texture we want to be returned
                ///
                /// @returns Pointer to an ITexture2D Instance
                ///
                CTexture2D* GetTexture2D(int32 index);

                /// @brief Draw the object
                ///
                /// @param Camera for the View and Projection Matrix
                /// @param Material used to draw
                ///
                void Draw(CCamera* a_pCamera, IMaterial* a_pMaterial);

                /// @brief Draw the object
                ///
                /// @param Camera for the View and Projection Matrix
                /// @param Material used to draw
                /// @param Position of the Quad
                /// @param Size of the Quad
                ///
                void Draw(CCamera* a_pCamera, IMaterial* a_pMaterial, Vector3<float32> a_Position, Vector3<float32> a_Size);

                /// @brief Draw the object
                ///
                /// @param Camera for the View and Projection Matrix
                /// @param Material used to draw
                /// @param X+Y Position on the UV
                /// @param Width and Height on the UV
                /// @param Position of the Quad
                /// @param Size of the Quad
                ///
                void Draw(CCamera* a_pCamera, IMaterial* a_pMaterial, Vector2<float32> a_UVPosition, Vector2<float32> a_UVSize, Vector3<float32> a_Position, Vector3<float32> a_Size);
            };

        }
    }
}

#endif /* _RENDERTARGET_H_ */