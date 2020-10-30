#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

// Direct3D specific includes
#include <D3D11.h>
#include <D3DX11.h>

// PuReEngine::Core specific includes
#include "PuReEngine/IWindow.h"
#include "PuReEngine/IPlatform.h"
#include "PuReEngine/IGraphics.h"
#include "PuReEngine/Color.h"
#include "PuReEngine/IRendertarget.h"
#include "PuReEngine/GraphicsDescription.h"
#include "PuReEngine/BoundingBox.h"


// PuReEngine::DirectX11 specific includes
#include "Material.h"
#include "Texture2D.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "InstanceBuffer.h"
#include "Rendertarget.h"

namespace PuReEngine
{
    namespace Graphics
    {
        namespace DirectX11
        {

            using ::PuReEngine::Core::IWindow;
            using ::PuReEngine::Core::IPlatform;
            using ::PuReEngine::Core::IGraphics;
            using ::PuReEngine::Core::Color;
            using ::PuReEngine::Core::ITexture2D;
            using ::PuReEngine::Core::IVertexBuffer;
            using ::PuReEngine::Core::IInstanceBuffer;
            using ::PuReEngine::Core::IRendertarget;
            using ::PuReEngine::Core::IIndexBuffer;
            using ::PuReEngine::Core::IMaterial;
            using ::PuReEngine::Core::SGraphicsDescription;
            using ::PuReEngine::Core::CBoundingBox;

            /// @brief Graphic Class for DirectX11
            ///
            class CGraphics : public IGraphics
            {

            private:
                /// @brief Pointer to the Window drawn on
                ///
                IWindow* m_pWindow;
                /// @brief Pointer to the Platform Interface
                ///
                IPlatform* m_pPlatform;
                /// @brief Pointer to the device
                ///
                ID3D11Device* m_pDevice;
                /// @brief Pointer to the device Context
                ///
                ID3D11DeviceContext* m_pDeviceContext;
                /// @brief Pointer to the backbuffer
                ///
                ID3D11RenderTargetView* m_pBackBufferView;
                /// @brief Pointer to the depthstencilbutter
                ///
                ID3D11DepthStencilView* m_pDepthStencilBufferView;
                /// @brief Pointer to the DephtSTencilState
                ///
                ID3D11DepthStencilState* m_pDepthStencilState;
                /// @brief Pointer to the DephtSTencilState when its off
                ///
                ID3D11DepthStencilState* m_pDepthStencilStateOff;
                /// @brief Blend State for Alpha Channels
                ///
                ID3D11BlendState* m_pBlendState;
                /// @brief swap Chain
                ///
                IDXGISwapChain* m_pSwapChain;

                /// @brief Pointer to the rasterstate
                ///
                ID3D11RasterizerState* m_pRasterstate;
                /// @brief Window Handle
                ///
                HWND m_HWND;
                /// @brief Graphics Description
                ///
                SGraphicsDescription m_Description;

                /// @brief Pointer to the rasterstate of the culling offstate
                ///
                ID3D11RasterizerState* m_pRasterstateCullOff;

            public:
                /// @brief Initializes a Graphic object
                ///
                /// @param Pointer to the Window Interface
                /// @param Pointer to the Platform Interface
                /// @param Graphics Description
                ///
                CGraphics(IWindow* a_pWindow, IPlatform* a_pPlatform, SGraphicsDescription& a_rDescription);

                /// @brief Destroyes Graphics Class
                ///
                ~CGraphics();
                /// @brief Initializes Device, Sets Buffers and the Viewport
                ///
                void Initialize();

                /// @brief Change the Resolution of the Game.
                ///
                /// @param Resolution as Vector2.
                ///
                void ChangeResolution(const Vector2<int32> a_Resolution);

                /// @brief Gets the description of the graphic device.
                ///
                /// @returns The description of this graphic.
                ///
                SGraphicsDescription GetDescription();

                /// @brief Clear the BackBuffer
                ///
                /// @param Color to clear with
                ///
                void Clear(Color a_Color);

                /// @brief Indicates the beginning of the rendering process.
                ///
                /// @param Box for Viewport Settings
                ///
                void Begin(CBoundingBox Box);

                /// @brief End Drawcalls, Draws everything on the Backbuffer
                ///
                void End();

                /// @brief Loads a material from specified file.
                ///
                /// @param file A file name.
                ///
                /// @returns A pointer to a IMaterial.
                ///
                IMaterial* LoadMaterial(const char8* a_pFile);
                /// @brief Creates a Rendertarget, size is the Graphics Resolution
                ///
                /// @param Size of a Rendertarget.
                ///
                /// @returns A pointer to a IRendertarget.
                ///
                IRendertarget* CreateRendertarget(Vector2<int32> a_Size);

