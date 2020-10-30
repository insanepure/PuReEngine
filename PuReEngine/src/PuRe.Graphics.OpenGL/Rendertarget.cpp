#include "include/PuReEngine/OpenGL/Rendertarget.h"

namespace PuReEngine
{
    namespace Graphics
    {
        namespace OpenGL
        {

            // **************************************************************************
            // **************************************************************************
            CRendertarget::CRendertarget(IGraphics* a_pGraphics, const STexture2DDescription& a_rDescription, Quad* a_pQuadBuffer)
            {
                this->m_pGraphics = a_pGraphics;
                this->m_pQuadBuffer = a_pQuadBuffer;
                this->m_TextureCount = 5;
                //Create FrameBuffer for Color
                this->m_FrameBuffer = 0;
                glGenFramebuffers(1, &this->m_FrameBuffer);
                //create texture
                this->m_pTexture = new CTexture2D*[this->m_TextureCount];
                for (int32 i = 0; i < this->m_TextureCount; i++)
                {
                    this->m_pTexture[i] = new CTexture2D(a_rDescription);
                    this->m_pTexture[i]->CreateTexture();
                }
                this->m_pDepthTexture = new CTexture2D(a_rDescription);
                this->m_pDepthTexture->CreateDepth();
            }


            // **************************************************************************
            // **************************************************************************
            void CRendertarget::ApplyGeometryPass(Color a_Color)
            {
                glDepthMask(GL_TRUE);
                glEnable(GL_DEPTH_TEST);
                glLineWidth(5.0f);
                glEnable(GL_BLEND);
                glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
                STexture2DDescription desc = this->m_pTexture[0]->GetDescription();
                glViewport(0, 0, desc.Width, desc.Height);
                //make the framebuffer active so we draw on it
                glBindFramebuffer(GL_FRAMEBUFFER, this->m_FrameBuffer);
                //use the saved texture for the active framebuffer
                for (int32 i = 0; i < 3; i++)
                    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, (GLuint)this->m_pTexture[i]->GetData(), 0);
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, (GLuint)this->m_pDepthTexture->GetData(), 0);
                //PuRe_CLEAR the framebuffer with the specific color
                GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
                glDrawBuffers(3, DrawBuffers);
                glClearColor(a_Color.R, a_Color.G, a_Color.B, a_Color.A);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            }


