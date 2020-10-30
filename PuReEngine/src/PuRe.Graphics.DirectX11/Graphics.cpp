#include "include/PuReEngine/DirectX11/Graphics.h"

namespace PuReEngine
{
    namespace Graphics
    {
        namespace DirectX11
        {

            // **************************************************************************
            // **************************************************************************
            CGraphics::CGraphics(IWindow* a_pWindow, IPlatform* m_pPlatform, SGraphicsDescription& a_rDescription)
            {
                this->m_HWND = (HWND)a_pWindow->GetHandle();
                this->m_pWindow = a_pWindow;
                this->m_pPlatform = m_pPlatform;
                this->m_pDevice = NULL;
                this->m_pDeviceContext = NULL;
                this->m_pBackBufferView = NULL;
                this->m_pDepthStencilBufferView = NULL;
                this->m_pSwapChain = NULL;
                this->m_Description = a_rDescription;
            }

            // **************************************************************************
            // **************************************************************************
            CGraphics::~CGraphics()
            {
                SAFE_RELEASE(this->m_pBackBufferView);
                this->m_pBackBufferView = NULL;
                SAFE_RELEASE(this->m_pDepthStencilBufferView);
                this->m_pDepthStencilBufferView = NULL;
                this->m_pSwapChain->SetFullscreenState(false, NULL);
                SAFE_RELEASE(this->m_pSwapChain);
                this->m_pSwapChain = NULL;
                SAFE_RELEASE(this->m_pDeviceContext);
                this->m_pDeviceContext = NULL;
                SAFE_RELEASE(this->m_pDevice);
                this->m_pDevice = NULL;
            }

            // **************************************************************************
            // **************************************************************************
            void CGraphics::Initialize()
            {
                // Create the Direct3D device. First, try a pure hardware device (applications will run at best performance). 
                // If that fails try a high-performance software rasterizer (application will be slower but still OK for this sample). 
                // If that also fails try a reference rasterizer (application will be much slower but maybe still OK for this sample).
                // If creation fails totally the application will end.
                if (FAILED(D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL,
                    D3D11_CREATE_DEVICE_SINGLETHREADED | D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_DEBUG, nullptr, 0, D3D11_SDK_VERSION, &this->m_pDevice, nullptr, &this->m_pDeviceContext)))
                {
                    MessageBox(this->m_HWND, "Creation of hardware graphics device failed! Trying high-performant software device!",
                        "Warning", MB_OK);
                    if (FAILED(D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_WARP, NULL,
                        D3D11_CREATE_DEVICE_SINGLETHREADED | D3D11_CREATE_DEVICE_BGRA_SUPPORT, nullptr, 0, D3D11_SDK_VERSION, &this->m_pDevice, nullptr, &this->m_pDeviceContext)))
                    {
                        MessageBox(this->m_HWND, "Creation of high-performant software device failed! Trying reference device!", "Warning", MB_OK);

                        if (FAILED(D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_REFERENCE, NULL,
                            D3D11_CREATE_DEVICE_SINGLETHREADED | D3D11_CREATE_DEVICE_BGRA_SUPPORT, nullptr, 0, D3D11_SDK_VERSION, &this->m_pDevice, nullptr, &this->m_pDeviceContext)))
                        {
                            MessageBox(this->m_HWND, "Creation of reference device failed! The application will now exit!", "Warning", MB_OK);
                        }
                    }
                }

                this->ChangeResolution(Vector2<int32>(this->m_Description.ResolutionWidth,this->m_Description.ResolutionHeight));

                D3D11_DEPTH_STENCIL_DESC depthStencilDesc;

                depthStencilDesc.DepthEnable = true;
                depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
                depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

                depthStencilDesc.StencilEnable = true;
                depthStencilDesc.StencilReadMask = 0xFF;
                depthStencilDesc.StencilWriteMask = 0xFF;

                depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
                depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
                depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
                depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

                depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
                depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
                depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
                depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

                this->m_pDevice->CreateDepthStencilState(&depthStencilDesc, &this->m_pDepthStencilState);

                depthStencilDesc.DepthEnable = false;

                depthStencilDesc.StencilEnable = false;

                this->m_pDevice->CreateDepthStencilState(&depthStencilDesc, &this->m_pDepthStencilStateOff);

                D3D11_BLEND_DESC BlendState;
                ZeroMemory(&BlendState, sizeof(D3D11_BLEND_DESC));
                BlendState.AlphaToCoverageEnable = FALSE;
                BlendState.RenderTarget[0].BlendEnable = TRUE;
                BlendState.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
                BlendState.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
                BlendState.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
                BlendState.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
                BlendState.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
                BlendState.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
                BlendState.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

                this->m_pDevice->CreateBlendState(&BlendState, &this->m_pBlendState);

                D3D11_RASTERIZER_DESC rasterDesc;
                rasterDesc.AntialiasedLineEnable = true;
                rasterDesc.CullMode = D3D11_CULL_BACK;
                rasterDesc.DepthBias = 0;
                rasterDesc.DepthBiasClamp = 0.0f;
                rasterDesc.DepthClipEnable = false;
                rasterDesc.FillMode = D3D11_FILL_SOLID;
                rasterDesc.FrontCounterClockwise = false;
                rasterDesc.MultisampleEnable = false;
                rasterDesc.ScissorEnable = false;
                rasterDesc.SlopeScaledDepthBias = 0.0f;

                this->m_pDevice->CreateRasterizerState(&rasterDesc, &this->m_pRasterstate);

                D3D11_RASTERIZER_DESC rasterDescOff;
                rasterDescOff.AntialiasedLineEnable = true;
                rasterDescOff.CullMode = D3D11_CULL_NONE;
                rasterDescOff.DepthBias = 0;
                rasterDescOff.DepthBiasClamp = 0.0f;
                rasterDescOff.DepthClipEnable = true;
                rasterDescOff.FillMode = D3D11_FILL_SOLID;
                rasterDescOff.FrontCounterClockwise = false;
                rasterDescOff.MultisampleEnable = false;
                rasterDescOff.ScissorEnable = false;
                rasterDescOff.SlopeScaledDepthBias = 0.0f;

