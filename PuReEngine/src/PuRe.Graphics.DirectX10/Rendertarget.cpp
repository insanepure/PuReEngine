#include "include\PuReEngine\DirectX10\Rendertarget.h"

namespace PuReEngine
{
    namespace Graphics
    {
        namespace DirectX10
        {

            // **************************************************************************
            // **************************************************************************
            CRendertarget::CRendertarget(IGraphics* a_pGraphics, ID3D10Device* a_pDevice, const STexture2DDescription& a_rDescription, Quad* a_pQuadBuffer)
            {
                
                this->m_pGraphics = a_pGraphics;
                this->m_pQuadBuffer = a_pQuadBuffer;
                this->m_pDevice = a_pDevice;
                this->m_TextureCount = 5;

                this->m_ppTexture = new CTexture2D*[this->m_TextureCount];
                this->m_ppBuffer = new ID3D10RenderTargetView*[this->m_TextureCount];


                for (int32 i = 0; i < this->m_TextureCount; i++)
                {
                    this->m_ppTexture[i] = new CTexture2D(a_pDevice, a_rDescription);
                    this->m_ppTexture[i]->CreateRendertarget();
                }
                this->m_pDepthTexture = new CTexture2D(a_pDevice, a_rDescription);
                this->m_pDepthTexture->CreateDepth();

                D3D10_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
                // Setup the description of the render target view.
                depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
                depthStencilViewDesc.ViewDimension = D3D10_DSV_DIMENSION_TEXTURE2DMS;
                depthStencilViewDesc.Texture2D.MipSlice = 0;

                D3D10_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
                // Setup the description of the render target view.
                renderTargetViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
                renderTargetViewDesc.ViewDimension = D3D10_RTV_DIMENSION_TEXTURE2D;
                renderTargetViewDesc.Texture2D.MipSlice = 0;

                for (int32 i = 0; i < this->m_TextureCount; i++)
                {
                    //Set the Texture Resource for the Rendertarget
                    ID3D10Resource* ptextureResource;
                    //Get the Texture Resource
                    ID3D10ShaderResourceView* shaderView = (ID3D10ShaderResourceView*)this->m_ppTexture[i]->GetData();
                    shaderView->GetResource((ID3D10Resource**)&ptextureResource);
                    // Create the render target view.
                    a_pDevice->CreateRenderTargetView(ptextureResource, &renderTargetViewDesc, &this->m_ppBuffer[i]);
                    //Reset Texture
                    SAFE_RELEASE(ptextureResource);
                }

                //Set the Texture Resource for the Rendertarget
                ID3D10Resource* pDepthTextureResource;
                //Get the Texture Resource
                ID3D10ShaderResourceView* shaderDepthView = (ID3D10ShaderResourceView*)this->m_pDepthTexture->GetData();
                shaderDepthView->GetResource((ID3D10Resource**)&pDepthTextureResource);
                // Create the render target view.
                a_pDevice->CreateDepthStencilView(pDepthTextureResource, &depthStencilViewDesc, &this->m_pDepthBuffer);
                //Reset Texture
                SAFE_RELEASE(pDepthTextureResource);



                D3D10_DEPTH_STENCIL_DESC depthStencilDesc;

                depthStencilDesc.DepthEnable = true;
                depthStencilDesc.DepthWriteMask = D3D10_DEPTH_WRITE_MASK_ALL;
                depthStencilDesc.DepthFunc = D3D10_COMPARISON_LESS;

                depthStencilDesc.StencilEnable = true;
                depthStencilDesc.StencilReadMask = 0xFF;
                depthStencilDesc.StencilWriteMask = 0xFF;

                depthStencilDesc.FrontFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
                depthStencilDesc.FrontFace.StencilDepthFailOp = D3D10_STENCIL_OP_INCR;
                depthStencilDesc.FrontFace.StencilPassOp = D3D10_STENCIL_OP_KEEP;
                depthStencilDesc.FrontFace.StencilFunc = D3D10_COMPARISON_ALWAYS;

                depthStencilDesc.BackFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
                depthStencilDesc.BackFace.StencilDepthFailOp = D3D10_STENCIL_OP_DECR;
                depthStencilDesc.BackFace.StencilPassOp = D3D10_STENCIL_OP_KEEP;
                depthStencilDesc.BackFace.StencilFunc = D3D10_COMPARISON_ALWAYS;

                this->m_pDevice->CreateDepthStencilState(&depthStencilDesc, &this->m_pDepthStencilState);

                depthStencilDesc.DepthEnable = false;

                this->m_pDevice->CreateDepthStencilState(&depthStencilDesc, &this->m_pLightDepthStencilState);


                D3D10_BLEND_DESC BlendState;
                ZeroMemory(&BlendState, sizeof(D3D10_BLEND_DESC));
                BlendState.AlphaToCoverageEnable = true;
                for (int32 i = 0; i<this->m_TextureCount; i++)
                    BlendState.BlendEnable[i] = TRUE;
                BlendState.SrcBlend = D3D10_BLEND_SRC_ALPHA;
                BlendState.DestBlend = D3D10_BLEND_INV_SRC_ALPHA;
                BlendState.BlendOp = D3D10_BLEND_OP_ADD;
                BlendState.SrcBlendAlpha = D3D10_BLEND_SRC_ALPHA;
                BlendState.DestBlendAlpha = D3D10_BLEND_INV_SRC_ALPHA;
                BlendState.BlendOpAlpha = D3D10_BLEND_OP_ADD;
                for (int32 i = 0; i<this->m_TextureCount; i++)
                    BlendState.RenderTargetWriteMask[i] = D3D10_COLOR_WRITE_ENABLE_ALL;

                this->m_pDevice->CreateBlendState(&BlendState, &this->m_pBlendState);

                BlendState.AlphaToCoverageEnable = true;
                for (int32 i = 0; i<this->m_TextureCount; i++)
                    BlendState.BlendEnable[i] = TRUE;
                BlendState.SrcBlend = D3D10_BLEND_ONE;
                BlendState.DestBlend = D3D10_BLEND_ONE;
                BlendState.BlendOp = D3D10_BLEND_OP_ADD;
                BlendState.SrcBlendAlpha = D3D10_BLEND_ONE;
                BlendState.DestBlendAlpha = D3D10_BLEND_ONE;
                BlendState.BlendOpAlpha = D3D10_BLEND_OP_ADD;
                for (int32 i = 0; i<this->m_TextureCount; i++)
                    BlendState.RenderTargetWriteMask[i] = D3D10_COLOR_WRITE_ENABLE_ALL;

                this->m_pDevice->CreateBlendState(&BlendState, &this->m_pLightBlendState);

                D3D10_RASTERIZER_DESC rasterDesc;

                rasterDesc.AntialiasedLineEnable = true;
                rasterDesc.CullMode = D3D10_CULL_BACK;
                rasterDesc.DepthBias = 0;
                rasterDesc.DepthBiasClamp = 0.0f;
                rasterDesc.DepthClipEnable = true;
                rasterDesc.FillMode = D3D10_FILL_SOLID;
                rasterDesc.FrontCounterClockwise = false;
                rasterDesc.MultisampleEnable = false;
                rasterDesc.ScissorEnable = false;
                rasterDesc.SlopeScaledDepthBias = 0.0f;

                this->m_pDevice->CreateRasterizerState(&rasterDesc, &this->m_pRasterstate);
            }


