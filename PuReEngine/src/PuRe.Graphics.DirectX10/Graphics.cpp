#include "include/PuReEngine/DirectX10/Graphics.h"

namespace PuReEngine
{
    namespace Graphics
    {
        namespace DirectX10
        {

            // **************************************************************************
            // **************************************************************************
            CGraphics::CGraphics(IWindow* window, IPlatform* platform, SGraphicsDescription& description)
            {
                this->m_HWND = (HWND)window->GetHandle();
                this->m_pWindow = window;
                this->m_pPlatform = platform;
                this->m_pDevice = NULL;
                this->m_pBackBufferView = NULL;
                this->m_pDepthStencilBufferView = NULL;
                this->m_pSwapChain = NULL;
                this->m_Description = description;
            }

            // **************************************************************************
            // **************************************************************************
            CGraphics::~CGraphics()
            {
                this->m_pSwapChain->SetFullscreenState(false, NULL);
                SAFE_RELEASE(this->m_pBackBufferView);
                SAFE_RELEASE(this->m_pDepthStencilBufferView);
                SAFE_RELEASE(this->m_pSwapChain);
                SAFE_RELEASE(this->m_pDevice);
            }

            // **************************************************************************
            // **************************************************************************
            void CGraphics::Initialize()
            {
                // Create the Direct3D device. First, try a pure hardware device (applications will run at best performance). 
                // If that fails try a high-performance software rasterizer (application will be slower but still OK for this sample). 
                // If that also fails try a reference rasterizer (application will be much slower but maybe still OK for this sample).
                // If creation fails totally the application will end.

                if (FAILED(D3D10CreateDevice(NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL,
                    D3D10_CREATE_DEVICE_SINGLETHREADED | D3D10_CREATE_DEVICE_BGRA_SUPPORT, D3D10_SDK_VERSION, &this->m_pDevice)))
                {
                    MessageBox(m_HWND, "Creation of hardware graphics device failed! Trying high-performant software device!",
                        "Warning", MB_OK);

                    if (FAILED(D3D10CreateDevice(NULL, D3D10_DRIVER_TYPE_WARP, NULL,
                        D3D10_CREATE_DEVICE_SINGLETHREADED | D3D10_CREATE_DEVICE_BGRA_SUPPORT, D3D10_SDK_VERSION, &this->m_pDevice)))
                    {
                        MessageBox(this->m_HWND, "Creation of high-performant software device failed! Trying reference device!", "Warning", MB_OK);

                        if (FAILED(D3D10CreateDevice(NULL, D3D10_DRIVER_TYPE_REFERENCE, NULL,
                            D3D10_CREATE_DEVICE_SINGLETHREADED | D3D10_CREATE_DEVICE_BGRA_SUPPORT, D3D10_SDK_VERSION, &this->m_pDevice)))
                        {
                            MessageBox(this->m_HWND, "Creation of reference device failed! The application will now exit!", "Warning", MB_OK);
                        }
                    }
                }

                this->ChangeResolution(Vector2<int32>(this->m_Description.ResolutionWidth, this->m_Description.ResolutionHeight));

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
                depthStencilDesc.StencilEnable = false;

                this->m_pDevice->CreateDepthStencilState(&depthStencilDesc, &this->m_pDepthStencilStateOff);

                D3D10_BLEND_DESC BlendState;
                ZeroMemory(&BlendState, sizeof(D3D10_BLEND_DESC));
                BlendState.AlphaToCoverageEnable = FALSE;
                BlendState.BlendEnable[0] = TRUE;
                BlendState.SrcBlend = D3D10_BLEND_SRC_ALPHA;
                BlendState.DestBlend = D3D10_BLEND_INV_SRC_ALPHA;
                BlendState.BlendOp = D3D10_BLEND_OP_ADD;
                BlendState.SrcBlendAlpha = D3D10_BLEND_ZERO;
                BlendState.DestBlendAlpha = D3D10_BLEND_ZERO;
                BlendState.BlendOpAlpha = D3D10_BLEND_OP_ADD;
                BlendState.RenderTargetWriteMask[0] = D3D10_COLOR_WRITE_ENABLE_ALL;

                this->m_pDevice->CreateBlendState(&BlendState, &this->m_pBlendState);

                D3D10_RASTERIZER_DESC rasterDesc;
                rasterDesc.AntialiasedLineEnable = true;
                rasterDesc.CullMode = D3D10_CULL_BACK;
                rasterDesc.DepthBias = 0;
                rasterDesc.DepthBiasClamp = 0.0f;
                rasterDesc.DepthClipEnable = false;
                rasterDesc.FillMode = D3D10_FILL_SOLID;
                rasterDesc.FrontCounterClockwise = false;
                rasterDesc.MultisampleEnable = false;
                rasterDesc.ScissorEnable = false;
                rasterDesc.SlopeScaledDepthBias = 0.0f;

                this->m_pDevice->CreateRasterizerState(&rasterDesc, &this->m_pRasterstate);

                D3D10_RASTERIZER_DESC rasterDescOff;
                rasterDescOff.AntialiasedLineEnable = true;
                rasterDescOff.CullMode = D3D10_CULL_NONE;
                rasterDescOff.DepthBias = 0;
                rasterDescOff.DepthBiasClamp = 0.0f;
                rasterDescOff.DepthClipEnable = true;
                rasterDescOff.FillMode = D3D10_FILL_SOLID;
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
                ID3D10Texture2D* pbackBuffer;
                ID3D10Texture2D* pdepthStencilBuffer;
                D3D10_TEXTURE2D_DESC depthStencilDescription;
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

                this->m_pSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*)&pbackBuffer);
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
                depthStencilDescription.Usage = D3D10_USAGE_DEFAULT;
                depthStencilDescription.BindFlags = D3D10_BIND_DEPTH_STENCIL;
                depthStencilDescription.CPUAccessFlags = 0;
                depthStencilDescription.MiscFlags = 0;

