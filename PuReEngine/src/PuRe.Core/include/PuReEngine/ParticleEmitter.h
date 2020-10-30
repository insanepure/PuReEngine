#ifndef _PARTICLEEMITTER_H_
#define _PARTICLEEMITTER_H_

#include "Defines.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Sprite.h"
#include "Model.h"
#include "IGraphics.h"
#include <vector>

// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {
        /// @brief Particles
        ///
        struct Particle
        {
            float32 LifeTime;
            Vector3<float32> Position;
            Vector3<float32> Size;
            Vector3<float32> Velocity;
            Quaternion<float32> Rotation;
            Color Color;
        };
        /// @brief Particle Emitter
        ///
        class CParticleEmitter
        {
        private:
            /// @brief Owned Particles
            ///
            std::vector<Particle> m_Particles;
        public:
            /// @brief Position of the Emitter in world
            ///
            Vector3<float32> m_Position;
            /// @brief Rotation of the Emitter in world
            ///
            Quaternion<float32> m_Rotation;
        private:
            /// @brief Creates the Instance Buffer
            ///
            /// @param Graphics Pointer
            /// @param Whether it should cull or not
            /// @param Camera for culling
            /// @param box for culling
            /// @param When fading should start
            ///
            /// @returns the Instance Buffer
            ///
            IInstanceBuffer* CreateInstanceBuffer(IGraphics* a_pGraphics, bool a_Cull, CCamera* a_pCam, CBoundingBox box,float a_Fade);

        public:
            /// @brief Constructor to initialize an emitter
            /// @param Position for this Emitter
            /// @param Rotation for this Emitter
            ///
            CParticleEmitter(Vector3<float32> a_Position,Quaternion<float32> a_Rotation);
            /// @brief Destructor to destroy an emitter
            ///
            ~CParticleEmitter();
            /// @brief Return the Amount of the particles
            ///
            /// @returns Amount as uint32
            ///
            uint32 GetAmount();
            /// @brief Spawn a new Particle
            ///
            /// @param LifeTime for this Particle
            /// @param Position for this Particle
            /// @param Size for this Particle
            /// @param Velocity for this Particle
            /// @param Rotation for this Particle
            ///
            void Spawn(float32 a_LifeTime=10.0f, Vector3<float32> a_Position = Vector3<float32>(0.0f,0.0f,0.0f), Vector3<float32> a_Size = Vector3<float32>(1.0f, 1.0f, 1.0f), Vector3<float32> a_Velocity = Vector3<float32>(), Quaternion<float32> a_Rotation = Quaternion<float32>(),Color a_Color=Color());
            /// @brief Update the Particles
            ///
            /// @param Deltatime
            ///
            void Update(float32 a_DeltaTime);
            /// @brief Render the Particles as Sprite
            ///
            /// @param Graphics Pointer
            /// @param Sprite for Rendering
            /// @param Camera for Rendering
            /// @param Material for Rendering
            /// @param Primitive for Rendering
            /// @param Whether he should do culling or not
            /// @param When fading should start
            ///
            void Render(IGraphics* a_pGraphics, CSprite* a_pSprite, CCamera* a_pCam, IMaterial* a_pMaterial, bool a_Cull = true, float a_Fade=0.0f);
            /// @brief Render the Particles as Model
            ///
            /// @param Graphics Pointer
            /// @param Model for Rendering
            /// @param Camera for Rendering
            /// @param Material for Rendering
            /// @param Primitive for Rendering
            /// @param Whether he should do culling or not
            /// @param When fading should start
            ///
            void Render(IGraphics* a_pGraphics, CModel* a_pModel, CCamera* a_pCam, IMaterial* a_pMaterial, EPrimitive a_Primitive, bool a_Cull = true, float a_Fade = 0.0f);
        };
    }
}

#endif /* _PARTICLEEMITTER_H_ */
