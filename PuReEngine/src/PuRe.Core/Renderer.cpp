#include "include/PuReEngine/Renderer.h"


// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {
        // **************************************************************************
        // **************************************************************************
        template<typename Calls, typename... Arguments>
        std::list<SCall>::iterator CRenderer::AddFunction(int32 a_RenderIndex, std::list<SCall>* a_pFunctions, std::list<SCall>::iterator a_Position, Calls&& a_rrFunction, Arguments&&... a_rrArgument)
        {
            SCall call;
            call.calledFunction = std::bind(std::forward<Calls>(a_rrFunction), std::forward<Arguments>(a_rrArgument)...);
            call.RenderIndex = a_RenderIndex;
            return a_pFunctions->insert(a_Position, call);
        }

        // **************************************************************************
        // **************************************************************************
        CRenderer::CRenderer(IGraphics* a_pGraphics)
        {
            this->m_pGraphics = a_pGraphics;

            this->m_pQuad = new Quad(a_pGraphics);
            this->m_pFinalRendertarget = NULL;
        }

        // **************************************************************************
        // **************************************************************************
        CRenderer::~CRenderer()
        {
            this->DeleteTargets();
            SAFE_DELETE(this->m_pQuad);
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::DeleteTargets()
        {
            for (uint32 i = 0; i < this->m_Targets.size(); i++)
            {
                SAFE_DELETE(this->m_Targets[i]->m_pRenderTarget);
                SAFE_DELETE(this->m_Targets[i]->m_pPostCamera);
                SAFE_DELETE(this->m_Targets[i]);
            }
            this->m_Targets.clear();
            SAFE_DELETE(this->m_pFinalRendertarget);
            this->m_pFinalRendertarget = NULL;

        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::AddTarget(Vector2<int32> a_Size)
        {
            if (this->m_pFinalRendertarget == NULL)
                this->m_pFinalRendertarget = this->m_pGraphics->CreateRendertarget(a_Size);

            Target* target = new Target();
            target->m_pRenderTarget = this->m_pGraphics->CreateRendertarget(a_Size);
            target->m_pPostCamera = new CCamera(Vector2<float32>((float32)a_Size.X, (float32)a_Size.Y), CameraProjection::Orthogonal);
            target->m_TexturePosition = 0;
            target->m_pSSAOMaterial = NULL;
            target->m_pNoiseTexture = NULL;
            this->m_Targets.push_back(target);
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::Begin(Color a_Color)
        {
            this->m_pGraphics->Clear(a_Color);
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::End()
        {
            this->m_pGraphics->End();

            for (uint32 i = 0; i < this->m_Targets.size(); i++)
            {
                this->m_Targets[i]->m_SetCalls.clear();
                this->m_Targets[i]->m_SkyBoxCalls.clear();
                this->m_Targets[i]->m_GeometryCalls.clear();
                this->m_Targets[i]->m_LightCalls.clear();
                this->m_Targets[i]->m_AlphaCalls.clear();
            }
        }


        // **************************************************************************
        // **************************************************************************
        void CRenderer::Draw(uint32 a_Index, bool, CSkyBox* a_pSkyBox, IMaterial* a_pMaterial, Vector3<float32> a_Rotation, int32 a_RenderIndex)
        {
            if (this->m_Targets.size() > a_Index)
            {
                auto target = this->m_Targets[a_Index];
                //Set active call
                target->m_pActiveCall = &target->m_SkyBoxCalls;
                //draw Call
                SCall c;
                target->m_CallPosition = this->AddFunction(a_RenderIndex,target->m_pActiveCall, target->m_pActiveCall->end(), &CRenderer::RenderSkybox, this, a_pSkyBox, a_pMaterial, a_Rotation);
                //add setcalls before draw call
                std::list<SCall>::iterator it;
                for (it = target->m_SetCalls.begin(); it != target->m_SetCalls.end(); ++it)
                    target->m_CallPosition = target->m_pActiveCall->insert(target->m_CallPosition, (*it));
                //add apply before setcalls
                if (target->m_SetCalls.size() != 0)
                    target->m_CallPosition = this->AddFunction(a_RenderIndex,target->m_pActiveCall, target->m_CallPosition, &CRenderer::ApplyMaterial, this, a_pMaterial);
                //Clear values
                target->m_TexturePosition = 0;
                //clear setcalls
                target->m_SetCalls.clear();
            }
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::Draw(uint32 a_Index, bool, CModel* a_pModel, EPrimitive a_Primitive, IMaterial* a_pMaterial, SRenderInstance* a_pInstances, int32 a_Instances, int32 a_RenderIndex)
        {
            if (a_pInstances != NULL&&a_Instances > 0)
            {
                if (this->m_Targets.size() > a_Index)
                {
                    auto target = this->m_Targets[a_Index];
                    //Set active call
                    if (a_pInstances[0].Color.A == 1.0f)
                        target->m_pActiveCall = &target->m_GeometryCalls;
                    else
                        target->m_pActiveCall = &target->m_AlphaCalls;
                    //draw Call
                    target->m_CallPosition = this->AddFunction(a_RenderIndex,target->m_pActiveCall, target->m_pActiveCall->end(), &CRenderer::RenderInstancedModels, this, a_pModel, a_pMaterial, a_Primitive, a_pInstances, a_Instances);
                    //add setcalls before draw call
                    std::list<SCall>::iterator it;
                    for (it = target->m_SetCalls.begin(); it != target->m_SetCalls.end(); ++it)
                        target->m_CallPosition = target->m_pActiveCall->insert(target->m_CallPosition, (*it));
                    //add apply before setcalls
                    if (target->m_SetCalls.size() != 0)
                        target->m_CallPosition = this->AddFunction(a_RenderIndex,target->m_pActiveCall, target->m_CallPosition, &CRenderer::ApplyMaterial, this, a_pMaterial);
                    //Clear values
                    target->m_TexturePosition = 0;
                    //clear setcalls
                    target->m_SetCalls.clear();
                }
            }
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::Draw(uint32 a_Index, bool, IVertexBuffer* a_pBuffer, int32 a_VertexCount, EPrimitive a_Primitive, IMaterial* a_pMaterial, SRenderInstance* a_pInstances, int32 a_Instances, int32 a_RenderIndex)
        {
            if (a_pInstances != NULL&&a_Instances > 0)
            {
                if (this->m_Targets.size() > a_Index)
                {
                    auto target = this->m_Targets[a_Index];
                    //Set active call
                    if (a_pInstances[0].Color.A == 1.0f)
                        target->m_pActiveCall = &target->m_GeometryCalls;
                    else
                        target->m_pActiveCall = &target->m_AlphaCalls;
                    //draw Call
                    target->m_CallPosition = this->AddFunction(a_RenderIndex,target->m_pActiveCall, target->m_pActiveCall->end(), &CRenderer::RenderInstancedVBuffer, this, a_pBuffer, a_VertexCount, a_pMaterial, a_Primitive, a_pInstances, a_Instances);
                    //add setcalls before draw call
                    std::list<SCall>::iterator it;
                    for (it = target->m_SetCalls.begin(); it != target->m_SetCalls.end(); ++it)
                        target->m_CallPosition = target->m_pActiveCall->insert(target->m_CallPosition, (*it));
                    //add apply before setcalls
                    if (target->m_SetCalls.size() != 0)
                        target->m_CallPosition = this->AddFunction(a_RenderIndex,target->m_pActiveCall, target->m_CallPosition, &CRenderer::ApplyMaterial, this, a_pMaterial);
                    //Clear values
                    target->m_TexturePosition = 0;
                    //clear setcalls
                    target->m_SetCalls.clear();
                }
            }
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::Draw(uint32 a_Index, bool, IVertexBuffer* a_pBuffer, int32 a_VertexCount, EPrimitive a_Primitive, IMaterial* a_pMaterial, Vector3<float32> a_Position, Matrix<float32> a_Rotation, Vector3<float32> a_Center, Vector3<float32> a_Size, Color a_Color, int32 a_RenderIndex)
        {
            if (this->m_Targets.size() > a_Index)
            {
                auto target = this->m_Targets[a_Index];
                //Set active call
                if (a_Color.A == 1.0f)
                    target->m_pActiveCall = &target->m_GeometryCalls;
                else
                    target->m_pActiveCall = &target->m_AlphaCalls;
                //draw Call
                target->m_CallPosition = this->AddFunction(a_RenderIndex,target->m_pActiveCall, target->m_pActiveCall->end(), &CRenderer::RenderVertexBuffer, this, a_pBuffer, a_VertexCount, a_pMaterial, a_Primitive, a_Position, a_Rotation, a_Center, a_Size, a_Color);
                //add setcalls before draw call
                std::list<SCall>::iterator it;
                for (it = target->m_SetCalls.begin(); it != target->m_SetCalls.end(); ++it)
                    target->m_CallPosition = target->m_pActiveCall->insert(target->m_CallPosition, (*it));
                //add apply before setcalls
                if (target->m_SetCalls.size() != 0)
                    target->m_CallPosition = this->AddFunction(a_RenderIndex,target->m_pActiveCall, target->m_CallPosition, &CRenderer::ApplyMaterial, this, a_pMaterial);
                //Clear values
                target->m_TexturePosition = 0;
                //clear setcalls
                target->m_SetCalls.clear();
            }
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::Draw(uint32 a_Index, bool a_Cull, CFont* a_pFont, IMaterial* a_pMaterial, std::string a_pText, Vector3<float32> a_Position, Matrix<float32> a_Rotation, Vector3<float32> a_Size, float32 a_Offset, Color a_Color, int32 a_RenderIndex)
        {
            if (this->m_Targets.size() > a_Index)
            {
                auto target = this->m_Targets[a_Index];
                //Set active call
                target->m_pActiveCall = &target->m_GeometryCalls;
                //draw Call
                target->m_CallPosition = this->AddFunction(a_RenderIndex,target->m_pActiveCall, target->m_pActiveCall->end(), &CRenderer::RenderFont, this, a_pFont, a_pMaterial, a_pText, a_Position, a_Rotation, a_Size, a_Offset, a_Cull,a_Color);
                //add setcalls before draw call
                std::list<SCall>::iterator it;
                for (it = target->m_SetCalls.begin(); it != target->m_SetCalls.end(); ++it)
                    target->m_CallPosition = target->m_pActiveCall->insert(target->m_CallPosition, (*it));
                //add apply before setcalls
                if (target->m_SetCalls.size() != 0)
                    target->m_CallPosition = this->AddFunction(a_RenderIndex,target->m_pActiveCall, target->m_CallPosition, &CRenderer::ApplyMaterial, this, a_pMaterial);
                //Clear values
                target->m_TexturePosition = 1;
                //clear setcalls
                target->m_SetCalls.clear();
            }
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::Draw(uint32 a_Index, bool a_Cull, CSprite* a_pSprite, IMaterial* a_pMaterial, Vector3<float32> a_Position, Matrix<float32> a_Rotation, Vector3<float32> a_Center, Vector3<float32> a_Size, Color a_Color, Vector2<float32> a_UVSize, Vector2<float32> a_UVPosition, int32 a_RenderIndex)
        {
            if (this->m_Targets.size() > a_Index)
            {
                auto target = this->m_Targets[a_Index];
                //Set active call
                if (a_Color.A == 1.0f)
                    target->m_pActiveCall = &target->m_GeometryCalls;
                else
                    target->m_pActiveCall = &target->m_AlphaCalls;
                //draw Call
                target->m_CallPosition = this->AddFunction(a_RenderIndex,target->m_pActiveCall, target->m_pActiveCall->end(), &CRenderer::RenderSprite, this, a_pSprite, a_pMaterial, a_Position, a_Rotation, a_Center, a_Size, a_Color, a_Cull, a_UVSize, a_UVPosition);
                //add setcalls before draw call
                std::list<SCall>::iterator it;
                for (it = target->m_SetCalls.begin(); it != target->m_SetCalls.end(); ++it)
                    target->m_CallPosition = target->m_pActiveCall->insert(target->m_CallPosition, (*it));
                //add apply before setcalls
                if (target->m_SetCalls.size() != 0)
                    target->m_CallPosition = this->AddFunction(a_RenderIndex,target->m_pActiveCall, target->m_CallPosition, &CRenderer::ApplyMaterial, this, a_pMaterial);
                //Clear values
                target->m_TexturePosition = 1;
                //clear setcalls
                target->m_SetCalls.clear();
            }
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::Draw(uint32 a_Index, bool a_Cull, CModel* a_pModel, EPrimitive a_Primitive, IMaterial* a_pMaterial, Vector3<float32> a_Position, Matrix<float32> a_Rotation, Vector3<float32> a_Center, Vector3<float32> a_Size, Color a_Color, int32 a_RenderIndex)
        {
            if (this->m_Targets.size() > a_Index)
            {
                auto target = this->m_Targets[a_Index];
                //Set active call
                if (a_Color.A == 1.0f)
                    target->m_pActiveCall = &target->m_GeometryCalls;
                else
                    target->m_pActiveCall = &target->m_AlphaCalls;
                //draw Call
                target->m_CallPosition = this->AddFunction(a_RenderIndex,target->m_pActiveCall, target->m_pActiveCall->end(), &CRenderer::RenderModel, this, a_pModel, a_pMaterial, a_Primitive, a_Position, a_Rotation, a_Center, a_Size, a_Color, a_Cull);
                //add setcalls before draw call
                std::list<SCall>::iterator it;
                for (it = target->m_SetCalls.begin(); it != target->m_SetCalls.end(); ++it)
                    target->m_CallPosition = target->m_pActiveCall->insert(target->m_CallPosition, (*it));
                //add apply before setcalls
                if (target->m_SetCalls.size() != 0)
                    target->m_CallPosition = this->AddFunction(a_RenderIndex,target->m_pActiveCall, target->m_CallPosition, &CRenderer::ApplyMaterial, this, a_pMaterial);
                //Clear values
                target->m_TexturePosition = 1;
                //clear setcalls
                target->m_SetCalls.clear();
            }
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::Draw(uint32 a_Index, bool, CPointLight* a_pPointLight, IMaterial* a_pMaterial, Vector3<float32> a_Position, Color a_Color, float32 a_Radius, float32 a_Intensity, int32 a_RenderIndex)
        {
            if (this->m_Targets.size() > a_Index)
            {
                auto target = this->m_Targets[a_Index];
                //Set active call
                target->m_pActiveCall = &target->m_LightCalls;
                //draw Call
                target->m_CallPosition = this->AddFunction(a_RenderIndex,target->m_pActiveCall, target->m_pActiveCall->end(), &CRenderer::RenderPointLight, this, a_pPointLight, a_pMaterial, a_Position, a_Color, a_Radius, a_Intensity);
                //add setcalls before draw call
                std::list<SCall>::iterator it;
                for (it = target->m_SetCalls.begin(); it != target->m_SetCalls.end(); ++it)
                    target->m_CallPosition = target->m_pActiveCall->insert(target->m_CallPosition, (*it));
                //add apply before setcalls
                if (target->m_SetCalls.size() != 0)
                    target->m_CallPosition = this->AddFunction(a_RenderIndex,target->m_pActiveCall, target->m_CallPosition, &CRenderer::ApplyMaterial, this, a_pMaterial);
                //Clear values
                target->m_TexturePosition = 1;
                //clear setcalls
                target->m_SetCalls.clear();
            }
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::Draw(uint32 a_Index, bool, CDirectionalLight* a_pDirectionalLight, IMaterial* a_pMaterial, Vector3<float32> a_Direction, Color a_Color, int32 a_RenderIndex)
        {
            if (this->m_Targets.size() > a_Index)
            {
                auto target = this->m_Targets[a_Index];
                //Set active call
                target->m_pActiveCall = &target->m_LightCalls;
                //draw Call
                target->m_CallPosition = this->AddFunction(a_RenderIndex,target->m_pActiveCall, target->m_pActiveCall->end(), &CRenderer::RenderDirectionalLight, this, a_pDirectionalLight, a_pMaterial, a_Direction, a_Color);
                //add setcalls before draw call
                std::list<SCall>::iterator it;
                for (it = target->m_SetCalls.begin(); it != target->m_SetCalls.end(); ++it)
                    target->m_CallPosition = target->m_pActiveCall->insert(target->m_CallPosition, (*it));
                //add apply before setcalls
                if (target->m_SetCalls.size() != 0)
                    target->m_CallPosition = this->AddFunction(a_RenderIndex,target->m_pActiveCall, target->m_CallPosition, &CRenderer::ApplyMaterial, this, a_pMaterial);
                //Clear values
                target->m_TexturePosition = 1;
                //clear setcalls
                target->m_SetCalls.clear();
            }
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::Draw(uint32 a_Index, bool a_Cull, CParticleEmitter* a_pEmitter, IMaterial* a_pMaterial, CModel* a_pModel, EPrimitive a_Primitive, int32 a_RenderIndex, float a_Fade)
        {
            if (this->m_Targets.size() > a_Index)
            {
                auto target = this->m_Targets[a_Index];
                //Set active call
                target->m_pActiveCall = &target->m_GeometryCalls;
                //draw Call
                target->m_CallPosition = this->AddFunction(a_RenderIndex,target->m_pActiveCall, target->m_pActiveCall->end(), &CRenderer::RenderEmitterModel, this, a_pEmitter,a_pMaterial, a_pModel, a_Primitive, a_Cull,a_Fade);
                //add setcalls before draw call
                std::list<SCall>::iterator it;
                for (it = target->m_SetCalls.begin(); it != target->m_SetCalls.end(); ++it)
                    target->m_CallPosition = target->m_pActiveCall->insert(target->m_CallPosition, (*it));
                //add apply before setcalls
                if (target->m_SetCalls.size() != 0)
                    target->m_CallPosition = this->AddFunction(a_RenderIndex,target->m_pActiveCall, target->m_CallPosition, &CRenderer::ApplyMaterial, this, a_pMaterial);
                //Clear values
                target->m_TexturePosition = 1;
                //clear setcalls
                target->m_SetCalls.clear();
            }
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::Draw(uint32 a_Index, bool a_Cull, CParticleEmitter* a_pEmitter, IMaterial* a_pMaterial, CSprite* a_pSprite, int32 a_RenderIndex, float a_Fade)
        {
            if (this->m_Targets.size() > a_Index)
            {
                auto target = this->m_Targets[a_Index];
                //Set active call
                target->m_pActiveCall = &target->m_GeometryCalls;
                //draw Call
                target->m_CallPosition = this->AddFunction(a_RenderIndex,target->m_pActiveCall, target->m_pActiveCall->end(), &CRenderer::RenderEmitterSprite, this, a_pEmitter,a_pMaterial, a_pSprite, a_Cull,a_Fade);
                //add setcalls before draw call
                std::list<SCall>::iterator it;
                for (it = target->m_SetCalls.begin(); it != target->m_SetCalls.end(); ++it)
                    target->m_CallPosition = target->m_pActiveCall->insert(target->m_CallPosition, (*it));
                //add apply before setcalls
                if (target->m_SetCalls.size() != 0)
                    target->m_CallPosition = this->AddFunction(a_RenderIndex,target->m_pActiveCall, target->m_CallPosition, &CRenderer::ApplyMaterial, this, a_pMaterial);
                //Clear values
                target->m_TexturePosition = 1;
                //clear setcalls
                target->m_SetCalls.clear();
            }
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::Draw(uint32 a_Index, bool a_Cull, IVertexBuffer* a_pBuffer, int32 a_VertexCount, EPrimitive a_Primitive, IMaterial* a_pMaterial, Vector3<float32> a_Position, Vector3<float32> a_Rotation, Vector3<float32> a_Center, Vector3<float32> a_Size, Color a_Color, int32 a_RenderIndex)
        {
            this->Draw(a_Index, a_Cull, a_pBuffer, a_VertexCount, a_Primitive, a_pMaterial, a_Position, Quaternion<float32>(a_Rotation).GetMatrix(), a_Center, a_Size, a_Color, a_RenderIndex);
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::Draw(uint32 a_Index, bool a_Cull, CModel* a_pModel, EPrimitive a_Primitive, IMaterial* a_pMaterial, Vector3<float32> a_Position, Vector3<float32> a_Rotation, Vector3<float32> a_Center, Vector3<float32> a_Size, Color a_Color, int32 a_RenderIndex)
        {
            this->Draw(a_Index, a_Cull, a_pModel, a_Primitive, a_pMaterial, a_Position, Quaternion<float32>(a_Rotation).GetMatrix(), a_Center, a_Size, a_Color, a_RenderIndex);
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::Draw(uint32 a_Index, bool a_Cull, CFont* a_pFont, IMaterial* a_pMaterial, std::string a_pText, Vector3<float32> a_Position, Vector3<float32> a_Rotation, Vector3<float32> a_Size, float32 a_Offset, Color a_Color, int32 a_RenderIndex)
        {
            this->Draw(a_Index, a_Cull, a_pFont, a_pMaterial, a_pText, a_Position, Quaternion<float32>(a_Rotation).GetMatrix(), a_Size, a_Offset, a_Color, a_RenderIndex);
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::Draw(uint32 a_Index, bool a_Cull, CSprite* a_pSprite, IMaterial* a_pMaterial, Vector3<float32> a_Position, Vector3<float32> a_Rotation, Vector3<float32> a_Center, Vector3<float32> a_Size, Color a_Color, Vector2<float32> a_UVSize, Vector2<float32> a_UVPosition, int32 a_RenderIndex)
        {
            this->Draw(a_Index, a_Cull, a_pSprite, a_pMaterial, a_Position, Quaternion<float32>(a_Rotation).GetMatrix(), a_Center, a_Size, a_Color, a_UVSize, a_UVPosition, a_RenderIndex);
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::Set(uint32 a_Index, float32 a_Value, const char8* a_pName, int32 a_RenderIndex)
        {
            if (this->m_Targets.size() > a_Index)
            {
                auto target = this->m_Targets[a_Index];
                target->m_CallPosition = this->AddFunction(a_RenderIndex,&target->m_SetCalls, target->m_SetCalls.begin(), &CRenderer::UseFloat, this, nullptr, a_Value, a_pName);
            }
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::Set(uint32 a_Index, Vector2<float32> a_Value, const char8* a_pName, int32 a_RenderIndex)
        {
            if (this->m_Targets.size() > a_Index)
            {
                auto target = this->m_Targets[a_Index];
                target->m_CallPosition = this->AddFunction(a_RenderIndex, &target->m_SetCalls, target->m_SetCalls.begin(), &CRenderer::UseVector2, this, nullptr, a_Value, a_pName);
            }
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::Set(uint32 a_Index, Vector3<float32> a_Value, const char8* a_pName, int32 a_RenderIndex)
        {
            if (this->m_Targets.size() > a_Index)
            {
                auto target = this->m_Targets[a_Index];
                target->m_CallPosition = this->AddFunction(a_RenderIndex, &target->m_SetCalls, target->m_SetCalls.begin(), &CRenderer::UseVector3, this, nullptr, a_Value, a_pName);
            }
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::Set(uint32 a_Index, Vector4<float32> a_Value, const char8* a_pName, int32 a_RenderIndex)
        {
            if (this->m_Targets.size() > a_Index)
            {
                auto target = this->m_Targets[a_Index];
                target->m_CallPosition = this->AddFunction(a_RenderIndex, &target->m_SetCalls, target->m_SetCalls.begin(), &CRenderer::UseVector4, this, nullptr, a_Value, a_pName);
            }
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::Set(uint32 a_Index, Color a_Value, const char8* a_pName, int32 a_RenderIndex)
        {
            if (this->m_Targets.size() > a_Index)
            {
                auto target = this->m_Targets[a_Index];
                target->m_CallPosition = this->AddFunction(a_RenderIndex, &target->m_SetCalls, target->m_SetCalls.begin(), &CRenderer::UseColor, this, nullptr, a_Value, a_pName);
            }
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::SetCulling(uint32 a_Index, bool a_Culling, int32 a_RenderIndex)
        {
            if (this->m_Targets.size() > a_Index)
            {
                auto target = this->m_Targets[a_Index];
                target->m_CallPosition = this->AddFunction(a_RenderIndex, &target->m_SetCalls, target->m_SetCalls.begin(), &CRenderer::RenderCulling, this, a_Culling);
            }
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::Set(uint32 a_Index, Matrix<float32> a_Value, const char8* a_pName, int32 a_RenderIndex)
        {
            if (this->m_Targets.size() > a_Index)
            {
                auto target = this->m_Targets[a_Index];
                target->m_CallPosition = this->AddFunction(a_RenderIndex, &target->m_SetCalls, target->m_SetCalls.begin(), &CRenderer::UseMatrix, this, nullptr, a_Value, a_pName);
            }
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::SetTexture(uint32 a_Index, ITexture2D* a_Value, const char8* a_pName, int32 a_RenderIndex)
        {
            if (this->m_Targets.size() > a_Index)
            {
                auto target = this->m_Targets[a_Index];
                target->m_CallPosition = this->AddFunction(a_RenderIndex, &target->m_SetCalls, target->m_SetCalls.begin(), &CRenderer::UseTexture2D, this, nullptr, a_Value, a_pName, target->m_TexturePosition);
                target->m_TexturePosition++;
            }
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::SetCubeMap(uint32 a_Index, ITexture2D* a_Value, const char8* a_pName, int32 a_RenderIndex)
        {
            if (this->m_Targets.size() > a_Index)
            {
                auto target = this->m_Targets[a_Index];
                target->m_CallPosition = this->AddFunction(a_RenderIndex, &target->m_SetCalls, target->m_SetCalls.begin(), &CRenderer::UseCubeMap, this, nullptr, a_Value, a_pName, target->m_TexturePosition);
                target->m_TexturePosition++;
            }
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::SetSSAO(uint32 a_Index,IMaterial* a_pMaterial, CSprite* a_pNoise)
        {
            if (this->m_Targets.size() > a_Index)
            {
                auto target = this->m_Targets[a_Index];
                target->m_pSSAOMaterial = a_pMaterial;
                target->m_pNoiseTexture = a_pNoise;
            }
        }

        // **************************************************************************
        // **************************************************************************
        ITexture2D* CRenderer::GetResult()
        {
            return this->m_pFinalRendertarget->GetTexture2D(0);
        }

        // **************************************************************************
        // **************************************************************************
        ITexture2D* CRenderer::GetTexture(uint32 a_Target, uint32 a_Texture)
        {
            if (this->m_Targets.size() > a_Target)
            {
                if (4 >= a_Texture)
                {
                    return this->m_Targets[a_Target]->m_pRenderTarget->GetTexture2D(a_Texture);
                }
            }
            return nullptr;
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::Render(int32 a_Index, uint32 a_Target, CCamera* a_pCamera, IMaterial* a_pPostMaterial, IMaterial* a_pFinalMaterial, Vector3<float32> a_Position)
        {
            if (this->m_Targets.size() > a_Target)
            {
                auto target = this->m_Targets[a_Target];
                this->m_pActiveRenderTarget = target->m_pRenderTarget;
                this->m_pActivePostCamera = target->m_pPostCamera;
                this->m_pActiveCamera = a_pCamera;


                std::list<SCall>::iterator it;
                STexture2DDescription tdesc = target->m_pRenderTarget->GetTexture2D(0)->GetDescription();
                Vector3<float32> Scale = Vector3<float32>((float32)tdesc.Width, (float32)tdesc.Height, 0.0f);
                this->m_pGraphics->SetCulling(true);
                /////////////  BEGIN GEOMETRY RENDERING  /////////////
                target->m_pRenderTarget->ApplyGeometryPass(Color(0.0f, 0.0f, 0.0f, 0.0f));
                //Render
                for (it = target->m_GeometryCalls.begin(); it != target->m_GeometryCalls.end(); ++it)
                {
                    if (it->RenderIndex == -1 || it->RenderIndex == a_Index)
                        (*it).calledFunction();
                }
                this->m_pGraphics->SetDepthMask(false);
                /////////////  BEGIN ADDITIONAL CALLS  /////////////
                for (it = target->m_AlphaCalls.begin(); it != target->m_AlphaCalls.end(); ++it)
                {
                    if (it->RenderIndex == -1 || it->RenderIndex == a_Index)
                        (*it).calledFunction();
                }
                this->m_pGraphics->SetDepthMask(true);
                this->m_pGraphics->SetCulling(false);
                /////////////  BEGIN LIGHT RENDERING  /////////////
                target->m_pRenderTarget->ApplyLightPass(Color(0.0f, 0.0f, 0.0f, 0.0f));
                //Render
                for (it = target->m_LightCalls.begin(); it != target->m_LightCalls.end(); ++it)
                {
                    if (it->RenderIndex == -1 || it->RenderIndex == a_Index)
                        (*it).calledFunction();
                }

                if (target->m_pSSAOMaterial != NULL)
                {
                    this->m_pActiveRenderTarget->ApplySSAOPass(Color(0.0f, 0.0f, 0.0f, 0.0f));

                    target->m_pSSAOMaterial->Apply();
                    Matrix<float32> InvertViewProjection = this->m_pActiveCamera->GetInvertViewProjection();
                    target->m_pSSAOMaterial->SetMatrix(InvertViewProjection, "InvertViewProjection");
                    Matrix<float32> View = this->m_pActiveCamera->GetView();
                    target->m_pSSAOMaterial->SetMatrix(View, "CamView");
                    target->m_pSSAOMaterial->SetVector2(Vector2<float32>((float32)tdesc.Width, (float32)tdesc.Height), "Resolution");
                    target->m_pSSAOMaterial->SetTexture2D(this->m_pActiveRenderTarget->GetTexture2D(1), "NormalMap", 1);
                    target->m_pSSAOMaterial->SetTexture2D(this->m_pActiveRenderTarget->GetTexture2D(5), "DepthMap", 2);
                    Vector2<float32> tSize = target->m_pNoiseTexture->GetSize();
                    target->m_pSSAOMaterial->SetTexture2D(target->m_pNoiseTexture->GetTexture(), "NoiseTexture", 3);
                    target->m_pSSAOMaterial->SetVector2(Vector2<float32>((float32)tdesc.Width / tSize.X, (float32)tdesc.Height / tSize.Y), "NoiseScale");
                    //Vector2<float32> NearFar = this->m_pActiveCamera->GetNearFar();
                    //target->m_pSSAOMaterial->SetVector2(NearFar, "NearFar");
                    IVertexBuffer* buffer = this->m_pQuad->GetBuffer();
                    this->m_pGraphics->SetVertexBuffer(buffer);
                    target->m_pSSAOMaterial->Apply();
                    this->m_pGraphics->Draw(PuReEngine::Core::EPrimitive::Trianglestrip, buffer->GetSize());
                }
                else
                    this->m_pActiveRenderTarget->ApplySSAOPass(Color(1.0f, 1.0f, 1.0f, 1.0f));

                CBoundingBox viewport;
                viewport.m_Position = a_Position;
                viewport.m_Size = Scale;
                //this->m_pFinalRendertarget->Apply(viewport);

                this->m_pFinalRendertarget->ApplyGeometryPass(Color(0.0f, 0.0f, 0.0f, 0.0f));
                /////////////  BEGIN RENDERING TO BACKBUFFER  /////////////
                //Render
                for (it = target->m_SkyBoxCalls.begin(); it != target->m_SkyBoxCalls.end(); ++it)
                {
                    if (it->RenderIndex == -1 || it->RenderIndex == a_Index)
                        (*it).calledFunction();
                }



                //Apply Post Material
                a_pPostMaterial->Apply();
                this->m_pActiveMaterial = a_pPostMaterial;
                for (it = target->m_SetCalls.begin(); it != target->m_SetCalls.end(); ++it)
                {
                    if (it->RenderIndex == -1 || it->RenderIndex == a_Index)
                        (*it).calledFunction();
                }
                target->m_TexturePosition = 0;


                this->m_pGraphics->SetDepth(false);
                this->m_pActiveRenderTarget->Draw(target->m_pPostCamera, a_pPostMaterial, a_Position, Scale);
                this->m_pGraphics->SetDepth(true);

                target->m_SetCalls.clear();

                this->m_pGraphics->Begin(viewport);
                this->m_pFinalRendertarget->Draw(target->m_pPostCamera, a_pFinalMaterial, a_Position, Scale);

                this->m_pGraphics->SetCulling(true);
            }
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::ApplyMaterial(IMaterial* a_pMaterial)
        {
            a_pMaterial->Apply();
            this->m_pActiveMaterial = a_pMaterial;
        }
        // **************************************************************************
        // **************************************************************************
        void CRenderer::UseFloat(IMaterial* a_pMaterial, float32 a_Value, const char8* a_pName)
        {
            if (a_pMaterial != NULL)
                a_pMaterial->SetFloat(a_Value, a_pName);
            else
                this->m_pActiveMaterial->SetFloat(a_Value, a_pName);
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::UseVector2(IMaterial* a_pMaterial, Vector2<float32> a_Value, const char8* a_pName)
        {
            if (a_pMaterial != NULL)
                a_pMaterial->SetVector2(a_Value, a_pName);
            else
                this->m_pActiveMaterial->SetVector2(a_Value, a_pName);
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::UseVector3(IMaterial* a_pMaterial, Vector3<float32> a_Value, const char8* a_pName)
        {
            if (a_pMaterial != NULL)
                a_pMaterial->SetVector3(a_Value, a_pName);
            else
                this->m_pActiveMaterial->SetVector3(a_Value, a_pName);
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::UseVector4(IMaterial* a_pMaterial, Vector4<float32> a_Value, const char8* a_pName)
        {
            if (a_pMaterial != NULL)
                a_pMaterial->SetVector4(a_Value, a_pName);
            else
                this->m_pActiveMaterial->SetVector4(a_Value, a_pName);
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::UseColor(IMaterial* a_pMaterial, Color a_Value, const char8* a_pName)
        {
            if (a_pMaterial != NULL)
                a_pMaterial->SetColor(a_Value, a_pName);
            else
                this->m_pActiveMaterial->SetColor(a_Value, a_pName);
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::UseMatrix(IMaterial* a_pMaterial, Matrix<float32> a_Value, const char8* a_pName)
        {
            if (a_pMaterial != NULL)
                a_pMaterial->SetMatrix(a_Value, a_pName);
            else
                this->m_pActiveMaterial->SetMatrix(a_Value, a_pName);
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::UseTexture2D(IMaterial* a_pMaterial, ITexture2D* a_Value, const char8* a_pName, int32 m_TextureCount)
        {
            if (a_pMaterial != NULL)
                a_pMaterial->SetTexture2D(a_Value, a_pName, m_TextureCount);
            else
                this->m_pActiveMaterial->SetTexture2D(a_Value, a_pName, m_TextureCount);
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::UseCubeMap(IMaterial* a_pMaterial, ITexture2D* a_Value, const char8* a_pName, int32 m_TextureCount)
        {
            if (a_pMaterial != NULL)
                a_pMaterial->SetTexture2D(a_Value, a_pName, m_TextureCount);
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::RenderPointLight(CPointLight* a_pPointLight, IMaterial* a_pMaterial, Vector3<float32> a_Position, Color a_Color, float32 a_Radius, float32 a_Intensity)
        {
            a_pPointLight->Draw(this->m_pGraphics, a_pMaterial, this->m_pActiveCamera, this->m_pActivePostCamera, this->m_pActiveRenderTarget, a_Position, a_Color, a_Radius, a_Intensity);
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::RenderDirectionalLight(CDirectionalLight* a_pDirectionalLight, IMaterial* a_pMaterial, Vector3<float32> a_Direction, Color a_Color)
        {
            a_pDirectionalLight->Draw(this->m_pGraphics, a_pMaterial, this->m_pActiveCamera, this->m_pActivePostCamera, this->m_pActiveRenderTarget, a_Direction, a_Color);
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::RenderSkybox(CSkyBox* a_pSkyBox, IMaterial* a_pMaterial, Vector3<float32> a_Rotation)
        {
            a_pSkyBox->Draw(this->m_pActiveCamera, a_pMaterial, a_Rotation);
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::RenderInstancedVBuffer(IVertexBuffer* a_pBuffer, int32 a_VertexCount, IMaterial* a_pMaterial, EPrimitive a_Primitive, SRenderInstance* a_pInstances, int32 a_Instances)
        {
            IInstanceBuffer* instanceBuffer;
            instanceBuffer = this->m_pGraphics->CreateInstanceBuffer(a_Instances, sizeof(PuReEngine::Core::SInstance));
            PuReEngine::Core::SInstance* inst = (PuReEngine::Core::SInstance*)instanceBuffer->Lock();
            int count = 0;
            for (int32 i = 0; i < a_Instances; i++)
            {
                Matrix<float32> rot = a_pInstances[i].Rotation;
                Matrix<float32> scale = Matrix<float32>::Scale(a_pInstances[i].Size);
                Matrix<float32> translate = Matrix<float32>::Translation(a_pInstances[i].Position);
                inst[count].World = scale * rot * translate;
                inst[count].Color = a_pInstances[i].Color;
                count++;
            }

            instanceBuffer->Unlock();

            a_pMaterial->Apply();
            this->m_pActiveCamera->Apply(a_pMaterial);
            this->m_pGraphics->SetInstanceBuffer(a_pBuffer, instanceBuffer);
            a_pMaterial->Apply();
            this->m_pGraphics->DrawInstanced(a_Primitive, a_VertexCount, instanceBuffer->GetSize());
            SAFE_DELETE(instanceBuffer);
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::RenderInstancedModels(CModel* a_pModel, IMaterial* a_pMaterial, EPrimitive a_Primitive, SRenderInstance* a_pInstances, int32 a_Instances)
        {
            bool* in = new bool[a_Instances];
            int drawInstances = 0;
            for (int32 i = 0; i < a_Instances; i++)
            {
                CBoundingBox box = a_pModel->GetBoundingBox();
                box.m_Position += a_pInstances[i].Position;
                box.m_Size += a_pInstances[i].Position;
                in[i] = this->m_pActiveCamera->BoxInFrustum(&box);
                if (in[i])
                    drawInstances++;
            }
            if (drawInstances != 0)
            {
                IInstanceBuffer* instanceBuffer = this->m_pGraphics->CreateInstanceBuffer(drawInstances, sizeof(PuReEngine::Core::SInstance));
                PuReEngine::Core::SInstance* inst = (PuReEngine::Core::SInstance*)instanceBuffer->Lock();
                int count = 0;
                for (int32 i = 0; i < a_Instances; i++)
                {
                    if (in[i])
                    {
                        Matrix<float32> rot = a_pInstances[i].Rotation;
                        Matrix<float32> scale = Matrix<float32>::Scale(a_pInstances[i].Size);
                        Matrix<float32> translate = Matrix<float32>::Translation(a_pInstances[i].Position);
                        inst[count].World = scale * rot * translate;
                        inst[count].Color = a_pInstances[i].Color;
                        count++;
                    }
                }

                instanceBuffer->Unlock();
                a_pModel->DrawInstanced(this->m_pActiveCamera, a_pMaterial, a_Primitive, instanceBuffer);
                SAFE_DELETE(instanceBuffer);
            }
            SAFE_DELETE(in);
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::RenderFont(CFont* a_pFont, IMaterial* a_pMaterial, std::string a_Text, Vector3<float32> a_Position, Matrix<float32> a_Rotation, Vector3<float32> a_Size, float32 a_Offset, bool a_FrustrumCheck, Color a_Color)
        {
            CBoundingBox box(Vector3<float32>(-1.0f, -1.0f, 0.0f), Vector3<float32>(1.0f, 1.0f, 0.0f));
            box.m_Position += a_Position;
            box.m_Size += a_Position;
            if (!a_FrustrumCheck || this->m_pActiveCamera->BoxInFrustum(&box))
                a_pFont->Draw(this->m_pActiveCamera, a_pMaterial, a_Text.c_str(), a_Position, a_Size, a_Rotation, a_Offset,a_Color);
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::RenderSprite(CSprite* a_pSprite, IMaterial* a_pMaterial, Vector3<float32> a_Position, Matrix<float32> a_Rotation, Vector3<float32> a_Center, Vector3<float32> a_Size, Color a_Color, bool a_FrustrumCheck, Vector2<float32> a_UVSize, Vector2<float32> a_UVPosition)
        {
            CBoundingBox box(Vector3<float32>(-1.0f, -1.0f, 0.0f), Vector3<float32>(1.0f, 1.0f, 0.0f));
            box.m_Position += a_Position;
            box.m_Size += a_Position;
            Vector3<float32> size = a_Size;
            Vector2<float32> ssize = a_pSprite->GetSize();
            size.X *= ssize.X;
            size.Y *= ssize.Y;
            if (!a_FrustrumCheck || this->m_pActiveCamera->BoxInFrustum(&box))
            {
                if (a_UVSize.Length() == 0.0f)
                    a_pSprite->Draw(this->m_pActiveCamera, a_pMaterial, a_Position, size, a_Rotation, a_Center, a_Color);
                else
                    a_pSprite->Draw(this->m_pActiveCamera, a_pMaterial, a_UVPosition, a_UVSize, a_Position, size, a_Rotation, a_Center, a_Color);
            }
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::RenderVertexBuffer(IVertexBuffer* a_pBuffer, int32 a_VertexCount, IMaterial* a_pMaterial, EPrimitive a_Primitive, Vector3<float32> a_Position, Matrix<float32> a_Rotation, Vector3<float32> a_Center, Vector3<float32> a_Size, Color a_Color)
        {
            //because we start in the middle
            Vector3<float32> size = Vector3<float32>(a_Size.X, a_Size.Y, a_Size.Z);
            Vector3<float32> center = Vector3<float32>(a_Center.X, a_Center.Y, a_Center.Z);
            Vector3<float32> mCenter = Vector3<float32>(-center.X, -center.Y, -center.Z);

            Matrix<float32> rot = Matrix<float32>::Translation(mCenter)*a_Rotation*Matrix<float32>::Translation(center);
            Matrix<float32> scale = Matrix<float32>::Scale(size);
            Matrix<float32> translate = Matrix<float32>::Translation(a_Position);

            a_pMaterial->Apply();
            this->m_pActiveCamera->Apply(a_pMaterial);
            a_pMaterial->SetMatrix(scale, "Scale");
            a_pMaterial->SetMatrix(rot, "Rotation");
            a_pMaterial->SetMatrix(translate, "Translation");
            a_pMaterial->SetColor(a_Color, "Color");
            this->m_pGraphics->SetVertexBuffer(a_pBuffer);
            a_pMaterial->Apply();
            this->m_pGraphics->Draw(a_Primitive, a_VertexCount);
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::RenderModel(CModel* a_pModel, IMaterial* a_pMaterial, EPrimitive a_Primitive, Vector3<float32> a_Position, Matrix<float32> a_Rotation, Vector3<float32> a_Center, Vector3<float32> a_Size, Color a_Color, bool a_FrustrumCheck)
        {
            CBoundingBox box = a_pModel->GetBoundingBox();
            box.m_Position += a_Position;
            box.m_Size += a_Position;
            if (!a_FrustrumCheck || this->m_pActiveCamera->BoxInFrustum(&box))
                a_pModel->Draw(this->m_pActiveCamera, a_pMaterial, a_Primitive, a_Position, a_Size, a_Rotation, a_Center, a_Color);
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::RenderEmitterModel(CParticleEmitter* a_pEmitter, IMaterial* a_pMaterial, CModel* a_pModel, EPrimitive a_Primitive, bool a_FrustrumCheck, float a_Fade)
        {
            a_pEmitter->Render(this->m_pGraphics, a_pModel, this->m_pActiveCamera, a_pMaterial, a_Primitive, a_FrustrumCheck,a_Fade);
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::RenderCulling(bool a_Culling)
        {
            this->m_pGraphics->SetCulling(a_Culling);
        }

        // **************************************************************************
        // **************************************************************************
        void CRenderer::RenderEmitterSprite(CParticleEmitter* a_pEmitter, IMaterial* a_pMaterial, CSprite* a_pSprite, bool a_FrustrumCheck, float a_Fade)
        {
            a_pEmitter->Render(this->m_pGraphics, a_pSprite, this->m_pActiveCamera, a_pMaterial, a_FrustrumCheck,a_Fade);
        }
    }
}