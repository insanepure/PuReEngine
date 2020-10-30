#include "include/PuReEngine/OpenGL/Graphics.h"

namespace PuReEngine
{
    namespace Graphics
    {
        namespace OpenGL
        {

            // **************************************************************************
            // **************************************************************************
            CGraphics::CGraphics(IWindow* a_pWindow, IPlatform* a_pPlatform, SGraphicsDescription& a_rDescription)
            {
                this->m_pWindow = a_pWindow;
                this->m_pPlatform = a_pPlatform;
                this->m_Description = a_rDescription;
                this->m_pGraphicPlatform = CreateGraphic(a_pWindow, a_pPlatform, a_rDescription);
                glewInit();
            }

            // **************************************************************************
            // **************************************************************************
            CGraphics::~CGraphics()
            {
                SAFE_DELETE(this->m_BackBufferTexture);
                this->m_BackBufferTexture = NULL;
                SAFE_DELETE(this->m_DepthBufferTexture);
                this->m_DepthBufferTexture = NULL;
                SAFE_DELETE(this->m_pGraphicPlatform);
                this->m_pGraphicPlatform = NULL;
            }

            // **************************************************************************
            // **************************************************************************
            void CGraphics::Initialize()
            {
                glEnable(GL_BLEND);
                glEnable(GL_DEPTH_TEST);
                glDisable(GL_LIGHTING);
                glDepthFunc(GL_LESS);
                glShadeModel(GL_SMOOTH);
                glEnable(GL_CULL_FACE);
                glFrontFace(GL_CW);
                glCullFace(GL_BACK);
                glClearDepth(1.0f);
                glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
                glLoadIdentity();
                STexture2DDescription desc;
                desc.Bpp = 32;
                desc.Width = this->m_Description.ResolutionWidth;
                desc.Height = this->m_Description.ResolutionHeight;
                this->m_BackBuffer = 0;
                glGenFramebuffers(1, &this->m_BackBuffer);
                this->m_BackBufferTexture = new CTexture2D(desc);
                this->m_BackBufferTexture->CreateTexture();

                this->m_DepthBufferTexture = new CTexture2D(desc);
                this->m_DepthBufferTexture->CreateDepth();
            }

            // **************************************************************************
            // **************************************************************************
            void CGraphics::ChangeResolution(const Vector2<int32> a_Resolution)
            {
                SAFE_DELETE(this->m_BackBufferTexture);
                this->m_BackBufferTexture = NULL;
                SAFE_DELETE(this->m_DepthBufferTexture);
                this->m_DepthBufferTexture = NULL;

                this->m_Description.ResolutionWidth = a_Resolution.X;
                this->m_Description.ResolutionHeight = a_Resolution.Y;

                STexture2DDescription desc;
                desc.Bpp = 32;
                desc.Width = this->m_Description.ResolutionWidth;
                desc.Height = this->m_Description.ResolutionHeight;
                this->m_BackBuffer = 0;
                glGenFramebuffers(1, &this->m_BackBuffer);
                this->m_BackBufferTexture = new CTexture2D(desc);
                this->m_BackBufferTexture->CreateTexture();

                this->m_DepthBufferTexture = new CTexture2D(desc);
                this->m_DepthBufferTexture->CreateDepth();
            }

            // **************************************************************************
            // **************************************************************************

            SGraphicsDescription CGraphics::GetDescription()
            {
                return this->m_Description;
            }

            // **************************************************************************
            // **************************************************************************
            void CGraphics::Clear(Color Color)
            {
                glBindFramebuffer(GL_FRAMEBUFFER, this->m_BackBuffer);
                glClearColor(Color.R, Color.G, Color.B, Color.A);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                test = false;
            }

            // **************************************************************************
            // **************************************************************************
            void CGraphics::Begin(CBoundingBox Box)
            {
                glDepthMask(GL_TRUE);
                glEnable(GL_DEPTH_TEST);
                glLineWidth(5.0f);
                glEnable(GL_BLEND);
                glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
                glViewport((GLint)Box.m_Position.X, (GLint)Box.m_Position.Y, (GLsizei)Box.m_Size.X, (GLsizei)Box.m_Size.Y);
                //make the framebuffer active so we draw on it
                glBindFramebuffer(GL_FRAMEBUFFER, this->m_BackBuffer);
                //use the saved texture for the active framebuffer
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, (GLuint)this->m_BackBufferTexture->GetData(), 0);
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, (GLuint)this->m_DepthBufferTexture->GetData(), 0);
            }


