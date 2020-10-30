#include "include\PuReEngine\DirectX11\ShaderO.h"

namespace PuReEngine 
{
    namespace Graphics 
    {
        namespace DirectX11 
        {

            // **************************************************************************
            // **************************************************************************
            CShader::CShader(ID3D11Device* a_pDevice, ID3D11DeviceContext* a_pDeviceContext)
                : m_pDevice(a_pDevice), m_pDeviceContext(a_pDeviceContext)
            {


            }

            // **************************************************************************
            // **************************************************************************
            ID3DBlob* CShader::compile(const char8* a_pFilePath, const char8* a_pFunctionName, const char8* a_pProfile)
            {
                //declare variables

                DWORD shaderFlags = 0;

                #if defined(_DEBUG)
                    shaderFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
                #endif

                ID3DBlob* pshaderBuffer = 0;
                ID3DBlob* perrorMSG = 0;
                //compile shader
                HRESULT hr = D3DX11CompileFromFile(a_pFilePath, 0, 0, a_pFunctionName, a_pProfile, shaderFlags,
                    0, 0, &pshaderBuffer, &perrorMSG, 0);
                if (hr != S_OK)
                {
                    LPVOID pError = perrorMSG->GetBufferPointer();
                    std::string error = (char8*)pError;
                    printf("Shader Error: %s\n", error.c_str());
                }
                else
                {
                    //do a reflection of the vertex shader to get the constant buffers
                    D3DReflect(pshaderBuffer->GetBufferPointer(), pshaderBuffer->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&this->m_pVertexReflection);


                    //get the Shader description
                    D3D11_SHADER_DESC psDescr;
                    this->m_pVertexReflection->GetDesc(&psDescr);
                    //allocate memory for the buffers
                    this->m_pConstBuffers = new SConstantBufferData[psDescr.ConstantBuffers];
                    //define memory for all const buffers
                    for (uint32 i = 0; i < psDescr.ConstantBuffers; i++)
                    {
                        //get Informations from the shader
                        ID3D11ShaderReflectionConstantBuffer* pConstBuffer = this->m_pVertexReflection->GetConstantBufferByIndex(i);
                        D3D11_SHADER_BUFFER_DESC buffDescr;
                        pConstBuffer->GetDesc(&buffDescr);
                        //set constant buffer data
                        this->m_pConstBuffers[i].idx = i;
                        this->m_pConstBuffers[i].size = buffDescr.Size; // size dependend on the size within the shader
                        this->m_pConstBuffers[i].data = malloc(buffDescr.Size);
                        this->m_pConstBuffers[i].changed = true;

                        //define memory for all variables
                        for (uint32 j = 0; j < buffDescr.Variables; j++)
                        {
                            //get informations for the variables
                            ID3D11ShaderReflectionVariable* pvar = pConstBuffer->GetVariableByIndex(j);
                            D3D11_SHADER_VARIABLE_DESC varDescr;
                            pvar->GetDesc(&varDescr);
                            //copy memory
                            if (varDescr.DefaultValue)
                                memcpy((char*)this->m_pConstBuffers[i].data + varDescr.StartOffset, varDescr.DefaultValue, varDescr.Size);
                        }

                        //Buffer settings
                        D3D11_BUFFER_DESC cbDesc;
                        cbDesc.ByteWidth = this->m_pConstBuffers[i].size;
                        cbDesc.Usage = D3D11_USAGE_DYNAMIC;
                        cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
                        cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
                        cbDesc.MiscFlags = 0;
                        cbDesc.StructureByteStride = 0;

                        //initial settings
                        D3D11_SUBRESOURCE_DATA initData;
                        initData.pSysMem = &this->m_pConstBuffers[i].data;
                        initData.SysMemPitch = 0;
                        initData.SysMemSlicePitch = 0;
                        //create buffer
                        this->m_pDevice->CreateBuffer(&cbDesc, &initData, &this->m_pConstBuffers[i].constantBuffer);

                    }

                    D3D11_SHADER_INPUT_BIND_DESC desc;

                    for (uint32 i = 0; i < psDescr.BoundResources; i++)
                    {
                        //Get Ressource Informations
                        this->m_pVertexReflection->GetResourceBindingDesc(i, &desc);

                        if (desc.Type == D3D_SIT_TEXTURE)
                        {
                            //if it is a texture, save it as texture
                            STextureBind texture;
                            texture.name = desc.Name;
                            texture.bindPoint = desc.BindPoint;
                            texture.pResource = 0;
                            //push it into the list
                            this->m_Textures.push_back(texture);
                        }
                    }
                }

                return pshaderBuffer;
            }

