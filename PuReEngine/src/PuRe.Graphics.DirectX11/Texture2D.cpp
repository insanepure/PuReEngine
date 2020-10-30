#include "include/PuReEngine/DirectX11/Texture2D.h"

namespace PuReEngine
{
    namespace Graphics
    {
        namespace DirectX11
        {

            // **************************************************************************
            // **************************************************************************
            CTexture2D::CTexture2D(ID3D11Device* a_pDevice, ID3D11DeviceContext* a_pDeviceContext)
            {
                STexture2DDescription desc;
                desc.Bpp = 32;
                desc.Height = 1;
                desc.Width = 1;
                this->m_Description = desc;
                this->m_pDevice = a_pDevice;
                this->m_pDeviceContext = a_pDeviceContext;

            }

            // **************************************************************************
            // **************************************************************************
            CTexture2D::CTexture2D(ID3D11Device* a_pDevice, ID3D11DeviceContext* a_pDeviceContext, const STexture2DDescription& a_rDescription)
            {
                this->m_Description = a_rDescription;
                this->m_pDevice = a_pDevice;
                this->m_pDeviceContext = a_pDeviceContext;

            }

            // **************************************************************************
            // **************************************************************************
            void CTexture2D::Copy(ITexture2D* a_Target, bool a_Rendertarget)
            {
                this->m_pDeviceContext->CopyResource(((CTexture2D*)a_Target)->m_pTexture, this->m_pTexture);
            }

            // **************************************************************************
            // **************************************************************************
            void CTexture2D::CreateTexture()
            {
                D3D11_TEXTURE2D_DESC descriptionWrite;
                ZeroMemory(&descriptionWrite, sizeof(descriptionWrite));
                descriptionWrite.Width = this->m_Description.Width;
                descriptionWrite.Height = this->m_Description.Height;
                descriptionWrite.MipLevels = 1;
                descriptionWrite.ArraySize = 1;
                descriptionWrite.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
                descriptionWrite.SampleDesc.Count = 1;
                descriptionWrite.Usage = D3D11_USAGE_DYNAMIC;
                descriptionWrite.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
                descriptionWrite.BindFlags = D3D11_BIND_SHADER_RESOURCE;
                this->m_pDevice->CreateTexture2D(&descriptionWrite, NULL, &this->m_pTexture);

                D3D11_SHADER_RESOURCE_VIEW_DESC descriptionShader;
                ZeroMemory(&descriptionShader, sizeof(descriptionShader));
                descriptionShader.Format = descriptionWrite.Format;
                descriptionShader.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
                descriptionShader.Texture2D.MipLevels = descriptionWrite.MipLevels;
                descriptionShader.Texture2D.MostDetailedMip = descriptionWrite.MipLevels - 1;
                this->m_pDevice->CreateShaderResourceView(this->m_pTexture, &descriptionShader, &this->m_pShaderView);

                //Use Buffer
                this->m_pDeviceContext->Map(this->m_pTexture, 0, D3D11_MAP_WRITE_DISCARD, 0, &this->m_MappedTex);
                //Fill buffer
                int32 size = this->m_Description.Height*this->m_Description.Width * 4;
                UCHAR* ptexels = (UCHAR*)this->m_MappedTex.pData;
                memset(ptexels, 30, size);
                ptexels[3] = 255;
                //Unmap
                this->m_pDeviceContext->Unmap(this->m_pTexture, 0);
            }