            // **************************************************************************
            // **************************************************************************
            void CGraphics::End()
            {
                SWindowDescription desc = this->m_pWindow->GetDescription();
                glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
                glBlitFramebuffer(0, 0, this->m_Description.ResolutionWidth, this->m_Description.ResolutionHeight, 0, 0, desc.Width, desc.Height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
                this->m_pGraphicPlatform->SwapBuffs();
            }

            // **************************************************************************
            // **************************************************************************
            IMaterial* CGraphics::LoadMaterial(const char8* file)
            {
                return new CMaterial(file);
            }

            // **************************************************************************
            // **************************************************************************
            IRendertarget* CGraphics::CreateRendertarget(Vector2<int32> a_Size)
            {
                STexture2DDescription desc;
                desc.Bpp = 32;
                desc.Width = a_Size.X;
                desc.Height = a_Size.Y;
                Quad* QuadBuffer = new Quad(this);
                return new CRendertarget(this, desc, QuadBuffer);
            }

            // **************************************************************************
            // **************************************************************************
            ITexture2D* CGraphics::CreateCubeMap()
            {
                CTexture2D* texture = new CTexture2D();
                texture->CreateCubeMap();
                return texture;
            }

            // **************************************************************************
            // **************************************************************************
            ITexture2D* CGraphics::CreateTexture2D()
            {
                CTexture2D* texture = new CTexture2D();
                texture->CreateTexture();
                return texture;
            }

            // **************************************************************************
            // **************************************************************************
            ITexture2D* CGraphics::CreateTexture2D(const STexture2DDescription& a_rDescription)
            {
                CTexture2D* texture = new CTexture2D(a_rDescription);
                texture->CreateTexture();
                return texture;
            }

            // **************************************************************************
            // **************************************************************************
            IVertexBuffer* CGraphics::CreateVertexBuffer(int32 a_Size, int32 a_Stride)
            {
                return new CVertexBuffer(a_Size, a_Stride);
            }

            // **************************************************************************
            // **************************************************************************
            IInstanceBuffer* CGraphics::CreateInstanceBuffer(int32 a_Size, int32 a_Stride)
            {
                return new CInstanceBuffer(a_Size, a_Stride);
            }

            // **************************************************************************
            // **************************************************************************
            IIndexBuffer* CGraphics::CreateIndexBuffer(int32 a_Size)
            {
                return new CIndexBuffer(a_Size);
            }

            // **************************************************************************
            // **************************************************************************
            void CGraphics::Draw(PuReEngine::Core::EPrimitive a_Primitive, int32 a_Vertices)
            {
                switch (a_Primitive)
                {
                case PuReEngine::Core::Points:
                    glDrawArrays(GL_POINTS, 0, a_Vertices);
                    break;
                case PuReEngine::Core::Lines:
                    glDrawArrays(GL_LINES, 0, a_Vertices);
                    break;
                case PuReEngine::Core::Linestrip:
                    glDrawArrays(GL_LINE_STRIP, 0, a_Vertices);
                    break;
                case PuReEngine::Core::Triangles:
                    glDrawArrays(GL_TRIANGLES, 0, a_Vertices);
                    break;
                case PuReEngine::Core::Trianglestrip:
                    glDrawArrays(GL_TRIANGLE_STRIP, 0, a_Vertices);
                    break;
                }
                glDisableVertexAttribArray(0);
                glDisableVertexAttribArray(1);
                glDisableVertexAttribArray(2);
                glDisableVertexAttribArray(3);
                glUseProgram(NULL);
            }

            // **************************************************************************
            // **************************************************************************
            void CGraphics::DrawIndexed(PuReEngine::Core::EPrimitive a_Primitive, int32 a_Indexes)
            {
                switch (a_Primitive)
                {
                case PuReEngine::Core::Points:
                    glDrawElements(GL_POINTS, a_Indexes, GL_UNSIGNED_INT, (void*)0);
                    break;
                case PuReEngine::Core::Lines:
                    glDrawElements(GL_LINES, a_Indexes, GL_UNSIGNED_INT, (void*)0);
                    break;
                case PuReEngine::Core::Linestrip:
                    glDrawElements(GL_LINE_STRIP, a_Indexes, GL_UNSIGNED_INT, (void*)0);
                    break;
                case PuReEngine::Core::Triangles:
                    glDrawElements(GL_TRIANGLES, a_Indexes, GL_UNSIGNED_INT, (void*)0);
                    break;
                case PuReEngine::Core::Trianglestrip:
                    glDrawElements(GL_TRIANGLE_STRIP, a_Indexes, GL_UNSIGNED_INT, (void*)0);
                    break;
                }
                glDisableVertexAttribArray(0);
                glDisableVertexAttribArray(1);
                glDisableVertexAttribArray(2);
                glDisableVertexAttribArray(3);
                glUseProgram(NULL);
            }

            // **************************************************************************
            // **************************************************************************
            void CGraphics::DrawInstanced(PuReEngine::Core::EPrimitive a_Primitive, int32 a_Vertices, int32 a_Instances)
            {
                switch (a_Primitive)
                {
                case PuReEngine::Core::Points:
                    glDrawArraysInstanced(GL_POINTS, 0, a_Vertices, a_Instances);
                    break;
                case PuReEngine::Core::Lines:
                    glDrawArraysInstanced(GL_LINES, 0, a_Vertices, a_Instances);
                    break;
                case PuReEngine::Core::Linestrip:
                    glDrawArraysInstanced(GL_LINE_STRIP, 0, a_Vertices, a_Instances);
                    break;
                case PuReEngine::Core::Triangles:
                    glDrawArraysInstanced(GL_TRIANGLES, 0, a_Vertices, a_Instances);
                    break;
                case PuReEngine::Core::Trianglestrip:
                    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, a_Vertices, a_Instances);
                    break;
                }
                glDisableVertexAttribArray(0);
                glDisableVertexAttribArray(1);
                glDisableVertexAttribArray(2);
                glDisableVertexAttribArray(3);
                glDisableVertexAttribArray(4);
                glDisableVertexAttribArray(5);
                glDisableVertexAttribArray(6);
                glDisableVertexAttribArray(7);
                glDisableVertexAttribArray(8);
                glUseProgram(NULL);
            }

