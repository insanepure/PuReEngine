#ifndef _IGRAPHICS_H_
#define _IGRAPHICS_H_

// Engine specific includes
#include "Defines.h"
#include "IMaterial.h"
#include "IRendertarget.h"
#include "ITexture2D.h"
#include "IVertexBuffer.h"
#include "IIndexBuffer.h"
#include "IInstanceBuffer.h"
#include "Color.h"
#include "BoundingBox.h"
#include "Texture2DDescription.h"
#include "GraphicsDescription.h"


// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {


        /// @brief All possible Primitives we could draw our vertices as
        ///
        enum EPrimitive
        {
            Points,
            Lines,
            Linestrip,
            Triangles,
            Trianglestrip
        };

        /// @brief Base interface for graphics devices
        ///
        struct IGraphics
        {
            /// @brief Destroyes the Graphics Device
            ///
            virtual ~IGraphics() {};
            /// @brief Gets the description of the window.
            ///
            /// @returns The description of this window.
            ///
            virtual SGraphicsDescription GetDescription() = 0;
            /// @brief Initialzes the graphics device.
            ///
            virtual void Initialize() = 0;

            /// @brief Change the Resolution of the Game.
            ///
            /// @param Resolution as Vector2.
            ///
            virtual void ChangeResolution(const Vector2<int32> a_Resolution) = 0;

            /// @brief Loads a material from specified file.
            ///
            /// @param file A file name.
            ///
            /// @returns A pointer to a IMaterial.
            ///
            virtual IMaterial* LoadMaterial(const char8* a_pFile) = 0;

            /// @brief Creates a Rendertarget, size is the Graphics Resolution
            ///
            /// @param Size of a Rendertarget.
            ///
            /// @returns A pointer to a IRendertarget.
            ///
            virtual IRendertarget* CreateRendertarget(Vector2<int32> a_Size) = 0;
            /// @brief Creates an empty CubeMap
            ///
            /// @returns A pointer to a ITexture2D.
            ///

           virtual  ITexture2D* CreateCubeMap() = 0;

            /// @brief Creates an empty 2D texture.
            ///
            /// @returns A pointer to a ITexture2D.
            ///
           virtual ITexture2D* CreateTexture2D() = 0;

            /// @brief Creates a 2D texture.
            ///
            /// @param width The width in pixels.
            /// @param height The height in pixels.
            /// @param bpp The bits per pixel.
            ///
            /// @returns A pointer to a ITexture2D.
            ///
            virtual ITexture2D* CreateTexture2D(const STexture2DDescription& a_rDescription) = 0;

            /// @brief Creates a Vertex Buffer
            ///
            /// @param Size of the Buffer
            /// @param Amount of Strides
            ///
            /// @returns A pointer to a IVertexBuffer
            ///
            virtual IVertexBuffer* CreateVertexBuffer(int32 a_Size, int32 a_Stride) = 0;

            /// @brief Creates a Vertex Buffer
            ///
            /// @param Size of the Buffer
            /// @param Amount of Strides
            ///
            /// @returns A pointer to a IVertexBuffer
            ///
            virtual IInstanceBuffer* CreateInstanceBuffer(int32 a_Size, int32 a_Stride) = 0;

            /// @brief Creates a Index Buffer
            ///
            /// @param Size of the Buffer
            ///
            /// @returns A pointer to a IIndexBuffer
            ///
            virtual IIndexBuffer* CreateIndexBuffer(int32 a_Size) = 0;

            /// @brief Draw a Mesh
            ///
            /// @param Primitive to use
            /// @param Vertices of the Mesh
            ///
            virtual void Draw(EPrimitive a_Primitive, int32 a_Vertices) = 0;

            /// @brief Draw an indexed Mesh
            ///
            /// @param Primitive to use
            /// @param Vertices of the Mesh
            ///
            virtual void DrawIndexed(EPrimitive a_Primitive, int32 Indexes) = 0;

            /// @brief Draw an instanced Mesh
            ///
            /// @param Primitive to use
            /// @param Vertices of the Mesh
            /// @param Instances of the Mesh
            ///
            virtual void DrawInstanced(EPrimitive a_Primitive, int32 a_Vertices, int32 Instances) = 0;

            /// @brief Sets the specified index buffer.
            ///
            /// @param buffer The buffer to set.
            ///
            virtual void SetIndexBuffer(IIndexBuffer* a_pBuffer) = 0;

            /// @brief Sets the specified vertex buffer.
            ///
            /// @param buffer The buffer to set.
            ///
            virtual void SetVertexBuffer(IVertexBuffer* a_pBuffer) = 0;

            /// @brief Sets the specified Instance and Vertex buffer.
            ///
            /// @param Vertex Buffer to use.
            /// @param Instance Buffer to use.
            ///
            /// @remarks We draw the Vertices from the Buffer X times with the different Values from the Instance Buffer
            ///
            virtual void SetInstanceBuffer(IVertexBuffer* a_pVertexBuffer, IInstanceBuffer* a_pInstanceBuffer) = 0;

            /// @brief Sets the specified rendertarget.
            ///
            /// @param rendertarget The rendertarget to set.
            ///
            virtual void SetRenderTarget(IRendertarget* a_pRendertarget, Color a_Color) = 0;

            /// @brief Sets the specified material. Has to be on top.
            ///
            /// @param material The material to set.
            ///
            virtual void SetMaterial(IMaterial* a_pMaterial) = 0;

            /// @brief Clear the BackBuffer
            ///
            /// @param Color to clear with
            ///
            virtual void Clear(Color a_Color) = 0;

            /// @brief Indicates the beginning of the rendering process.
            ///
            /// @param Box for Viewport Settings
            ///
            virtual void Begin(CBoundingBox Box) = 0;

            /// @brief Indicates the ending of the rendering process.
            ///

            virtual void End() = 0;

            /// @brief Changes Depth
            ///
            /// @param true culling is on, false its off
            ///
            virtual void SetDepth(bool a_On) = 0;

            /// @brief Changes DepthMask
            ///
            /// @param true culling is on, false its off
            ///
            virtual void SetDepthMask(bool a_On) = 0;

            /// @brief Changes CullMode
            ///
            /// @param true culling is on, false its off
            ///
            virtual void SetCulling(bool a_On) = 0;
        };

    }
}

#endif /* _IGRAPHICS_H_ */