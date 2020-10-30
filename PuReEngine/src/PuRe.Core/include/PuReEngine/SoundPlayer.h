#ifndef _SOUNDPLAYER_H_
#define _SOUNDPLAYER_H_
// Engine specific includes
#include "Defines.h"

#include <unordered_map>

#include "Vector3.h"

// Declare namespace PuReEngine::Core
namespace FMOD
{
    class System;
    class Sound;
}

namespace PuReEngine
{
    namespace Core
    {
        /// @brief SoundPlayer to Play Sound and Music
        ///
        class CSoundPlayer
        {
        private:
            /// @brief Loaded Sounds saved into an unordered map for fast access
            ///
            std::unordered_map<std::string, FMOD::Sound*> m_Sounds;
            /// @brief Sound System
            ///
            FMOD::System* m_pSoundSystem;

        public:
            enum { MaxChannels = 64 };
        public:
            /// @brief Creates an instance of SoundPlayer.
            ///
            CSoundPlayer();

            /// @brief Destroyes an instance of SoundPlayer.
            ///
            ~CSoundPlayer();
        public:
            /// @brief Update the system
            ///
            void Update();
            /// @brief Set the amount of Listeners
            ///
            /// @param  Amount of Listeners
            ///
            void SetListeners(int a_Listeners);
            /// @brief Set the Position of a Listener
            ///
            /// @param Which Listener
            ///
            void SetListenPosition(int a_Listener, Vector3<float32> a_Position , Vector3<float32> a_Velocity , Vector3<float32> a_Forward , Vector3<float32> a_Up);
            /// @brief Load and Save a Sound into our map
            ///
            /// @param Path to the Sound
            /// @param Name of the Sound
            ///
            void LoadSound(const char8* a_pPath, const char8* a_pName);
            /// @brief Change the Volume of a Sound
            ///
            /// @param Channel to change
            /// @param New Volume
            ///
            void SetVolume(int a_Channel,float32 a_Volume);
            /// @brief Change that the sound loops or not
            ///
            /// @param Name of the Sound
            /// @param If the Sound should loop or not
            ///
            void SetLoop(const char8* a_pName, bool a_Loop);
            /// @brief Change The Position of a Sound
            ///
            /// @param Channel to change
            /// @param New Position
            /// @param New Velocity
            ///
            void SetPosition(int a_Channel, Vector3<float32> a_Position, Vector3<float32> a_Velocity);
            /// @brief Change The MinMax of a Sound
            ///
            /// @param Channel to change
            /// @param New Minmax
            ///
            void SetMinMax(int a_Channel, const char8* a_pName, Vector2<float32> a_MinMaxDist);
            /// @brief Stop all Sounds
            ///
            void StopAll();
            /// @brief Stop a Sound from playing
            ///
            /// @param Channel to stop
            ///
            void StopSound(int a_Channel);
            /// @brief Play a Sound based on a Name
            ///
            /// @param Name of the Sound
            /// @param If the Sound should loop or not
            /// @param If the Sound should stop or not
            /// @param Volume
            /// @param Position
            /// @param Velocity
            /// @param MinMaxDistance
            ///
            int PlaySound(const char8* a_pName, bool a_Loop, bool a_Stop, float32 a_Volume,
                Vector3<float32> a_Position = Vector3<float32>(), Vector3<float32> a_Velocity = Vector3<float32>(), Vector2<float32> a_MinMaxDist = Vector2<float32>());
        };
    }
}
#endif /* _SOUNDPLAYER_H_ */