            // **************************************************************************
            // **************************************************************************
            void CRendertarget::ApplyGeometryPass(Color a_Color)
            {
                D3D10_VIEWPORT viewPort;
                STexture2DDescription desc = this->m_ppTexture[0]->GetDescription();
                viewPort.Width = desc.Width;
                viewPort.Height = desc.Height;
                viewPort.MinDepth = 0;
                viewPort.MaxDepth = 1;
                viewPort.TopLeftX = 0;
                viewPort.TopLeftY = 0;
                this->m_pDevice->RSSetViewports(1, &viewPort);
                //PuRe_CLEAR the target and use it
                this->m_pDevice->OMSetBlendState(this->m_pBlendState, 0, 0xffffffff);
                this->m_pDevice->OMSetDepthStencilState(this->m_pDepthStencilState, 0);
                this->m_pDevice->OMSetRenderTargets(this->m_TextureCount-2, this->m_ppBuffer, this->m_pDepthBuffer);
                for (int32 i = 0; i < this->m_TextureCount-2; i++)
                    this->m_pDevice->ClearRenderTargetView(this->m_ppBuffer[i], a_Color);
                this->m_pDevice->ClearDepthStencilView(this->m_pDepthBuffer, D3D10_CLEAR_DEPTH | D3D10_CLEAR_STENCIL, 1.0f, 0);
            }


            // **************************************************************************
            // **************************************************************************
            void CRendertarget::ApplyLightPass(Color a_Color)
            {
                D3D10_VIEWPORT viewPort;
                STexture2DDescription desc = this->m_ppTexture[0]->GetDescription();
                viewPort.Width = desc.Width;
                viewPort.Height = desc.Height;
                viewPort.MinDepth = 0;
                viewPort.MaxDepth = 1;
                viewPort.TopLeftX = 0;
                viewPort.TopLeftY = 0;
                this->m_pDevice->RSSetViewports(1, &viewPort);
                //PuRe_CLEAR the target and use it
                this->m_pDevice->OMSetBlendState(this->m_pLightBlendState, 0, 0xffffffff);
                this->m_pDevice->OMSetDepthStencilState(this->m_pLightDepthStencilState, 0);
                this->m_pDevice->OMSetRenderTargets(1, &this->m_ppBuffer[this->m_TextureCount - 2], NULL);
                this->m_pDevice->ClearRenderTargetView(this->m_ppBuffer[this->m_TextureCount - 2], a_Color);
            }