            // **************************************************************************
            // **************************************************************************
            CShader::~CShader()
            {
                SAFE_DELETE_ARRAY(this->m_pConstBuffers);
            }

            // **************************************************************************
            // **************************************************************************
            void CShader::SetTexture2D(ITexture2D* a_pTexture, const char8* a_pName)
            {
                //Go through all textures
                for (uint32 i = 0; i < this->m_Textures.size(); i++)
                {
                    //if name fits to a texture
                    if (strcmp(this->m_Textures[i].name, a_pName) == 0)
                    {
                        //set texture data to given texture data
                        if (a_pTexture != NULL)
                            this->m_Textures[i].pResource = (ID3D11ShaderResourceView*)a_pTexture->GetData();
                        else
                            this->m_Textures[i].pResource = NULL;
                        break;
                    }
                }
            }

            // **************************************************************************
            // **************************************************************************
            void CShader::setVar(void* a_pData, const char8* a_pName)
            {
                //get Shader Informations
                D3D11_SHADER_DESC shaderDescr;
                this->m_pVertexReflection->GetDesc(&shaderDescr);
                //Get variable Reflection
                ID3D11ShaderReflectionVariable* var = this->m_pVertexReflection->GetVariableByName(a_pName);
                //Get Variable Informations
                D3D11_SHADER_VARIABLE_DESC varDescr;
                if (!FAILED(var->GetDesc(&varDescr)))
                {
                    for (uint32 i = 0; i < shaderDescr.ConstantBuffers; i++)
                    {
                        //search through shaders and see if the variable is inside a  const buffer
                        if (this->m_pVertexReflection->GetConstantBufferByIndex(i) == var->GetBuffer())
                        {
                            //Variable inside buffer found, copy memory
                            memcpy((char*)this->m_pConstBuffers[i].data + varDescr.StartOffset, a_pData, varDescr.Size);
                            //set const buffer to changed
                            this->m_pConstBuffers[i].changed = true;

                            break;
                        }

                    }
                }
            }

            // **************************************************************************
            // **************************************************************************
            ID3D11Buffer* CShader::getConstantBuffer(int idx)
            {
                //if the const buffer has changed
                if (this->m_pConstBuffers[idx].changed)
                {
                    //remap the buffer
                    D3D11_MAPPED_SUBRESOURCE mappedResource;
                    //lock it
                    this->m_pDeviceContext->Map(this->m_pConstBuffers[idx].constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
                    //copy memory
                    memcpy(mappedResource.pData, this->m_pConstBuffers[idx].data, this->m_pConstBuffers[idx].size);
                    //unlock it
                    this->m_pDeviceContext->Unmap(this->m_pConstBuffers[idx].constantBuffer, 0);
                    //set changed to false
                    this->m_pConstBuffers[idx].changed = false;
                }
                //return buffer
                return this->m_pConstBuffers[idx].constantBuffer;

            }

            // **************************************************************************
            // **************************************************************************
            int CShader::getNumBuffers()
            {
                //get amount
                D3D11_SHADER_DESC psDescr;
                this->m_pVertexReflection->GetDesc(&psDescr);
                //return the amount
                return psDescr.ConstantBuffers;
            }

            // **************************************************************************
            // **************************************************************************
            ID3D11ShaderResourceView* CShader::getTexture(int idx)
            {
                return this->m_Textures[idx].pResource;
            }

            // **************************************************************************
            // **************************************************************************
            int CShader::getTextureBindPoint(int idx)
            {
                return this->m_Textures[idx].bindPoint;
            }

            // **************************************************************************
            // **************************************************************************
            int CShader::getNumTextures()
            {
                return this->m_Textures.size();
            }

        }
    }
}