            // **************************************************************************
            // **************************************************************************
            void CTexture2D::CreateCubeMap(uint8** a_ppPixels)
            {
                D3D11_TEXTURE2D_DESC descriptionWrite;
                ZeroMemory(&descriptionWrite, sizeof(descriptionWrite));
                descriptionWrite.Width = this->m_Description.Width;
                descriptionWrite.Height = this->m_Description.Height;
                descriptionWrite.MipLevels = 1;
                descriptionWrite.ArraySize = 6;
                descriptionWrite.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
                descriptionWrite.SampleDesc.Count = 1;
                descriptionWrite.Usage = D3D11_USAGE_DEFAULT;
                descriptionWrite.BindFlags = D3D11_BIND_SHADER_RESOURCE;
                descriptionWrite.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;
                D3D11_SUBRESOURCE_DATA pData[6];
                for (int32 i = 0; i < 6; i++)
                {
                    pData[i].pSysMem = a_ppPixels[i];
                    pData[i].SysMemPitch = this->m_Description.Width*4;
                    pData[i].SysMemSlicePitch = this->m_Description.Width * this->m_Description.Height * 4;
                }
                HRESULT hr = this->m_pDevice->CreateTexture2D(&descriptionWrite,pData, &this->m_pTexture);
                D3D11_SHADER_RESOURCE_VIEW_DESC descriptionShader;
                ZeroMemory(&descriptionShader, sizeof(descriptionShader));
                descriptionShader.Format = descriptionWrite.Format;
                descriptionShader.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
                descriptionShader.Texture2D.MipLevels = descriptionWrite.MipLevels;
                descriptionShader.Texture2D.MostDetailedMip = descriptionWrite.MipLevels - 1;
                hr = this->m_pDevice->CreateShaderResourceView(this->m_pTexture, &descriptionShader, &this->m_pShaderView);
            }

            // **************************************************************************
            // **************************************************************************
            void CTexture2D::CreateCubeMapFromMemory(uint8** a_ppPixels, int32 a_Width, int32 a_Height)
            {
                SAFE_RELEASE(this->m_pTexture);
                SAFE_RELEASE(this->m_pShaderView);
                //Define Values
                this->m_Description.Bpp = 32;
                this->m_Description.Width = a_Width;
                this->m_Description.Height = a_Height;
                //Create Texture
                this->CreateCubeMap(a_ppPixels);
            }
            // **************************************************************************
            // **************************************************************************
            void CTexture2D::CreateRendertarget()
            {
                D3D11_TEXTURE2D_DESC descriptionWrite;
                ZeroMemory(&descriptionWrite, sizeof(descriptionWrite));
                descriptionWrite.Width = this->m_Description.Width;
                descriptionWrite.Height = this->m_Description.Height;
                descriptionWrite.MipLevels = 1;
                descriptionWrite.ArraySize = 1;
                descriptionWrite.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
                descriptionWrite.SampleDesc.Count = 1;
                descriptionWrite.Usage = D3D11_USAGE_DEFAULT;
                descriptionWrite.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
                descriptionWrite.CPUAccessFlags = 0;
                descriptionWrite.MiscFlags = 0;
                this->m_pDevice->CreateTexture2D(&descriptionWrite, NULL, &this->m_pTexture);

                D3D11_SHADER_RESOURCE_VIEW_DESC descriptionShader;
                ZeroMemory(&descriptionShader, sizeof(descriptionShader));
                descriptionShader.Format = descriptionWrite.Format;
                descriptionShader.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
                descriptionShader.Texture2D.MipLevels = descriptionWrite.MipLevels;
                descriptionShader.Texture2D.MostDetailedMip = descriptionWrite.MipLevels - 1;
                this->m_pDevice->CreateShaderResourceView(this->m_pTexture, &descriptionShader, &this->m_pShaderView);
            }
            // **************************************************************************
            // **************************************************************************
            void CTexture2D::CreateDepth()
            {
                D3D11_TEXTURE2D_DESC descriptionWrite;
                ZeroMemory(&descriptionWrite, sizeof(descriptionWrite));
                descriptionWrite.Width = this->m_Description.Width;
                descriptionWrite.Height = this->m_Description.Height;
                descriptionWrite.MipLevels = 1;
                descriptionWrite.ArraySize = 1;
                descriptionWrite.Format = DXGI_FORMAT_R24G8_TYPELESS;
                descriptionWrite.SampleDesc.Count = 1;
                descriptionWrite.Usage = D3D11_USAGE_DEFAULT;
                descriptionWrite.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
                descriptionWrite.CPUAccessFlags = 0;
                descriptionWrite.MiscFlags = 0;
                HRESULT hr = this->m_pDevice->CreateTexture2D(&descriptionWrite, NULL, &this->m_pTexture);

                D3D11_SHADER_RESOURCE_VIEW_DESC descriptionShader;
                ZeroMemory(&descriptionShader, sizeof(descriptionShader));
                descriptionShader.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
                descriptionShader.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
                descriptionShader.Texture2D.MipLevels = descriptionWrite.MipLevels;
                descriptionShader.Texture2D.MostDetailedMip = descriptionWrite.MipLevels - 1;
                hr =this->m_pDevice->CreateShaderResourceView(this->m_pTexture, &descriptionShader, &m_pShaderView);
            }