                this->m_pDevice->CreateTexture2D(&depthStencilDescription, 0, &pdepthStencilBuffer);
                this->m_pDevice->CreateDepthStencilView(pdepthStencilBuffer, 0, &this->m_pDepthStencilBufferView);
                pdepthStencilBuffer->Release();
            }

            SGraphicsDescription CGraphics::GetDescription()
            {
                return this->m_Description;
            }

            // **************************************************************************
            // **************************************************************************
            void CGraphics::Clear(Color a_Color)
            {
                this->m_pDevice->ClearRenderTargetView(this->m_pBackBufferView, a_Color);
                this->m_pDevice->ClearDepthStencilView(this->m_pDepthStencilBufferView, D3D10_CLEAR_DEPTH | D3D10_CLEAR_STENCIL, 1.0f, 0);
            }

            // **************************************************************************
            // **************************************************************************
            void CGraphics::Begin(CBoundingBox Box)
            {
                D3D10_VIEWPORT viewPort;
                viewPort.Width = (uint32)Box.m_Size.X;
                viewPort.Height = (uint32)Box.m_Size.Y;
                viewPort.MinDepth = 0.0f;
                viewPort.MaxDepth = 1.0f;
                viewPort.TopLeftX = (int32)Box.m_Position.X;
                viewPort.TopLeftY = (int32)(this->m_Description.ResolutionHeight - Box.m_Size.Y - Box.m_Position.Y);
                this->m_pDevice->RSSetViewports(1, &viewPort);
                this->m_pDevice->RSSetState(this->m_pRasterstate);
                this->m_pDevice->OMSetBlendState(this->m_pBlendState, 0, 0xffffffff);
                this->m_pDevice->OMSetDepthStencilState(this->m_pDepthStencilState, 0);
                this->m_pDevice->OMSetRenderTargets(1, &this->m_pBackBufferView, this->m_pDepthStencilBufferView);
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
                return new CMaterial(this->m_pDevice, a_pFile);
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
                return new CRendertarget(this, this->m_pDevice, desc, QuadBuffer);
            }

            // **************************************************************************
            // **************************************************************************
            ITexture2D* CGraphics::CreateCubeMap()
            {
                CTexture2D* texture = new CTexture2D(this->m_pDevice);
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
                CTexture2D* ptexture = new CTexture2D(this->m_pDevice);
                ptexture->CreateTexture();
                return ptexture;
            }

            // **************************************************************************
            // **************************************************************************
            ITexture2D* CGraphics::CreateTexture2D(const STexture2DDescription& a_rDescription)
            {
                CTexture2D* ptexture = new CTexture2D(this->m_pDevice, a_rDescription);
                ptexture->CreateTexture();
                return ptexture;
            }

            // **************************************************************************
            // **************************************************************************
            IVertexBuffer* CGraphics::CreateVertexBuffer(int32 a_Size, int32 a_Stride)
            {
                return new CVertexBuffer(this->m_pDevice, a_Size, a_Stride);
            }

            // **************************************************************************
            // **************************************************************************
            IIndexBuffer* CGraphics::CreateIndexBuffer(int32 a_Size)
            {
                return new CIndexBuffer(this->m_pDevice, a_Size);
            }

            // **************************************************************************
            // **************************************************************************
            IInstanceBuffer* CGraphics::CreateInstanceBuffer(int32 a_Size, int32 a_Stride)
            {
                return new CInstanceBuffer(this->m_pDevice, a_Size, a_Stride);
            }