            // **************************************************************************
            // **************************************************************************
            void CGraphics::SetIndexBuffer(IIndexBuffer* a_pBuffer)
            {
                GLuint indexBuffer = ((GLuint)a_pBuffer->GetData());
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
            }

            // **************************************************************************
            // **************************************************************************
            void CGraphics::SetVertexBuffer(IVertexBuffer* a_pBuffer)
            {
                GLuint vertexbuffer = ((GLuint)a_pBuffer->GetData());
                glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
                glEnableVertexAttribArray(0); //layout = 0
                glVertexAttribPointer(
                    0,                  //Layout
                    3,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    a_pBuffer->GetStride(), // stride
                    (int*)0           // array buffer offset (0*4 = 0), next (3*4 = 12)
                    );
                glEnableVertexAttribArray(1);
                glVertexAttribPointer(
                    1,                  //Layout
                    2,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    a_pBuffer->GetStride(), // stride
                    (int*)12           // array buffer offset (3*4 = 12), next ((3+2)*4 = 5*4 = 20)
                    );
                glEnableVertexAttribArray(2);
                glVertexAttribPointer(
                    2,                  //Layout
                    3,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    a_pBuffer->GetStride(), // stride
                    (int*)20           // array buffer offset (3*4 = 12), next ((3+2+3)*4 = 8*4 = 32)
                    );
                glEnableVertexAttribArray(3);
                glVertexAttribPointer(
                    3,                  //Layout
                    3,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    a_pBuffer->GetStride(), // stride
                    (int*)32           // array buffer offset (3*4 = 12), next ((3+2+3+3)*4 = 11*4 = 44)
                    );
            }