            // **************************************************************************
            // **************************************************************************
            void CRendertarget::ApplySSAOPass(Color a_Color)
            {
                D3D10_VIEWPORT viewPort;
                STexture2DDescription desc = this->m_ppTexture[0]->GetDescription();
                viewPort.Width = desc.Width;
                viewPort.Height = desc.Height;
                viewPort.MinDepth = 0;
                viewPort.MaxDepth = 1;
                viewPort.TopLeftX = 0;
                viewPort.TopLeftY = 0;
                this->m_pDevice->RSSetViewports(1, &viewPort);
                //PuRe_CLEAR the target and use it
                this->m_pDevice->OMSetBlendState(this->m_pLightBlendState, 0, 0xffffffff);
                this->m_pDevice->OMSetDepthStencilState(this->m_pLightDepthStencilState, 0);
                this->m_pDevice->OMSetRenderTargets(1, &this->m_ppBuffer[this->m_TextureCount - 1], NULL);
                this->m_pDevice->ClearRenderTargetView(this->m_ppBuffer[this->m_TextureCount - 1], a_Color);
            }


            // **************************************************************************
            // **************************************************************************
            void CRendertarget::Copy(IRendertarget*, Vector2<int32>, Vector2<int32>, Vector2<int32>, Vector2<int32>)
            {

            }

            // **************************************************************************
            // **************************************************************************

            void CRendertarget::Draw(CCamera* a_pCamera,IMaterial* a_pMaterial)
            {
                STexture2DDescription desc = this->m_ppTexture[0]->GetDescription();
                Vector3<float32> Position = Vector3<float32>(0.0f, 0.0f, 0.0f);
                Vector3<float32> Scale = Vector3<float32>(1.0f, 1.0f, 1.0f);
                Vector2<float32> uvPosition = Vector2<float32>(0.0f, 0.0f);
                Vector2<float32> uvScale = Vector2<float32>((float32)desc.Width, (float32)desc.Height);
                this->Draw(a_pCamera,a_pMaterial, uvPosition, uvScale, Position, Scale);
            }

            // **************************************************************************
            // **************************************************************************

            void CRendertarget::Draw(CCamera* a_pCamera,IMaterial* a_pMaterial, Vector3<float32> a_Position, Vector3<float32> a_Size)
            {
                STexture2DDescription desc = this->m_ppTexture[0]->GetDescription();
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
                STexture2DDescription desc = this->m_ppTexture[0]->GetDescription();
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
                        a_pMaterial->SetTexture2D(this->m_ppTexture[i], "DiffuseMap", 0);
                        break;
                    case 1:
                        a_pMaterial->SetTexture2D(this->m_ppTexture[i], "NormalMap", 1);
                        break;
                    case 2:
                        a_pMaterial->SetTexture2D(this->m_ppTexture[i], "GlowMap", 2);
                        break;
                    case 3:
                        a_pMaterial->SetTexture2D(this->m_ppTexture[i], "LightMap", 3);
                        break;
                    case 4:
                        a_pMaterial->SetTexture2D(this->m_ppTexture[i], "SSAOMap", 4);
                        break;
                    }
                }
                a_pMaterial->SetTexture2D(this->m_pDepthTexture, "DepthMap", 5);
                this->m_pGraphics->SetVertexBuffer(this->m_pQuadBuffer->GetBuffer());
                a_pMaterial->Apply();
                this->m_pGraphics->Draw(PuReEngine::Core::EPrimitive::Trianglestrip, 4);
                for (int32 i = 0; i < this->m_TextureCount; i++)
                {
                    switch (i)
                    {
                    case 0:
                        a_pMaterial->SetTexture2D(NULL, "DiffuseMap", 0);
                        break;
                    case 1:
                        a_pMaterial->SetTexture2D(NULL, "NormalMap", 1);
                        break;
                    case 2:
                        a_pMaterial->SetTexture2D(NULL, "GlowMap", 2);
                        break;
                    case 3:
                        a_pMaterial->SetTexture2D(NULL, "LightMap", 3);
                        break;
                    case 4:
                        a_pMaterial->SetTexture2D(NULL, "SSAOMap", 4);
                        break;
                    }
                }
                a_pMaterial->SetTexture2D(NULL, "DepthMap", 5);
                a_pMaterial->Apply();
            }


            // **************************************************************************
            // **************************************************************************
            CRendertarget::~CRendertarget()
            {
                SAFE_DELETE(this->m_pQuadBuffer);
                for (int32 i = 0; i < this->m_TextureCount; i++)
                    SAFE_DELETE(this->m_ppTexture[i]);
                for (int32 i = 0; i < this->m_TextureCount; i++)
                    SAFE_RELEASE(this->m_ppBuffer[i]);
            }

            // **************************************************************************
            // **************************************************************************
            CTexture2D* CRendertarget::GetTexture2D(int32 index)
            {
                if (this->m_TextureCount > index)
                    return this->m_ppTexture[index];
                else if (this->m_TextureCount == index)
                    return this->m_pDepthTexture;
                else
                    return nullptr;
            }

        }
    }
}