            // **************************************************************************
            // **************************************************************************
            void CGraphics::Draw(PuReEngine::Core::EPrimitive a_Primitive, int32 a_Vertices)
            {
                D3D10_PRIMITIVE_TOPOLOGY primitiveTopology = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
                switch (a_Primitive)
                {
                case PuReEngine::Core::EPrimitive::Points:
                    primitiveTopology = D3D10_PRIMITIVE_TOPOLOGY_POINTLIST;
                    break;
                case PuReEngine::Core::EPrimitive::Lines:
                    primitiveTopology = D3D10_PRIMITIVE_TOPOLOGY_LINELIST;
                    break;
                case PuReEngine::Core::EPrimitive::Linestrip:
                    primitiveTopology = D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP;
                    break;
                case PuReEngine::Core::EPrimitive::Triangles:
                    primitiveTopology = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
                    break;
                case PuReEngine::Core::EPrimitive::Trianglestrip:
                    primitiveTopology = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
                    break;
                }
                this->m_pDevice->IASetPrimitiveTopology(primitiveTopology);
                this->m_pDevice->Draw(a_Vertices, 0);
            }

            // **************************************************************************
            // **************************************************************************
            void CGraphics::DrawIndexed(PuReEngine::Core::EPrimitive a_Primitive, int32 a_Indexes)
            {
                D3D10_PRIMITIVE_TOPOLOGY primitiveTopology = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
                switch (a_Primitive)
                {
                case PuReEngine::Core::EPrimitive::Points:
                    primitiveTopology = D3D10_PRIMITIVE_TOPOLOGY_POINTLIST;
                    break;
                case PuReEngine::Core::EPrimitive::Lines:
                    primitiveTopology = D3D10_PRIMITIVE_TOPOLOGY_LINELIST;
                    break;
                case PuReEngine::Core::EPrimitive::Linestrip:
                    primitiveTopology = D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP;
                    break;
                case PuReEngine::Core::EPrimitive::Triangles:
                    primitiveTopology = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
                    break;
                case PuReEngine::Core::EPrimitive::Trianglestrip:
                    primitiveTopology = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
                    break;
                }
                this->m_pDevice->IASetPrimitiveTopology(primitiveTopology);
                this->m_pDevice->DrawIndexed(a_Indexes, 0, 0);
            }

            // **************************************************************************
            // **************************************************************************
            void CGraphics::DrawInstanced(PuReEngine::Core::EPrimitive a_Primitive, int32 a_Vertices, int32 a_Instances)
            {
                D3D10_PRIMITIVE_TOPOLOGY primitiveTopology = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
                switch (a_Primitive)
                {
                case PuReEngine::Core::EPrimitive::Points:
                    primitiveTopology = D3D10_PRIMITIVE_TOPOLOGY_POINTLIST;
                    break;
                case PuReEngine::Core::EPrimitive::Lines:
                    primitiveTopology = D3D10_PRIMITIVE_TOPOLOGY_LINELIST;
                    break;
                case PuReEngine::Core::EPrimitive::Linestrip:
                    primitiveTopology = D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP;
                    break;
                case PuReEngine::Core::EPrimitive::Triangles:
                    primitiveTopology = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
                    break;
                case PuReEngine::Core::EPrimitive::Trianglestrip:
                    primitiveTopology = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
                    break;
                }
                this->m_pDevice->IASetPrimitiveTopology(primitiveTopology);
                this->m_pDevice->DrawInstanced(a_Vertices, a_Instances, 0, 0);
            }

            // **************************************************************************
            // **************************************************************************
            void CGraphics::SetVertexBuffer(IVertexBuffer* a_pBuffer)
            {
                ID3D10Buffer* pbuff = (ID3D10Buffer*)a_pBuffer->GetData();

                UINT stride = a_pBuffer->GetStride();
                UINT offset = 0;

                this->m_pDevice->IASetVertexBuffers(0, 1, &pbuff, &stride, &offset);
            }

            // **************************************************************************
            // **************************************************************************
            void CGraphics::SetIndexBuffer(IIndexBuffer* a_pBuffer)
            {
                ID3D10Buffer* pbuff = (ID3D10Buffer*)a_pBuffer->GetData();

                this->m_pDevice->IASetIndexBuffer(pbuff, DXGI_FORMAT_R32_UINT, 0);
            }

            // **************************************************************************
            // **************************************************************************
            void CGraphics::SetInstanceBuffer(IVertexBuffer* a_pVertexBuffer, IInstanceBuffer* a_pInstanceBuffer)
            {
                ID3D10Buffer* pbuff[2] = { (ID3D10Buffer*)a_pVertexBuffer->GetData(), (ID3D10Buffer*)a_pInstanceBuffer->GetData() };

                UINT strides[2] = { a_pVertexBuffer->GetStride(), a_pInstanceBuffer->GetStride() };
                UINT offsets[2] = { 0, 0 };

                this->m_pDevice->IASetVertexBuffers(0, 2, pbuff, strides, offsets);
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
                    this->m_pDevice->OMSetDepthStencilState(this->m_pDepthStencilState, 0);
                else
                    this->m_pDevice->OMSetDepthStencilState(this->m_pDepthStencilStateOff, 0);
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
                    this->m_pDevice->RSSetState(this->m_pRasterstate);
                else
                    this->m_pDevice->RSSetState(this->m_pRasterstateCullOff);
            }

        }
    }
}