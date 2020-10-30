#include "include/PuReEngine/DirectX11/Material.h"

namespace PuReEngine
{
    namespace Graphics
    {
        namespace DirectX11
        {

            CMaterial::CMaterial(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const char8* file)
            {
                this->m_pDevice = device;
                this->m_pDeviceContext = deviceContext;
                //Create the Shader Data
                this->m_pPixelShaderData = new CShader(this->m_pDevice, this->m_pDeviceContext);
                this->m_pVertexShaderData = new CShader(this->m_pDevice, this->m_pDeviceContext);
                //Compile Shaders
                std::string filename = file;
                filename += ".hlsl";
                ID3DBlob* pixelShaderBuffer = this->m_pPixelShaderData->compile(filename.c_str(), "PS_MAIN", "ps_5_0");
                ID3DBlob* vertexShaderBuffer = this->m_pVertexShaderData->compile(filename.c_str(), "VS_MAIN", "vs_5_0");
                if (pixelShaderBuffer != NULL&&vertexShaderBuffer != NULL)
                {
                    //create vertex shader
                    this->m_pDevice->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &this->m_pVertexShader);
                    //create pixel shader
                    this->m_pDevice->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &this->m_pPixelShader);


                    D3D11_INPUT_ELEMENT_DESC elements[] =
                    {
                        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
                        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
                        { "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 },
                        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 },
                        { "MATRIX", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
                        { "MATRIX", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 16, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
                        { "MATRIX", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 32, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
                        { "MATRIX", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 48, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
                        { "COLOR", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 64, D3D11_INPUT_PER_INSTANCE_DATA, 1 }
                    };
                    // Create input layout
                    this->m_pDevice->CreateInputLayout(elements, 9, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &this->m_pInputLayout);

                    D3D11_SAMPLER_DESC samplerDesc;
                    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
                    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
                    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
                    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
                    samplerDesc.MipLODBias = 0.0f;
                    samplerDesc.MaxAnisotropy = 1;
                    samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
                    samplerDesc.BorderColor[0] = 0;
                    samplerDesc.BorderColor[1] = 0;
                    samplerDesc.BorderColor[2] = 0;
                    samplerDesc.BorderColor[3] = 0;
                    samplerDesc.MinLOD = 0;
                    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

                    // Create the texture sampler state.
                    this->m_pDevice->CreateSamplerState(&samplerDesc, &this->m_pSamplerState);

                    this->m_pDeviceContext->IASetInputLayout(this->m_pInputLayout);
                    //we do not need the buffers which were set before
                    //release them
                    SAFE_RELEASE(vertexShaderBuffer);
                    SAFE_RELEASE(pixelShaderBuffer);
                }

            }
            CMaterial::~CMaterial()
            {
                //free memory
                SAFE_DELETE(this->m_pPixelShaderData);
                SAFE_DELETE(this->m_pVertexShaderData);
            }

            void CMaterial::SetMatrix(Matrix<float32>& a_rMatrix, const char8* a_pName)
            {
                if (m_pPixelShader != NULL&&m_pVertexShader != NULL)
                {
                    this->m_pVertexShaderData->setVar(Matrix<float32>::Transpose(a_rMatrix), a_pName);
                    this->m_pPixelShaderData->setVar(Matrix<float32>::Transpose(a_rMatrix), a_pName);
                }
            }

            void CMaterial::SetCubeMap(ITexture2D* a_pTexture, const char8* a_pName, int32)
            {
                if (m_pPixelShader != NULL&&m_pVertexShader != NULL)
                {
                    this->m_pVertexShaderData->SetTexture2D(a_pTexture, a_pName);
                    this->m_pPixelShaderData->SetTexture2D(a_pTexture, a_pName);
                }
            }

            void CMaterial::SetTexture2D(ITexture2D* a_pTexture, const char8* a_pName, int32)
            {
                if (m_pPixelShader != NULL&&m_pVertexShader != NULL)
                {
                    this->m_pVertexShaderData->SetTexture2D(a_pTexture, a_pName);
                    this->m_pPixelShaderData->SetTexture2D(a_pTexture, a_pName);
                }
            }

            void CMaterial::SetFloat(float32 a_Value, const char8* a_pName)
            {
                if (m_pPixelShader != NULL&&m_pVertexShader != NULL)
                {
                    this->m_pVertexShaderData->setVar(&a_Value, a_pName);
                    this->m_pPixelShaderData->setVar(&a_Value, a_pName);
                }
            }

            void CMaterial::SetVector2(Vector2<float32> a_Vector, const char8* a_pName)
            {
                if (m_pPixelShader != NULL&&m_pVertexShader != NULL)
                {
                    this->m_pVertexShaderData->setVar(&a_Vector, a_pName);
                    this->m_pPixelShaderData->setVar(&a_Vector, a_pName);
                }
            }

            void CMaterial::SetVector3(Vector3<float32> a_Vector, const char8* a_pName)
            {
                if (m_pPixelShader != NULL&&m_pVertexShader != NULL)
                {
                    this->m_pVertexShaderData->setVar(&a_Vector, a_pName);
                    this->m_pPixelShaderData->setVar(&a_Vector, a_pName);
                }
            }

            void CMaterial::SetVector4(Vector4<float32> a_Vector, const char8* a_pName)
            {
                if (m_pPixelShader != NULL&&m_pVertexShader != NULL)
                {
                    this->m_pVertexShaderData->setVar(&a_Vector, a_pName);
                    this->m_pPixelShaderData->setVar(&a_Vector, a_pName);
                }
            }

            void CMaterial::SetColor(Color a_Value, const char8* a_pName)
            {
                if (m_pPixelShader != NULL&&m_pVertexShader != NULL)
                {
                    this->m_pVertexShaderData->setVar(&a_Value, a_pName);
                    this->m_pPixelShaderData->setVar(&a_Value, a_pName);
                }
            }

            void CMaterial::Apply()
            {
                if (m_pPixelShader != NULL&&m_pVertexShader != NULL)
                {
                    this->m_pDeviceContext->IASetInputLayout(this->m_pInputLayout);
                    //Use sampler State
                    this->m_pDeviceContext->PSSetSamplers(0, 1, &this->m_pSamplerState);
                    //Set Pixel Shader
                    this->m_pDeviceContext->PSSetShader(this->m_pPixelShader, 0, 0);
                    //Set Vertex Shader
                    this->m_pDeviceContext->VSSetShader(this->m_pVertexShader, 0, 0);

                    //if Pixel Shader is defined
                    if (this->m_pPixelShaderData)
                    {
                        //go through const buffers
                        for (int i = 0; i < this->m_pPixelShaderData->getNumBuffers(); i++)
                        {
                            //set const buffers
                            ID3D11Buffer* pconstBuffer = this->m_pPixelShaderData->getConstantBuffer(i);
                            this->m_pDeviceContext->PSSetConstantBuffers(i, 1, &pconstBuffer);
                        }
                        //go through textures
                        for (int i = 0; i < this->m_pPixelShaderData->getNumTextures(); i++)
                        {
                            //set texture
                            ID3D11ShaderResourceView* pshaderResource = this->m_pPixelShaderData->getTexture(i);
                            this->m_pDeviceContext->PSSetShaderResources(this->m_pPixelShaderData->getTextureBindPoint(i), 1, &pshaderResource);
                        }

                    }

                    //if Vertex Shader is defined
                    if (this->m_pVertexShaderData)
                    {
                        //go through const buffers
                        for (int i = 0; i < this->m_pVertexShaderData->getNumBuffers(); i++)
                        {
                            //set const buffers
                            ID3D11Buffer* pconstBuffer = this->m_pVertexShaderData->getConstantBuffer(i);
                            this->m_pDeviceContext->VSSetConstantBuffers(i, 1, &pconstBuffer);
                        }

                        //go through textures
                        for (int i = 0; i < this->m_pVertexShaderData->getNumTextures(); i++)
                        {
                            //set texture
                            ID3D11ShaderResourceView* pshaderResource = this->m_pVertexShaderData->getTexture(i);
                            this->m_pDeviceContext->VSSetShaderResources(this->m_pVertexShaderData->getTextureBindPoint(i), 1, &pshaderResource);
                        }

                    }
                }
            }

        }
    }
}