            // **************************************************************************
            // **************************************************************************
            void CGraphics::SetInstanceBuffer(IVertexBuffer* a_pVertexBuffer, IInstanceBuffer* a_pInstanceBuffer)
            {
                GLuint vertexbuffer = ((GLuint)a_pVertexBuffer->GetData());
                glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
                glEnableVertexAttribArray(0); //layout = 0
                glVertexAttribPointer(
                    0,                  //Layout
                    3,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    a_pVertexBuffer->GetStride(), // stride
                    (int*)0           // array buffer offset (0*4 = 0), next (3*4 = 12)
                    );
                glEnableVertexAttribArray(1);
                glVertexAttribPointer(
                    1,                  //Layout
                    2,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    a_pVertexBuffer->GetStride(), // stride
                    (int*)12           // array buffer offset (3*4 = 12), next ((3+2)*4 = 5*4 = 20)
                    );
                glEnableVertexAttribArray(2);
                glVertexAttribPointer(
                    2,                  //Layout
                    3,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    a_pVertexBuffer->GetStride(), // stride
                    (int*)20           // array buffer offset (3*4 = 12), next ((3+2+3)*4 = 8*4 = 32)
                    );
                glEnableVertexAttribArray(3);
                glVertexAttribPointer(
                    3,                  //Layout
                    3,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    a_pVertexBuffer->GetStride(), // stride
                    (int*)32           // array buffer offset (3*4 = 12), next ((3+2+3+3)*4 = 11*4 = 44)
                    );
                //Bind the instance buffer and set the data
                GLuint instanceBuffer = ((GLuint)a_pInstanceBuffer->GetData());
                glBindBuffer(GL_ARRAY_BUFFER, instanceBuffer);
                glEnableVertexAttribArray(4);
                glVertexAttribPointer(
                    4,                  //Layout
                    4,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    a_pInstanceBuffer->GetStride(), // stride
                    (int*)0           // array buffer offset
                    );
                glEnableVertexAttribArray(5);
                glVertexAttribPointer(
                    5,                  //Layout
                    4,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    a_pInstanceBuffer->GetStride(), // stride
                    (int*)16           // array buffer offset
                    );
                glEnableVertexAttribArray(6);
                glVertexAttribPointer(
                    6,                  //Layout
                    4,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    a_pInstanceBuffer->GetStride(), // stride
                    (int*)32           // array buffer offset
                    );
                glEnableVertexAttribArray(7);
                glVertexAttribPointer(
                    7,                  //Layout
                    4,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    a_pInstanceBuffer->GetStride(), // stride
                    (int*)48           // array buffer offset
                    );
                glEnableVertexAttribArray(8);
                glVertexAttribPointer(
                    8,                  //Layout
                    4,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    a_pInstanceBuffer->GetStride(), // stride
                    (int*)64           // array buffer offset
                    );
                glVertexAttribDivisor(4, 1);
                glVertexAttribDivisor(5, 1);
                glVertexAttribDivisor(6, 1);
                glVertexAttribDivisor(7, 1);
                glVertexAttribDivisor(8, 1);
            }

            // **************************************************************************
            // **************************************************************************
            void CGraphics::SetMaterial(IMaterial* a_pMaterial)
            {
                a_pMaterial->Apply();
            }

            // **************************************************************************
            // **************************************************************************
            void CGraphics::SetRenderTarget(IRendertarget* a_pRendertarget, Color a_Color)
            {
                a_pRendertarget->ApplyGeometryPass(a_Color);
            }

            // **************************************************************************
            // **************************************************************************
            void CGraphics::SetDepth(bool a_On)
            {
                if (a_On)
                    glEnable(GL_DEPTH_TEST);
                else
                    glDisable(GL_DEPTH_TEST);
            }

            // **************************************************************************
            // **************************************************************************
            void CGraphics::SetDepthMask(bool a_On)
            {
                glDepthMask(a_On);
            }

            // **************************************************************************
            // **************************************************************************
            void CGraphics::SetCulling(bool a_On)
            {
                if (a_On)
                    glEnable(GL_CULL_FACE);
                else
                    glDisable(GL_CULL_FACE);
            }

        }
    }
}

