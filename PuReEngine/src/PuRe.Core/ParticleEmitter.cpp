#include "include/PuReEngine/ParticleEmitter.h"


// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {

        // **************************************************************************
        // **************************************************************************

        CParticleEmitter::CParticleEmitter(Vector3<float32> a_Position, Quaternion<float32> a_Rotation) : m_Position(a_Position), m_Rotation(a_Rotation)
        {

        }

        // **************************************************************************
        // **************************************************************************

        CParticleEmitter::~CParticleEmitter()
        {

        }

        // **************************************************************************
        // **************************************************************************

        uint32 CParticleEmitter::GetAmount()
        {
            return this->m_Particles.size();
        }

        // **************************************************************************
        // **************************************************************************

        void CParticleEmitter::Spawn(float32 a_LifeTime, Vector3<float32> a_Position, Vector3<float32> a_Size, Vector3<float32> a_Velocity, Quaternion<float32> a_Rotation, Color a_Color)
        {
            Particle p;
            p.LifeTime = a_LifeTime;
            p.Position = this->m_Position+(a_Position*m_Rotation);
            p.Size = a_Size;
            p.Velocity = a_Velocity*m_Rotation;
            p.Rotation = a_Rotation;
            p.Color = a_Color;
            this->m_Particles.push_back(p);
        }

        // **************************************************************************
        // **************************************************************************

        IInstanceBuffer* CParticleEmitter::CreateInstanceBuffer(IGraphics* a_pGraphics, bool a_Cull, CCamera* a_pCam, CBoundingBox a_Box, float a_Fade)
        {

            bool* in = new bool[this->m_Particles.size()];
            int drawInstances = 0;

            if (a_Cull)
            {
                for (uint32 i = 0; i < this->m_Particles.size(); i++)
                {
                    CBoundingBox box = a_Box;
                    box.m_Position += this->m_Particles[i].Position;
                    box.m_Size += this->m_Particles[i].Position;
                    in[i] = a_pCam->BoxInFrustum(&box);
                    if (in[i])
                        drawInstances++;
                }
            }
            else
                drawInstances = this->m_Particles.size();

            if (drawInstances != 0)
            {
                IInstanceBuffer* instanceBuffer = a_pGraphics->CreateInstanceBuffer(drawInstances, sizeof(PuReEngine::Core::SInstance));
                PuReEngine::Core::SInstance* inst = (PuReEngine::Core::SInstance*)instanceBuffer->Lock();
                int count = 0;
                for (uint32 i = 0; i < this->m_Particles.size(); i++)
                {
                    uint32 index = this->m_Particles.size()-i;
                    index -= 1;
                    if (!a_Cull || in[index])
                    {
                        Matrix<float32> rot = this->m_Particles[index].Rotation.GetMatrix();
                        Matrix<float32> scale = Matrix<float32>::Scale(this->m_Particles[index].Size);
                        Matrix<float32> translate = Matrix<float32>::Translation(this->m_Particles[index].Position);
                        inst[count].World = scale * rot * translate;
                        inst[count].Color = this->m_Particles[index].Color;
                        if (a_Fade > this->m_Particles[index].LifeTime)
                        {
                            float fadeFactor = this->m_Particles[index].LifeTime*(1.0f / a_Fade);
                            inst[count].Color.A *= fadeFactor;
                        }
                        count++;
                    }
                }
                instanceBuffer->Unlock();
                return instanceBuffer;
            }
            return nullptr;
        }

        // **************************************************************************
        // **************************************************************************

        void CParticleEmitter::Update(float32 a_DeltaTime)
        {
            for (uint32 i = 0; i < this->m_Particles.size(); i++)
            {
                this->m_Particles[i].LifeTime -= a_DeltaTime;
                if (this->m_Particles[i].LifeTime < 0)
                {
                    this->m_Particles.erase(this->m_Particles.begin()+i);
                    --i;
                }
                else
                    this->m_Particles[i].Position += this->m_Particles[i].Velocity;
            }
        }

        // **************************************************************************
        // **************************************************************************

        void CParticleEmitter::Render(IGraphics* a_pGraphics, CSprite* a_pSprite, CCamera* a_pCam, IMaterial* a_pMaterial, bool a_Cull, float a_Fade)
        {
            IInstanceBuffer* instanceBuffer = this->CreateInstanceBuffer(a_pGraphics, a_Cull, a_pCam, CBoundingBox(Vector3<float32>(-1.0f, -1.0f, 0.0f), Vector3<float32>(1.0f, 1.0f, 0.0f)),a_Fade);
            if (instanceBuffer != nullptr)
            {
                a_pSprite->DrawInstanced(a_pCam, a_pMaterial, instanceBuffer);
                SAFE_DELETE(instanceBuffer);
            }
        }

        // **************************************************************************
        // **************************************************************************

        void CParticleEmitter::Render(IGraphics* a_pGraphics, CModel* a_pModel, CCamera* a_pCam, IMaterial* a_pMaterial, EPrimitive a_Primitive, bool a_Cull, float a_Fade)
        {
            IInstanceBuffer* instanceBuffer = this->CreateInstanceBuffer(a_pGraphics, a_Cull, a_pCam, a_pModel->GetBoundingBox(), a_Fade);
            if (instanceBuffer != nullptr)
            {
                a_pModel->DrawInstanced(a_pCam, a_pMaterial, a_Primitive, instanceBuffer);
                SAFE_DELETE(instanceBuffer);
            }
        }
    }
}