                this->m_pDevice->CreateRasterizerState(&rasterDescOff, &this->m_pRasterstateCullOff);
            }

            // **************************************************************************
            // **************************************************************************
            void CGraphics::ChangeResolution(const Vector2<int32> a_Resolution)
            {

                SAFE_RELEASE(this->m_pBackBufferView);
                this->m_pBackBufferView = NULL;
                SAFE_RELEASE(this->m_pDepthStencilBufferView);
                this->m_pDepthStencilBufferView = NULL;
                if (this->m_pSwapChain != NULL)
                    this->m_pSwapChain->SetFullscreenState(false, NULL);
                SAFE_RELEASE(this->m_pSwapChain);
                this->m_pSwapChain = NULL;

                IDXGIDevice* pdxgiDevice;
                IDXGIFactory* pfactory = NULL;
                IDXGIAdapter* padapter = NULL;
                ID3D11Texture2D* pbackBuffer;
                ID3D11Texture2D* pdepthStencilBuffer;
                D3D11_TEXTURE2D_DESC depthStencilDescription;
                DXGI_SWAP_CHAIN_DESC swapChainDescription;

                this->m_Description.ResolutionWidth = a_Resolution.X;
                this->m_Description.ResolutionHeight = a_Resolution.Y;

                this->m_pDevice->QueryInterface(__uuidof(IDXGIDevice), (LPVOID*)&pdxgiDevice);
                pdxgiDevice->GetAdapter(&padapter);
                padapter->GetParent(IID_PPV_ARGS(&pfactory));


                ZeroMemory(&swapChainDescription, sizeof(swapChainDescription));
                swapChainDescription.BufferDesc.Width = this->m_Description.ResolutionWidth;
                swapChainDescription.BufferDesc.Height = this->m_Description.ResolutionHeight;
                swapChainDescription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
                swapChainDescription.BufferDesc.RefreshRate.Numerator = 60;
                swapChainDescription.BufferDesc.RefreshRate.Denominator = 1;
                swapChainDescription.BufferDesc.Scaling = DXGI_MODE_SCALING_STRETCHED;
                swapChainDescription.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
                swapChainDescription.SampleDesc.Count = 1;
                swapChainDescription.SampleDesc.Quality = 0;
                swapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
                swapChainDescription.BufferCount = 1;
                swapChainDescription.OutputWindow = this->m_HWND;
                swapChainDescription.Windowed = this->m_pWindow->GetDescription().DisplaySetting != PuReEngine::Core::EDisplaySetting::Fullscreen;
                swapChainDescription.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
                swapChainDescription.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

                pfactory->CreateSwapChain(this->m_pDevice, &swapChainDescription, &this->m_pSwapChain);

                this->m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pbackBuffer);
                this->m_pDevice->CreateRenderTargetView(pbackBuffer, NULL, &this->m_pBackBufferView);
                pbackBuffer->Release();

                ZeroMemory(&depthStencilDescription, sizeof(depthStencilDescription));
                depthStencilDescription.Width = this->m_Description.ResolutionWidth;
                depthStencilDescription.Height = this->m_Description.ResolutionHeight;
                depthStencilDescription.MipLevels = 1;
                depthStencilDescription.ArraySize = 1;
                depthStencilDescription.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
                depthStencilDescription.SampleDesc.Count = 1;
                depthStencilDescription.SampleDesc.Quality = 0;
                depthStencilDescription.Usage = D3D11_USAGE_DEFAULT;
                depthStencilDescription.BindFlags = D3D11_BIND_DEPTH_STENCIL;
                depthStencilDescription.CPUAccessFlags = 0;
                depthStencilDescription.MiscFlags = 0;

                this->m_pDevice->CreateTexture2D(&depthStencilDescription, 0, &pdepthStencilBuffer);
                this->m_pDevice->CreateDepthStencilView(pdepthStencilBuffer, 0, &this->m_pDepthStencilBufferView);
                pdepthStencilBuffer->Release();
            }
            // **************************************************************************
            // **************************************************************************
            SGraphicsDescription CGraphics::GetDescription()
            {
                return this->m_Description;
            }

            // **************************************************************************
            // **************************************************************************
            void CGraphics::Clear(Color a_Color)
            {
                this->m_pDeviceContext->ClearRenderTargetView(this->m_pBackBufferView, a_Color);
                this->m_pDeviceContext->ClearDepthStencilView(this->m_pDepthStencilBufferView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
            }

            // **************************************************************************
            // **************************************************************************
            void CGraphics::Begin(CBoundingBox Box)
            {
                D3D11_VIEWPORT viewPort;
                viewPort.Width = (float32)Box.m_Size.X;
                viewPort.Height = (float32)Box.m_Size.Y;
                viewPort.MinDepth = 0.0f;
                viewPort.MaxDepth = 1.0f;
                viewPort.TopLeftX = Box.m_Position.X;
                viewPort.TopLeftY = this->m_Description.ResolutionHeight-Box.m_Size.Y-Box.m_Position.Y;
                this->m_pDeviceContext->RSSetViewports(1, &viewPort);
                this->m_pDeviceContext->RSSetState(this->m_pRasterstate);
                this->m_pDeviceContext->OMSetBlendState(this->m_pBlendState, 0, 0xffffffff);
                this->m_pDeviceContext->OMSetDepthStencilState(this->m_pDepthStencilState, 0);
                this->m_pDeviceContext->OMSetRenderTargets(1, &this->m_pBackBufferView, this->m_pDepthStencilBufferView);
            }

            // **************************************************************************
            // **************************************************************************
            void CGraphics::End()
            {
                this->m_pSwapChain->Present(0, 0);
            }

            // **************************************************************************
            // **************************************************************************
            IMaterial* CGraphics::LoadMaterial(const char8* a_pFile)
            {
                return new CMaterial(this->m_pDevice, this->m_pDeviceContext, a_pFile);
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
                return new CRendertarget(this, this->m_pDevice, this->m_pDeviceContext, desc, QuadBuffer);
            }

            // **************************************************************************
            // **************************************************************************
            ITexture2D* CGraphics::CreateCubeMap()
            {
                CTexture2D* texture = new CTexture2D(this->m_pDevice, this->m_pDeviceContext);
                uint8** ppPixels = new uint8*[6];
                int32 size = 4;
                for (int32 i = 0; i < 6; i++)
                {
                    ppPixels[i] = new uint8[size];
                    memset(ppPixels[i], 30, size);
                    ppPixels[i][3] = 255;
                }
                texture->CreateCubeMap(ppPixels);
                for (int32 i = 0; i < 6; i++)
                {
                    SAFE_DELETE(ppPixels[i]);
                }
                SAFE_DELETE(ppPixels);
                return texture;
            }

            // **************************************************************************
            // **************************************************************************
            ITexture2D* CGraphics::CreateTexture2D()
            {
                CTexture2D* ptexture = new CTexture2D(this->m_pDevice, this->m_pDeviceContext);
                ptexture->CreateTexture();
                return ptexture;
            }

            // **************************************************************************
            // **************************************************************************
            ITexture2D* CGraphics::CreateTexture2D(const STexture2DDescription& a_rDescription)
            {
                CTexture2D* ptexture = new CTexture2D(this->m_pDevice, this->m_pDeviceContext, a_rDescription);
                ptexture->CreateTexture();
                return ptexture;
            }

            // **************************************************************************
            // **************************************************************************
            IVertexBuffer* CGraphics::CreateVertexBuffer(int32 a_Size, int32 a_Stride)
            {
                return new CVertexBuffer(this->m_pDevice, this->m_pDeviceContext, a_Size, a_Stride);
            }

            // **************************************************************************
            // **************************************************************************
            IIndexBuffer* CGraphics::CreateIndexBuffer(int32 a_Size)
            {
                return new CIndexBuffer(this->m_pDevice, this->m_pDeviceContext, a_Size);
            }

            // **************************************************************************
            // **************************************************************************
            IInstanceBuffer* CGraphics::CreateInstanceBuffer(int32 a_Size, int32 a_Stride)
            {
                return new CInstanceBuffer(this->m_pDevice, this->m_pDeviceContext, a_Size, a_Stride);
            }

            // **************************************************************************
            // **************************************************************************
            void CGraphics::Draw(PuReEngine::Core::EPrimitive a_Primitive, int32 a_Vertices)
            {
                D3D11_PRIMITIVE_TOPOLOGY primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
                switch (a_Primitive)
                {
                case PuReEngine::Core::EPrimitive::Points:
                    primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
                    break;
                case PuReEngine::Core::EPrimitive::Lines:
                    primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
                    break;
                case PuReEngine::Core::EPrimitive::Linestrip:
                    primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
                    break;
                case PuReEngine::Core::EPrimitive::Triangles:
                    primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
                    break;
                case PuReEngine::Core::EPrimitive::Trianglestrip:
                    primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
                    break;
                }
                this->m_pDeviceContext->IASetPrimitiveTopology(primitiveTopology);
                this->m_pDeviceContext->Draw(a_Vertices, 0);
            }

            // **************************************************************************
            // **************************************************************************
            void CGraphics::DrawIndexed(PuReEngine::Core::EPrimitive a_Primitive, int32 a_Indexes)
            {
                D3D11_PRIMITIVE_TOPOLOGY primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
                switch (a_Primitive)
                {
                case PuReEngine::Core::EPrimitive::Points:
                    primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
                    break;
                case PuReEngine::Core::EPrimitive::Lines:
                    primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
                    break;
                case PuReEngine::Core::EPrimitive::Linestrip:
                    primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
                    break;
                case PuReEngine::Core::EPrimitive::Triangles:
                    primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
                    break;
                case PuReEngine::Core::EPrimitive::Trianglestrip:
                    primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
                    break;
                }
                this->m_pDeviceContext->IASetPrimitiveTopology(primitiveTopology);
                this->m_pDeviceContext->DrawIndexed(a_Indexes, 0, 0);
            }

            // **************************************************************************
            // **************************************************************************
            void CGraphics::DrawInstanced(PuReEngine::Core::EPrimitive a_Primitive, int32 a_Vertices, int32 a_Instances)
            {
                D3D11_PRIMITIVE_TOPOLOGY primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
                switch (a_Primitive)
                {
                case PuReEngine::Core::EPrimitive::Points:
                    primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
                    break;
                case PuReEngine::Core::EPrimitive::Lines:
                    primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
                    break;
                case PuReEngine::Core::EPrimitive::Linestrip:
                    primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
                    break;
                case PuReEngine::Core::EPrimitive::Triangles:
                    primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
                    break;
                case PuReEngine::Core::EPrimitive::Trianglestrip:
                    primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
                    break;
                }
                this->m_pDeviceContext->IASetPrimitiveTopology(primitiveTopology);
                this->m_pDeviceContext->DrawInstanced(a_Vertices, a_Instances,0,0);
            }

            // **************************************************************************
            // **************************************************************************
            void CGraphics::SetVertexBuffer(IVertexBuffer* a_pBuffer)
            {
                ID3D11Buffer* pbuff = (ID3D11Buffer*)a_pBuffer->GetData();

                UINT stride = a_pBuffer->GetStride();
                UINT offset = 0;

                this->m_pDeviceContext->IASetVertexBuffers(0, 1, &pbuff, &stride, &offset);
            }

            // **************************************************************************
            // **************************************************************************
            void CGraphics::SetIndexBuffer(IIndexBuffer* a_pBuffer)
            {
                ID3D11Buffer* pbuff = (ID3D11Buffer*)a_pBuffer->GetData();

                this->m_pDeviceContext->IASetIndexBuffer(pbuff, DXGI_FORMAT_R32_UINT, 0);
            }

            // **************************************************************************
            // **************************************************************************
            void CGraphics::SetInstanceBuffer(IVertexBuffer* a_pVertexBuffer, IInstanceBuffer* a_pInstanceBuffer)
            {
                ID3D11Buffer* pbuff[2] = { (ID3D11Buffer*)a_pVertexBuffer->GetData(), (ID3D11Buffer*)a_pInstanceBuffer->GetData() };

                UINT strides[2] = { a_pVertexBuffer->GetStride(), a_pInstanceBuffer->GetStride() };
                UINT offsets[2] = { 0, 0 };

                this->m_pDeviceContext->IASetVertexBuffers(0, 2, pbuff, strides, offsets);
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
                    this->m_pDeviceContext->OMSetDepthStencilState(this->m_pDepthStencilState, 0);
                else
                    this->m_pDeviceContext->OMSetDepthStencilState(this->m_pDepthStencilStateOff, 0);
            }

            // **************************************************************************
            // **************************************************************************
            void CGraphics::SetDepthMask(bool)
            {
            }

            // **************************************************************************
            // **************************************************************************
            void CGraphics::SetCulling(bool a_On)
            {
                if (a_On)
                    this->m_pDeviceContext->RSSetState(this->m_pRasterstate);
                else
                    this->m_pDeviceContext->RSSetState(this->m_pRasterstateCullOff);
            }

        }
    }
}