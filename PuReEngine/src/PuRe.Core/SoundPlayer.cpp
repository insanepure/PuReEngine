#include "include/PuReEngine/SoundPlayer.h"
#include "fmod.hpp"

namespace PuReEngine
{
    namespace Core
    {
        struct ChannelInfo
        {
            FMOD::Channel* pChannel;
            std::string Sound;
        };
        ChannelInfo g_Channels[CSoundPlayer::MaxChannels];


        // **************************************************************************
        // **************************************************************************
        CSoundPlayer::CSoundPlayer()
        {
            FMOD::System_Create(&this->m_pSoundSystem);
            this->m_pSoundSystem->init(MaxChannels, FMOD_INIT_NORMAL, 0);
        }

        // **************************************************************************
        // **************************************************************************

        CSoundPlayer::~CSoundPlayer()
        {
            this->m_pSoundSystem->release();
        }

        // **************************************************************************
        // **************************************************************************

        void CSoundPlayer::SetListeners(int a_Listeners)
        {
            this->m_pSoundSystem->set3DNumListeners(a_Listeners);
        }

        // **************************************************************************
        // **************************************************************************

        void CSoundPlayer::SetListenPosition(int a_Listener, Vector3<float32> a_Position , Vector3<float32> a_Velocity , Vector3<float32> a_Forward , Vector3<float32> a_Up)
        {
            FMOD_VECTOR pos, vel, forw, up;

            pos.x = a_Position.X;
            pos.y = a_Position.Y;
            pos.z = a_Position.Z;

            vel.x = a_Velocity.X;
            vel.y = a_Velocity.Y;
            vel.z = a_Velocity.Z;

            forw.x = a_Forward.X;
            forw.y = a_Forward.Y;
            forw.z = a_Forward.Z;

            up.x = a_Up.X;
            up.y = a_Up.Y;
            up.z = a_Up.Z;
            this->m_pSoundSystem->set3DListenerAttributes(a_Listener, &pos, &vel, &forw, &up);
        }

        // **************************************************************************
        // **************************************************************************

        void CSoundPlayer::Update()
        {
            this->m_pSoundSystem->update();
        }

        // **************************************************************************
        // **************************************************************************

        void CSoundPlayer::LoadSound(const char8* a_pPath, const char8* a_pName)
        {
            FMOD::Sound* sound = 0;
            this->m_pSoundSystem->createSound(a_pPath, FMOD_3D, 0, &sound);
            this->m_Sounds.insert(std::pair<std::string, FMOD::Sound*>(a_pName,sound));
            //this->m_Sounds[a_pName] = sound;
        }

        // **************************************************************************
        // **************************************************************************

        void CSoundPlayer::SetPosition(int a_Channel, Vector3<float32> a_Position, Vector3<float32> a_Velocity)
        {
            FMOD_VECTOR pos, vel;

            pos.x = a_Position.X;
            pos.y = a_Position.Y;
            pos.z = a_Position.Z;

            vel.x = a_Velocity.X;
            vel.y = a_Velocity.Y;
            vel.z = a_Velocity.Z;
            g_Channels[a_Channel].pChannel->set3DAttributes(&pos, &vel);
        }

        // **************************************************************************
        // **************************************************************************

        void CSoundPlayer::SetMinMax(int a_Channel, const char8* a_pName, Vector2<float32> a_MinMax)
        {
            auto got = this->m_Sounds.find(a_pName);
            got->second->set3DMinMaxDistance(a_MinMax.X, a_MinMax.Y);
            g_Channels[a_Channel].pChannel->set3DMinMaxDistance(a_MinMax.X, a_MinMax.Y);
        }

        // **************************************************************************
        // **************************************************************************

        void CSoundPlayer::SetVolume(int a_Channel, float32 a_Volume)
        {
            g_Channels[a_Channel].pChannel->setVolume(a_Volume);
        }

        // **************************************************************************
        // **************************************************************************

        void CSoundPlayer::SetLoop(const char8* a_pName, bool a_Loop)
        {
            auto got = this->m_Sounds.find(a_pName);
            //Set Loop Mode
            if (a_Loop)
                got->second->setMode(FMOD_LOOP_NORMAL);
            else
                got->second->setMode(FMOD_LOOP_OFF);
        }

        // **************************************************************************
        // **************************************************************************

        void CSoundPlayer::StopAll()
        {
            for (int i = 0; i < MaxChannels; i++)
                g_Channels[i].pChannel->stop();
        }

        // **************************************************************************
        // **************************************************************************

        void CSoundPlayer::StopSound(int a_Channel)
        {
            g_Channels[a_Channel].pChannel->stop();
        }

        // **************************************************************************
        // **************************************************************************

        int CSoundPlayer::PlaySound(const char8* a_pName, bool a_Loop, bool a_Stop, float32 a_Volume, Vector3<float32> a_Position, Vector3<float32> a_Velocity, Vector2<float32> a_MinMax)
        {
            auto got = this->m_Sounds.find(a_pName);
            //Stop it first
            bool isPlaying;
            int id = 0;
            for (id = 0; id < MaxChannels; ++id)
            {
                g_Channels[id].pChannel->isPlaying(&isPlaying);
                if (!isPlaying || a_Stop&&g_Channels[id].Sound == a_pName)
                    break;
            }
            if (id < MaxChannels)
            {
                g_Channels[id].pChannel->stop();
                g_Channels[id].Sound = a_pName;
                //Set Loop Mode
                if (a_Loop)
                    got->second->setMode(FMOD_LOOP_NORMAL);
                else
                    got->second->setMode(FMOD_LOOP_OFF);
                //Play Sound
                this->m_pSoundSystem->playSound(got->second, 0, true, &g_Channels[id].pChannel);
                FMOD_VECTOR pos, vel;

                pos.x = a_Position.X;
                pos.y = a_Position.Y;
                pos.z = a_Position.Z;

                vel.x = a_Velocity.X;
                vel.y = a_Velocity.Y;
                vel.z = a_Velocity.Z;

                got->second->set3DMinMaxDistance(a_MinMax.X, a_MinMax.Y);
                g_Channels[id].pChannel->set3DMinMaxDistance(a_MinMax.X, a_MinMax.Y);
                g_Channels[id].pChannel->set3DAttributes(&pos, &vel);
                g_Channels[id].pChannel->setVolume(a_Volume);
                g_Channels[id].pChannel->setPaused(false);
                return id;
            }
            else
                return -1;

        }

    }
}