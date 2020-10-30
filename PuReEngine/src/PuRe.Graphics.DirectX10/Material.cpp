#include "include/PuReEngine/DirectX10/Material.h"

namespace PuReEngine
{
    namespace Graphics
    {
        namespace DirectX10
        {

            CMaterial::CMaterial(ID3D10Device* a_pDevice, const char8* a_pFile)
            {
                D3D10_PASS_DESC passDescription;

                D3D10_INPUT_ELEMENT_DESC elements[] =
                {
                    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
                    { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 },
                    { "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D10_INPUT_PER_VERTEX_DATA, 0 },
                    { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 32, D3D10_INPUT_PER_VERTEX_DATA, 0 },
                    { "MATRIX", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0, D3D10_INPUT_PER_INSTANCE_DATA, 1 },
                    { "MATRIX", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 16, D3D10_INPUT_PER_INSTANCE_DATA, 1 },
                    { "MATRIX", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 32, D3D10_INPUT_PER_INSTANCE_DATA, 1 },
                    { "MATRIX", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 48, D3D10_INPUT_PER_INSTANCE_DATA, 1 },
                    { "COLOR", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 64, D3D10_INPUT_PER_INSTANCE_DATA, 1 }
                };

                this->m_pDevice = a_pDevice;
                std::string filename = a_pFile;
                filename += ".fx";

                uint32 flags = 0;

#if defined(_DEBUG)
                flags = D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION;
#endif
                HRESULT hr;
                ID3D10Blob* perror;
                D3DX10CreateEffectFromFile(filename.c_str(), NULL, NULL, "fx_4_0", flags,
                    NULL, a_pDevice, NULL, NULL, &this->m_pEffect, &perror, &hr);
                if (hr == E_FAIL)
                {
                    char8* error = (char8*)perror->GetBufferPointer();
                    printf("Shader Error: %s\n", error);
                }
                else
                {

                    // Retrieve technique by name
                    this->m_pTechnique = this->m_pEffect->GetTechniqueByName("Main");

                    // Retrieve pass description
                    this->m_pTechnique->GetPassByIndex(0)->GetDesc(&passDescription);

                    // Create input layout
                    this->m_pDevice->CreateInputLayout(elements, 9, passDescription.pIAInputSignature,
                        passDescription.IAInputSignatureSize, &this->m_pInputLayout);
                }

            }
            CMaterial::~CMaterial()
            {

            }

            void CMaterial::SetMatrix(Matrix<float32>& mat, const char8* name)
            {
                if (this->m_pEffect != NULL)
                    this->m_pEffect->GetVariableByName(name)->AsMatrix()->SetMatrix(mat);
            }

            void CMaterial::SetCubeMap(ITexture2D* a_pTexture, const char8* a_pName, int32)
            {
                if (this->m_pEffect != NULL)
                {
                    if (a_pTexture != NULL)
                        this->m_pEffect->GetVariableByName(a_pName)->AsShaderResource()->SetResource((ID3D10ShaderResourceView*)a_pTexture->GetData());
                    else
                        this->m_pEffect->GetVariableByName(a_pName)->AsShaderResource()->SetResource(NULL);
                }
            }

            void CMaterial::SetTexture2D(ITexture2D* a_pTexture, const char8* a_pName, int32)
            {
                if (this->m_pEffect != NULL)
                {
                    if (a_pTexture != NULL)
                        this->m_pEffect->GetVariableByName(a_pName)->AsShaderResource()->SetResource((ID3D10ShaderResourceView*)a_pTexture->GetData());
                    else
                        this->m_pEffect->GetVariableByName(a_pName)->AsShaderResource()->SetResource(NULL);
                }
            }

            void CMaterial::SetFloat(float32 a_Value, const char8* a_pName)
            {
                if (this->m_pEffect != NULL)
                    this->m_pEffect->GetVariableByName(a_pName)->AsScalar()->SetFloat(a_Value);
            }

            void CMaterial::SetVector2(Vector2<float32> a_Vector, const char8* a_pName)
            {
                if (this->m_pEffect != NULL)
                    this->m_pEffect->GetVariableByName(a_pName)->AsVector()->SetFloatVector(a_Vector);
            }

            void CMaterial::SetVector3(Vector3<float32> a_Vector, const char8* a_pName)
            {
                if (this->m_pEffect != NULL)
                    this->m_pEffect->GetVariableByName(a_pName)->AsVector()->SetFloatVector(a_Vector);
            }

            void CMaterial::SetVector4(Vector4<float32> a_Vector, const char8* a_pName)
            {
                if (this->m_pEffect != NULL)
                    this->m_pEffect->GetVariableByName(a_pName)->AsVector()->SetFloatVector(a_Vector);
            }

            void CMaterial::SetColor(Color a_Value, const char8* a_pName)
            {
                if (this->m_pEffect != NULL)
                    this->m_pEffect->GetVariableByName(a_pName)->AsVector()->SetFloatVector(a_Value);
            }

            void CMaterial::Apply()
            {
                if (this->m_pTechnique != NULL)
                {
                    // Set coresponding input layout
                    this->m_pDevice->IASetInputLayout(this->m_pInputLayout);

                    // Apply specified pass of current technique
                    this->m_pTechnique->GetPassByIndex(0)->Apply(0);
                }

            }

        }
    }
}