            // **************************************************************************
            // **************************************************************************
            CTexture2D::~CTexture2D()
            {
                SAFE_RELEASE(this->m_pTexture);
                SAFE_RELEASE(this->m_pShaderView);
            }

            // **************************************************************************
            // **************************************************************************
            void* CTexture2D::GetData()
            {
                return this->m_pShaderView;
            }

            // **************************************************************************
            // **************************************************************************
            STexture2DDescription CTexture2D::GetDescription()
            {
                return this->m_Description;
            }
            // **************************************************************************
            // **************************************************************************
            void CTexture2D::LoadTextureFromMemory(uint8* a_pPixels, int32 a_Width, int32 a_Height)
            {
                SAFE_RELEASE(this->m_pTexture);
                SAFE_RELEASE(this->m_pShaderView);
                //Define Values
                this->m_Description.Bpp = 32;
                this->m_Description.Width = a_Width;
                this->m_Description.Height = a_Height;
                //Create Texture
                this->CreateTexture();
                //Map Data
                this->m_pDeviceContext->Map(this->m_pTexture, 0, D3D11_MAP_WRITE_DISCARD, 0, &this->m_MappedTex);
                //Copy Data
                memcpy(this->m_MappedTex.pData, a_pPixels, this->m_Description.Width*this->m_Description.Height * 4);
                //Unmap
                this->m_pDeviceContext->Unmap(this->m_pTexture, 0);

            }
            // **************************************************************************
            // **************************************************************************
            void CTexture2D::SaveTextureToFile(const char8* a_pPath)
            {
                std::string ending = a_pPath;
                ending = ending.substr(ending.find_last_of(".") + 1);
                if (ending == "bmp")
                    D3DX11SaveTextureToFile(this->m_pDeviceContext, this->m_pTexture, D3DX11_IFF_BMP, a_pPath);
                else if (ending == "jpg")
                    D3DX11SaveTextureToFile(this->m_pDeviceContext, this->m_pTexture, D3DX11_IFF_JPG, a_pPath);
                else if (ending == "png")
                    D3DX11SaveTextureToFile(this->m_pDeviceContext, this->m_pTexture, D3DX11_IFF_PNG, a_pPath);
                else if (ending == "dds")
                    D3DX11SaveTextureToFile(this->m_pDeviceContext, this->m_pTexture, D3DX11_IFF_DDS, a_pPath);
            }
            // **************************************************************************
            // **************************************************************************
            void CTexture2D::SetPixels(uint8* a_pPixels)
            {
                //Use Buffer
                this->m_pDeviceContext->Map(this->m_pTexture, 0, D3D11_MAP_WRITE_DISCARD, 0, &this->m_MappedTex);
                //Fill buffer
                int32 size = this->m_Description.Width * 4;
                UCHAR* ptexels = (UCHAR*)this->m_MappedTex.pData;
                for (int i = 0; i < this->m_Description.Height; i++)
                {
                    memcpy(ptexels, a_pPixels, size);
                    ptexels += this->m_MappedTex.RowPitch;
                    a_pPixels += size;
                }
                //Unmap
                this->m_pDeviceContext->Unmap(this->m_pTexture, 0);
            }

        }
    }
}