            // **************************************************************************
            // **************************************************************************
            void CRendertarget::ApplyLightPass(Color a_Color)
            {
                glDepthMask(GL_FALSE);
                glDisable(GL_DEPTH_TEST);
                glEnable(GL_BLEND);
                glBlendEquation(GL_FUNC_ADD);
                glBlendFunc(GL_ONE, GL_ONE);

                STexture2DDescription desc = this->m_pTexture[0]->GetDescription();
                glViewport(0, 0, desc.Width, desc.Height);
                //make the framebuffer active so we draw on it
                glBindFramebuffer(GL_FRAMEBUFFER, this->m_FrameBuffer);
                //use the saved texture for the active framebuffer
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + this->m_TextureCount - 2, GL_TEXTURE_2D, (GLuint)this->m_pTexture[this->m_TextureCount - 2]->GetData(), 0);
                //PuRe_CLEAR the framebuffer with the specific color
                GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT3 };
                glDrawBuffers(1, DrawBuffers);
                glClearColor(a_Color.R, a_Color.G, a_Color.B, a_Color.A);
                glClear(GL_COLOR_BUFFER_BIT);
            }


            // **************************************************************************
            // **************************************************************************
            void CRendertarget::ApplySSAOPass(Color a_Color)
            {
                glDepthMask(GL_FALSE);
                glDisable(GL_DEPTH_TEST);
                glEnable(GL_BLEND);
                glBlendEquation(GL_FUNC_ADD);
                glBlendFunc(GL_ONE, GL_ONE);

                STexture2DDescription desc = this->m_pTexture[0]->GetDescription();
                glViewport(0, 0, desc.Width, desc.Height);
                //make the framebuffer active so we draw on it
                glBindFramebuffer(GL_FRAMEBUFFER, this->m_FrameBuffer);
                //use the saved texture for the active framebuffer
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + this->m_TextureCount - 1, GL_TEXTURE_2D, (GLuint)this->m_pTexture[this->m_TextureCount - 1]->GetData(), 0);
                //PuRe_CLEAR the framebuffer with the specific color
                GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT4 };
                glDrawBuffers(1, DrawBuffers);
                glClearColor(a_Color.R, a_Color.G, a_Color.B, a_Color.A);
                glClear(GL_COLOR_BUFFER_BIT);
            }


            // **************************************************************************
            // **************************************************************************
            void CRendertarget::Copy(IRendertarget* a_pTarget, Vector2<int32> a_TargetPosition, Vector2<int32> a_TargetSize, Vector2<int32> a_SourcePosition, Vector2<int32> a_SourceSize)
            {
                CRendertarget* target = (CRendertarget*)a_pTarget;
                //Define read and draw
                GLenum error = glGetError();
                glBindFramebuffer(GL_READ_FRAMEBUFFER, this->m_FrameBuffer);
                glBindFramebuffer(GL_DRAW_FRAMEBUFFER, target->m_FrameBuffer);
                a_TargetSize += a_TargetPosition;
                a_SourceSize += a_SourcePosition;
                //Blit Color
                for (int32 i = 0; i < 3; i++)
                {
                    glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, (GLuint)this->m_pTexture[i]->GetData(), 0);
                    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, (GLuint)target->m_pTexture[i]->GetData(), 0);
                    glReadBuffer(GL_COLOR_ATTACHMENT0 + i);
                    glDrawBuffer(GL_COLOR_ATTACHMENT0 + i);
                    glBlitFramebuffer(a_SourcePosition.X, a_SourcePosition.Y, a_SourceSize.X, a_SourceSize.Y, a_TargetPosition.X, a_TargetPosition.Y, a_TargetSize.X, a_TargetSize.Y, GL_COLOR_BUFFER_BIT, GL_NEAREST);
                }
                //Blit Depth
                glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, (GLuint)this->m_pDepthTexture->GetData(), 0);
                glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, (GLuint)target->m_pDepthTexture->GetData(), 0);
                error = glGetError();
                glReadBuffer(GL_NONE);
                error = glGetError();
                glDrawBuffer(GL_NONE);
                error = glGetError();
                glBlitFramebuffer(a_SourcePosition.X, a_SourcePosition.Y, a_SourceSize.X, a_SourceSize.Y, a_TargetPosition.X, a_TargetPosition.Y, a_TargetSize.X, a_TargetSize.Y, GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT, GL_NEAREST);
                error = glGetError();
                printf("");
           }

            // **************************************************************************
            // **************************************************************************

            void CRendertarget::Draw(CCamera* a_pCamera, IMaterial* a_pMaterial)
            {
                STexture2DDescription desc = this->m_pTexture[0]->GetDescription();
                Vector3<float32> Position = Vector3<float32>(0.0f, 0.0f, 0.0f);
                Vector3<float32> Scale = Vector3<float32>(1.0f, 1.0f, 1.0f);
                Vector2<float32> uvPosition = Vector2<float32>(0.0f, 0.0f);
                Vector2<float32> uvScale = Vector2<float32>((float32)desc.Width, (float32)desc.Height);
                this->Draw(a_pCamera,a_pMaterial, uvPosition, uvScale, Position, Scale);
            }

            // **************************************************************************
            // **************************************************************************

            void CRendertarget::Draw(CCamera* a_pCamera, IMaterial* a_pMaterial, Vector3<float32> a_Position, Vector3<float32> a_Size)
            {
                STexture2DDescription desc = this->m_pTexture[0]->GetDescription();
                Vector2<float32> uvPosition = Vector2<float32>(0.0f, 0.0f);
                Vector2<float32> uvScale = Vector2<float32>((float32)desc.Width, (float32)desc.Height);
                this->Draw(a_pCamera,a_pMaterial, uvPosition, uvScale, a_Position, a_Size);
            }

            // **************************************************************************
            // **************************************************************************

            void CRendertarget::Draw(CCamera* a_pCamera,IMaterial* a_pMaterial, Vector2<float32> a_UVPosition, Vector2<float32> a_UVSize, Vector3<float32> a_Position, Vector3<float32> a_Size)
            {
                a_pMaterial->Apply();
                a_pCamera->Apply(a_pMaterial);
                Matrix<float32> Scale = Matrix<float32>::Scale(a_Size);
                Matrix<float32> Rot = Matrix<float32>::Identity();
                Matrix<float32> Trans = Matrix<float32>::Translation(a_Position);
                a_pMaterial->SetMatrix(Scale, "Scale");
                a_pMaterial->SetMatrix(Rot, "Rotation");
                a_pMaterial->SetMatrix(Trans, "Translation");
                STexture2DDescription desc = this->m_pTexture[0]->GetDescription();
                a_UVPosition = Vector2<float32>(a_UVPosition.X / desc.Width, a_UVPosition.Y / desc.Height);
                a_UVSize = Vector2<float32>(a_UVSize.X / desc.Width, a_UVSize.Y / desc.Height);
                a_pMaterial->SetVector2(a_UVPosition, "Position");
                a_pMaterial->SetVector2(a_UVSize, "Size");
                a_pMaterial->SetVector2(Vector2<float32>((float32)desc.Width, (float32)desc.Height), "Resolution");

                for (int32 i = 0; i < this->m_TextureCount; i++)
                {
                    switch (i)
                    {
                    case 0:
                        a_pMaterial->SetTexture2D(this->m_pTexture[i], "DiffuseMap", 0);
                        break;
                    case 1:
                        a_pMaterial->SetTexture2D(this->m_pTexture[i], "NormalMap", 1);
                        break;
                    case 2:
                        a_pMaterial->SetTexture2D(this->m_pTexture[i], "GlowMap", 2);
                        break;
                    case 3:
                        a_pMaterial->SetTexture2D(this->m_pTexture[i], "LightMap", 3);
                        break;
                    case 4:
                        a_pMaterial->SetTexture2D(this->m_pTexture[i], "SSAOMap", 4);
                        break;
                    }
                }
                a_pMaterial->SetTexture2D(this->m_pDepthTexture, "DepthMap", 5);

                IVertexBuffer* buffer = this->m_pQuadBuffer->GetBuffer();
                this->m_pGraphics->SetVertexBuffer(buffer);
                a_pMaterial->Apply();
                this->m_pGraphics->Draw(PuReEngine::Core::EPrimitive::Trianglestrip, buffer->GetSize());
            }


            // **************************************************************************
            // **************************************************************************
            CRendertarget::~CRendertarget()
            {
                glDeleteFramebuffers(1,&this->m_FrameBuffer);
                SAFE_DELETE(this->m_pQuadBuffer);
                for (int32 i = 0; i < this->m_TextureCount; i++)
                    SAFE_DELETE(this->m_pTexture[i]);
                this->m_pTexture = NULL;
            }

            // **************************************************************************
            // **************************************************************************
            CTexture2D* CRendertarget::GetTexture2D(int32 index)
            {
                if (this->m_TextureCount > index)
                    return this->m_pTexture[index];
                else if (this->m_TextureCount == index)
                    return this->m_pDepthTexture;
                else
                    return nullptr;
            }

        }
    }
}