                /// @brief Creates an empty CubeMap
                ///
                /// @returns A pointer to a ITexture2D.
                ///
                ITexture2D* CreateCubeMap();

                /// @brief Creates an empty 2D texture.
                ///
                /// @returns A pointer to a ITexture2D.
                ///

                ITexture2D* CreateTexture2D();

                /// @brief Creates a 2D texture.
                ///
                /// @param width The width in pixels.
                /// @param height The height in pixels.
                /// @param bpp The bits per pixel.
                ///
                /// @returns A pointer to a ITexture2D.
                ///

                ITexture2D* CreateTexture2D(const STexture2DDescription& a_rDescription);

                /// @brief Draw a Mesh
                ///
                /// @param Primitive to use
                /// @param Vertices of the Mesh
                ///
                void Draw(PuReEngine::Core::EPrimitive a_Primitive, int32 a_Vertices);

                /// @brief Draw an indexed Mesh
                ///
                /// @param Primitive to use
                /// @param Vertices of the Mesh
                ///
                void DrawIndexed(PuReEngine::Core::EPrimitive a_Primitive, int32 a_Indexes);

                /// @brief Draw an instanced Mesh
                ///
                /// @param Primitive to use
                /// @param Vertices of the Mesh
                /// @param Instances of the Mesh
                ///
                void DrawInstanced(PuReEngine::Core::EPrimitive a_Primitive, int32 a_Vertices, int32 Instances);

                /// @brief Creates a Vertex Buffer
                ///
                /// @param Size of the Buffer
                /// @param Amount of Strides
                ///
                /// @returns A pointer to a IVertexBuffer
                ///
                IVertexBuffer* CreateVertexBuffer(int32 a_Size, int32 a_Stride);

                /// @brief Creates a Vertex Buffer
                ///
                /// @param Size of the Buffer
                /// @param Amount of Strides
                ///
                /// @returns A pointer to a IVertexBuffer
                ///
                IInstanceBuffer* CreateInstanceBuffer(int32 a_Size, int32 a_Stride);

                /// @brief Creates a Index Buffer
                ///
                /// @param Size of the Buffer
                ///
                /// @returns A pointer to a IIndexBuffer
                ///
                IIndexBuffer* CreateIndexBuffer(int32 a_Size);

                /// @brief Sets the specified index buffer.
                ///
                /// @param buffer The buffer to set.
                ///
                void SetIndexBuffer(IIndexBuffer* a_pBuffer);

                /// @brief Sets the specified vertex buffer.
                ///
                /// @param buffer The buffer to set.
                ///
                void SetVertexBuffer(IVertexBuffer* a_pBuffer);

                /// @brief Sets the specified Instance and Vertex buffer.
                ///
                /// @param Vertex Buffer to use.
                /// @param Instance Buffer to use.
                ///
                /// @remarks We draw the Vertices from the Buffer X times with the different Values from the Instance Buffer
                ///
                void SetInstanceBuffer(IVertexBuffer* a_pVertexBuffer, IInstanceBuffer* a_pInstanceBuffer);

                /// @brief Sets the specified rendertarget.
                ///
                /// @param rendertarget The rendertarget to set.
                ///
                void SetRenderTarget(IRendertarget* a_pRendertarget, Color a_Color);


                /// @brief Sets the specified material.
                ///
                /// @param material The material to set.
                ///
                void SetMaterial(IMaterial* a_pMaterial);

                /// @brief Changes CullMode
                ///
                /// @param true culling is on, false its off
                ///
                void SetCulling(bool a_On);

                /// @brief Changes Depth
                ///
                /// @param true culling is on, false its off
                ///
                void SetDepth(bool a_On);

                /// @brief Changes DepthMask
                ///
                /// @param true culling is on, false its off
                ///
                void SetDepthMask(bool a_On);
            };

            /// @brief Creates a Graphic Object
            ///
            /// @param Pointer to the IWindow
            /// @param Pointer to the IPLatform
            /// @param Address of the Graphic Description
            ///
            /// @returns Pointer to the Graphic Object
            ///
            PuReEngine::Core::IGraphics* CreateGraphics(IWindow* a_pWindow, IPlatform* a_pPlatform, SGraphicsDescription& a_rDescription)
            {
                return new PuReEngine::Graphics::DirectX11::CGraphics(a_pWindow, a_pPlatform, a_rDescription);
            }

        }
    }
}

#endif /* _GRAPHICS_H_ */